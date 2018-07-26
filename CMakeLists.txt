cmake_minimum_required(VERSION 3.9)
project(SCCAlgorithm)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS_RELEASE -O3)

SET(CMAKE_CXX_FLAGS -lboost_timer)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREAD ON)

#set(BOOST_ROOT "/usr/local/boost_1_67_0/boost_1_67_0")
#find_package(Boost 1.67.0 COMPONENTS timers REQUIRED)
#if(NOT Boost_FOUND)
#    message(FATAL_ERROR "Could not find boost!")
#endif()
#include_directories(${Boost_INCLUDE_DIR})


add_executable(SCCAlgorithm main.cpp SCCAlgorithm/StrongConnectedComponents.h SCCAlgorithm/StrongConnectedComponentsNuutila.h)

add_executable(Testing SCCAlgorithmTesting/Testing.cpp)
add_executable(TestingNuutila SCCAlgorithmTesting/TestingNuutila.cpp)

IF(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(SCCAlgorithm PRIVATE SILENCE)
ENDIF(CMAKE_BUILD_TYPE MATCHES Release)
