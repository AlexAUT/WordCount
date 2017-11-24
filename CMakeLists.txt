cmake_minimum_required(VERSION 2.8)

set(SOURCES src/main.cpp src/wordCounter.hpp src/wordCounter.cpp)

project(WordCount)
add_executable(${PROJECT_NAME} ${SOURCES})
