cmake_minimum_required(VERSION 3.4)

project(format)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES format.cpp)

add_library(format ${SOURCE_FILES})

install (TARGETS format DESTINATION lib)

install(FILES format.h DESTINATION include)