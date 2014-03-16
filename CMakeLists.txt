cmake_minimum_required(VERSION 2.6)

project(contig_reference)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(cr contig_reference.cpp)
target_link_libraries (cr bamtools)

install(TARGETS cr DESTINATION bin)


