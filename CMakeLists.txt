cmake_minimum_required(VERSION 3.3)
project(cs380)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    hw1/GameState.cpp
    hw1/GameState.h
    hw1/main.cpp
    hw1/Move.cpp
    hw1/Move.h
    hw2/BasketGame.cpp
    hw2/BasketGame.h
    hw2/main.cpp
    hw2/Move.cpp
    hw2/Move.h)

add_executable(cs380 ${SOURCE_FILES})