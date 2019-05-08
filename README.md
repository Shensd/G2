# G2

Have you ever wanted to make generating hard to read code easier than ever?

### What is This?

G2 (short for general2) is a command line tool that generates obfuscated C code in random patterns with a future goal to output in the form of image ascii art. It is written from scratch in C++, with the goal of as little imports as possible.

### How Do I Use It?

G2 is a rather simple tool currently, and doesn't have many command line flags, here is the current help output:

```
G2 - An obfuscated C message generator

USAGE: G2 [OPTIONS] [TEXT]

Options:
--help, -h
   show this help text and exit
--text, -t
   text to encode
--in, -i
   name of input file
--out, -o
   (use - for stdout) name of output c file
--intensity
   numeric value to determine how intense the obfuscation should be
--whitespace, -w
   set to randomize whitespace

Copyright 2019 Jack Hance

```

### How Do I Build It?

G2 has an included [CMake](https://cmake.org/) file, so all one needs to do is the following:

 * Create a directory named `build` or something similar
 * `cd` into the directory
 * Execute `cmake .. && make`

The output executable will be named `G2`.


###### This project is licensed under the MIT Open Source License, see `LICENSE` for more information.