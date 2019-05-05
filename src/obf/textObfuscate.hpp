#ifndef TEXT_OBFUSCATE_HPP
#define TEXT_OBFUSCATE_HPP

#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <cctype>

#include <iostream>

#include "../tree/tree.hpp"

namespace obf {

    // private namespace
    namespace _helper {

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

        enum SIDE {
            LEFT = true,
            RIGHT = false
        };

        struct ArithmeticTreeMember {
            bool isOperator = false;

            int value;

            ArithmeticTreeMember(bool isOperator, int value) : isOperator(isOperator), value(value) {}
            ArithmeticTreeMember() {}
        };

        std::string EulersTourTreeTraverse(Tree<ArithmeticTreeMember>* tree, Position<ArithmeticTreeMember>* position);

        Tree<ArithmeticTreeMember> randomBreak(int num);

        std::vector<int> getAsciiValues(std::string str);

        Position<ArithmeticTreeMember>* getRandomNumberNode(Tree<ArithmeticTreeMember>* tree, Position<ArithmeticTreeMember>* startPoint);

        std::string getWeirdArithmetic(int num, int rounds = 1);

        // prime functions
        bool isPrime(int num);
        std::vector<int> getPrimeFactorization(int num);

        // spread functions
        std::pair<int, int> getSpreadAddition(int num);
        std::pair<int, int> getSpreadSubtraction(int num, int maxOverflow = 200);
        std::pair<int, int> getSpreadMultiplication(int num);
        std::pair<int, int> getSpreadDivision(int num, int maxOverflow = 200);
        std::pair<int, int> getSpreadXOR(int num, int maxOverflow = 200);
    }

    /**
     * TODO
     * 
     * Other methods of obfuscation could be
     * - Struct spam (we make a lot of structs and fill those with data and its awful)
     * - String arithmetic 
     * - function spam, we make functions that return what we want and its also awful
     *    - we can repeatidly pipe input and output from function to function to make very long chains
     * - pointers somehow? I feel like we could do something with pointer offsets 
     *    - maybe we can place items art certain memory positiongs and read the positions themselves as
     *      chars (convert memory addresses into chars)
     *    - if memory positions are consistent between runs then we should be able to do
     *      math with the memory addresses themselves consistently
     * - More spread operators (or, and, left shift, right shift, not somehow?)
     * - predicitable randomization
     *    - logically if we start with the same seed then it should produce the same result (probably varies
     *      across system though)
     * - take an image, convert it to black and white, and basically place characters on each
     *   black pixel creating an image of the given message
     * - and a mix of all of the above 
     */


    std::string textObfuscate(std::string message, int intensity=1);

}

#endif // !TEXT_OBFUSCATE_HPP