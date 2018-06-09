cmake_minimum_required(VERSION 3.9)
project(SCCAlgorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(SCCAlgorithm main.cpp SCCAlgorithm/StronglyConnectedComponents.cpp SCCAlgorithm/StronglyConnectedComponents.h Tests.h)


