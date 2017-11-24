//
// Created by alex on 11/24/17.
//

#ifndef WORDCOUNT_WORDCOUNTER_HPP
#define WORDCOUNT_WORDCOUNTER_HPP

#include <fstream>
#include <unordered_map>


class WordCounter
{
public:
  typedef std::unordered_map<std::string, unsigned> WordCountMap;

public:
  WordCounter(const std::string& fileName);

  void processFile();

  bool isFileOpen() const;
  const WordCountMap& getWordCountMap() const;

private:

private:
  std::fstream mFile;
  WordCountMap mWordCountMap;
};

#endif //WORDCOUNT_WORDCOUNTER_HPP
