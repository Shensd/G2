cmake_minimum_required(VERSION 3.0)

project(G2)

include_directories(src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(G2 ${SOURCES})