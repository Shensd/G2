#ifndef WHITESPACE_HPP
#define WHITESPACE_HPP

#include <string>
#include <stdlib.h>
#include <iostream>

namespace obf {

    // private namespace
    namespace {
        std::string replace(std::string str, std::string original, std::string replacement, int start = 0);
    }

    std::string randomizeWhitespace(std::string str, int intensity=1);
}

#endif // !WHTIESPACE_HPP