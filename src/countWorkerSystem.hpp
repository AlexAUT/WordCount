//
// Created by alex on 11/24/17.
//

#ifndef WORDCOUNT_COUNTWORKERSYSTEM_HPP
#define WORDCOUNT_COUNTWORKERSYSTEM_HPP

#include <array>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>

class CountWorkerSystem
{
public:
  typedef std::queue<std::string> LineQueue;
  typedef std::unordered_map<std::string, unsigned> WordCountMap;
public:
  CountWorkerSystem();
  explicit CountWorkerSystem(unsigned numberOfWorkers);
  ~CountWorkerSystem();

  void addJob(const std::string& line);
  bool getJob(std::string& line);

  void addWords(const WordCountMap& map);

  void stop();

  bool isRunning() const;
  const WordCountMap& getWordCountMap() const;
private:
  bool mRunning;

  std::mutex mWordCountMutex;
  WordCountMap mWordCount;

  std::condition_variable mCondWaitForJobs;
  std::mutex mLinesToParseMutex;
  LineQueue mLinesToParse;

  std::vector<std::thread> mWorkers;
};


#endif //WORDCOUNT_COUNTWORKERSYSTEM_HPP
