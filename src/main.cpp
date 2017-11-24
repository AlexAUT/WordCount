#include <iostream>
#include <vector>

#include "wordCounter.hpp"

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

int main(int argc, const char** argv)
{
  auto filePaths = parseCommandLineArguments(argc, argv);

  if(filePaths.empty())
    return -1;


  std::vector<WordCounter> wordCounters;
  for(auto& filePath : filePaths)
    wordCounters.emplace_back(filePath);

  for(auto& wordCounter : wordCounters)
    wordCounter.processFile();


  WordCounter::WordCountMap completeMap;
  for(auto& wordCounter : wordCounters)
  {
    auto map = wordCounter.getWordCountMap();
    for(auto& word : map)
      completeMap[word.first] = completeMap[word.first] + word.second;
  }

  for(auto &entry : completeMap)
    std::cout << entry.first << " -> " << entry.second << std::endl;

  return 0;
}
