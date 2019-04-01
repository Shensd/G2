#ifndef TEXT_OBFUSCATE_HPP
#define TEXT_OBFUSCATE_HPP

#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "../tree/tree.hpp"

namespace obf {

    // private namespace
    namespace {

        enum OPERATOR {
            ADD      = '+',
            SUBTRACT = '-',
            MULTIPLY = '*',
            DIVIDE   = '/',
            XOR      = '^',
            NOT      = '!',
            AND      = '&',
            OR       = '|'
        };

        struct ArithmeticTreeMember {
            bool isOperator = false;

            int value;

            ArithmeticTreeMember(bool isOperator, int value) : isOperator(isOperator), value(value) {}
        };

        std::string EulersTourTreeTraverse(Tree<ArithmeticTreeMember>* tree, Position<ArithmeticTreeMember>* position);

        std::vector<int> getAsciiValues(std::string str);
        std::string getWeirdArithmetic(int num, int rounds);

        // prime functions
        bool isPrime(int num);
        std::vector<int> getPrimeFactorization(int num);

        // spread functions
        std::pair<int, int> getSpreadAddition(int num);
        std::pair<int, int> getSpreadSubtraction(int num, int maxOverflow);
        std::pair<int, int> getSpreadXOR(int num, int maxOverflow);

    }


    std::string textObfuscate(std::string message);

}

#endif // !TEXT_OBFUSCATE_HPP