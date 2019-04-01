cmake_minimum_required(VERSION 3.0)

project(G2)

add_executable(
    G2

    src/main.cpp
    
    src/args/parseArgs.cpp

    src/obf/textObfuscate.cpp
)