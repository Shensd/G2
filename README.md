# G2

Have you ever wanted to make generating hard to read code easier than ever?

### What is This?

G2 (short for general2) is a command line tool that generates obfuscated C code in either random patterns or in the form of images. It is written from scratch in C++, with the goal of as little imports as possible.

### How Do I Use It?

Because I am top teir lazy and this tool is not finished, here is the current help output:

```
G2 - An obfuscated C message generator

USAGE: G2 [OPTIONS] [TEXT]

Options:
--help, -h
   show this help text and exit
--text, -t
   text to encode
--filename, -o
   (default out.c) name of output c file

Copyright 2019 Jack Hance
```

### How Do I Build It?

This project is configured with [CMake](https://cmake.org/), so to build it simply create a directory in the project named `build`, cd into it, and then run `cmake ..`

###### This project is licensed under the MIT Open Source License 