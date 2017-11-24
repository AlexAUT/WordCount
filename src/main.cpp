#include <iostream>
#include <iomanip>
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

void printResults(WordCounter::WordCountMap wordCounts)
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


  std::vector<WordCounter> wordCounters;
  //Create for every file a word counter
  for(auto& filePath : filePaths)
    wordCounters.emplace_back(filePath);
  //Start processing each file
  for(auto& wordCounter : wordCounters)
    wordCounter.processFile();

  //Join results of all files
  WordCounter::WordCountMap completeMap;
  for(auto& wordCounter : wordCounters)
  {
    auto map = wordCounter.getWordCountMap();
    for(auto& word : map)
      completeMap[word.first] = completeMap[word.first] + word.second;
  }

  //Print results
  printResults(completeMap);

  return 0;
}
