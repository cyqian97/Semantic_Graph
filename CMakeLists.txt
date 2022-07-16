cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(semantic_graph)


set(CMAKE_BUILD_TYPE Release)

add_executable (semantic_graph_builder src/semantic_graph_builder.cpp)
add_executable (test src/test.cpp)
