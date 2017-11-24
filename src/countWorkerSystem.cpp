//
// Created by alex on 11/24/17.
//

#include "countWorkerSystem.hpp"

#include <iostream>
#include <sstream>

void workerFunction(CountWorkerSystem* countSystem, unsigned id)
{
  CountWorkerSystem::WordCountMap wordCount;
  while(true)
  {
    std::string line;
    if(!countSystem->getJob(line))
      break; //If get job returns false, the system has no jobs left and is shutdown

    //Split words
    std::stringstream lineStream(line);
    std::string word;
    while(std::getline(lineStream, word, ' '))
    {
      wordCount[word] = wordCount[word] + 1;
    }
  }
  // Now report word count to system
  countSystem->addWords(wordCount);
}

CountWorkerSystem::CountWorkerSystem():
  CountWorkerSystem(10)
{}

CountWorkerSystem::CountWorkerSystem(unsigned numberOfWorkers) :
  mRunning(true)
{
  //Create workers
  for(unsigned i = 0; i < numberOfWorkers; i++)
  {
    mWorkers.emplace_back(workerFunction, this, i);
  }
}

CountWorkerSystem::~CountWorkerSystem()
{
  if(mRunning)
    stop();
}

void CountWorkerSystem::addJob(const std::string& line)
{
  mLinesToParseMutex.lock();
  mLinesToParse.push(line);
  mCondWaitForJobs.notify_one();
  mLinesToParseMutex.unlock();
}

bool CountWorkerSystem::getJob(std::string& line)
{
  std::unique_lock<std::mutex> lock(mLinesToParseMutex);
  while(true)
  {
    if (!mLinesToParse.empty())
    {
      //Get the job, unlock, return
      line = mLinesToParse.front();
      mLinesToParse.pop();
      return true;
    }
    else if(!mRunning)
    {
      return false; //Signal no more jobs left, because system shutdown
    }
    else
    {
      //IO bound, wait for new input
      mCondWaitForJobs.wait(lock);
    }
  }
}

void CountWorkerSystem::addWords(const WordCountMap& map)
{
  std::unique_lock<std::mutex> lock(mWordCountMutex);
  for(auto& word : map)
    mWordCount[word.first] = mWordCount[word.first] + word.second;
}

void CountWorkerSystem::stop()
{
  //Notify waiting waiters
  //Lock is important, otherwise deadlock would be possible
  mLinesToParseMutex.lock();
  mRunning = false;
  mCondWaitForJobs.notify_all();
  mLinesToParseMutex.unlock();
  //Now wait for them to terminate
  for(auto& worker : mWorkers)
    worker.join();
  if(!mLinesToParse.empty())
    throw std::runtime_error("Threading problem, no all jobs got completed!");
}

bool CountWorkerSystem::isRunning() const
{
  return mRunning;
}

const CountWorkerSystem::WordCountMap &CountWorkerSystem::getWordCountMap() const
{
  return mWordCount;
}
