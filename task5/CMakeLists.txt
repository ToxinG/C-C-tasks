cmake_minimum_required(VERSION 3.4)

project(task5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES format.cpp Test.cpp)
add_executable(task5 ${SOURCE_FILES})
add_library(format ${SOURCE_FILES})
target_link_libraries(task5 format)

set(HEADERS Test.cpp)
set(SOURCES format.cpp)
install (TARGETS format DESTINATION lib)
install(FILES format.h DESTINATION include)
