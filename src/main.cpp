#include <iostream>
#include <iomanip>
#include <vector>

#include <fstream>

#include "countWorkerSystem.hpp"

const unsigned NUMBER_OF_WORKERS = 10;


std::vector<std::string> parseCommandLineArguments(int argc, const char** argv)
{
  std::vector<std::string> filePaths;
  if(argc < 2)
  {
    std::cout << "Please call this program with file paths as command line arguments" << std::endl;
  } else
  {
    for(std::size_t i = 1; i < argc; i++)
    {
      filePaths.emplace_back(argv[i]);
    }
  }
  return filePaths;
}

void processFile(const std::string& fileName, CountWorkerSystem& countSystem)
{
  std::fstream file(fileName.c_str(), std::ios::in);

  if(!file.is_open())
  {
    std::cout << "Could not open file: " << fileName << std::endl;
    return;
  }

  //Read file line by line
  std::string line;
  while(std::getline(file, line))
  {
    countSystem.addJob(line);
  }
}

void printResults(CountWorkerSystem::WordCountMap wordCounts)
{
  //Find longest word
  std::size_t maxLength = 0;
  for(auto& word : wordCounts)
    maxLength = std::max(maxLength, word.first.size());

  //Format helpers
  using std::left;
  using std::right;
  auto cell1Format = std::setw(static_cast<int>(maxLength));
  auto cell2Format = std::setw(10);
  //Print
  std::cout << left << cell1Format << "Wort" << right << cell2Format << "Anzahl" << std::endl;
  for(auto &entry : wordCounts)
    std::cout << left << cell1Format << entry.first << right << cell2Format << entry.second << std::endl;

}

int main(int argc, const char** argv)
{
  auto filePaths = parseCommandLineArguments(argc, argv);

  if(filePaths.empty())
    return -1;

  CountWorkerSystem countSystem(NUMBER_OF_WORKERS);
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
  for(auto& filePath : filePaths)
  {
    processFile(filePath, countSystem);
  }

  //This is a blocking call, will stop workers (after all jobs are completed)
  countSystem.stop();

  //Print results
  printResults(countSystem.getWordCountMap());

  return 0;
}
