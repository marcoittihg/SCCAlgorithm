cmake_minimum_required(VERSION 3.9)
project(SCCAlgorithm)

set(CMAKE_CXX_STANDARD 11)

#SET(CMAKE_CXX_FLAGS_RELEASE -O3)

add_executable(SCCAlgorithm main.cpp SCCAlgorithm/StronglyConnectedComponents.cpp SCCAlgorithm/StronglyConnectedComponents.h)

add_executable(Testing SCCAlgorithmTesting/Testing.cpp)