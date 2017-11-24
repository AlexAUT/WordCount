//
// Created by alex on 11/24/17.
//

#include "wordCounter.hpp"

#include <iostream>
#include <string>
#include <sstream>

WordCounter::WordCounter(const std::string &fileName) :
  mFile(fileName.c_str(), std::ios::in)
{
  if(!mFile.is_open())
    std::cout << "Could not read file: " << fileName << std::endl;
}

void WordCounter::processFile()
{
  if(isFileOpen())
  {
    std::string line;
    //Split lines
    while(std::getline(mFile, line))
    {
      //Split words
      //Slow but elegant version
      std::stringstream lineStream(line);
      std::string word;
      while(std::getline(lineStream, word, ' '))
      {
        mWordCountMap[word] = mWordCountMap[word] + 1;
      }
      //Faster version but a bit more ugly
//      std::size_t wordStart = 0;
//      std::size_t wordEnd = line.find(' ');
//      // Save tokens
//      while(wordEnd != std::string::npos)
//      {
//        word = line.substr(wordStart, wordEnd - wordStart);
//        std::cout << "Word: " << word << std::endl;
//        //Skip whitespace
//        wordStart = wordEnd + 1;
//        wordEnd = line.find(' ', wordStart);
//      }
//      // Store last token (until end of line)
//      word = line.substr(wordStart);
//      std::cout << "Word: " << word << std::endl;
    }

  }
}

bool WordCounter::isFileOpen() const
{
  return mFile.is_open();
}

const WordCounter::WordCountMap& WordCounter::getWordCountMap() const
{
  return mWordCountMap;
}
