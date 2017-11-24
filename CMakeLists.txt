cmake_minimum_required(VERSION 2.8)

project(WordCount CXX)


set(SOURCES src/main.cpp src/countWorkerSystem.cpp src/countWorkerSystem.hpp)
find_package( Threads )

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )