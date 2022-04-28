cmake_minimum_required(VERSION 3.15)
project(OSFour)

set(CMAKE_CXX_STANDARD 14)

add_executable(OSFour prog4.cpp prog4_LRUclean.h prog4_MRU.h prog4_MyOwn.h)