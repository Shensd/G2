#ifndef TEXT_OBFUSCATE_HPP
#define TEXT_OBFUSCATE_HPP

#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include <iostream>

namespace obf {

    // private namespace
    namespace {

        struct OperationPair {
            char operation;
            int first, second;
            OperationPair(char operation, int first, int second) : 
                operation(operation), first(first), second(second) {}
            OperationPair() {}
        };

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