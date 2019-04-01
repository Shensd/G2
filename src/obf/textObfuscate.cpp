#include "textObfuscate.hpp"

namespace obf {

    // private namespace
    namespace {

        std::string EulersTourTreeTraverse(Tree<ArithmeticTreeMember>* tree, Node<ArithmeticTreeMember>* position) {
            std::string tour = "";

            if(tree->getLeft(position) != nullptr) {
                tour += "(" + EulersTourTreeTraverse(tree, tree->getLeft(position));
            }

            ArithmeticTreeMember temp = position->getElement();
            if(temp.isOperator) {
                tour += " " + std::to_string((char) temp.value) + " ";
            } else {
                tour += " " + std::to_string(temp.value) + " ";
            }

            if(tree->getRight(position) != nullptr) {
                tour += EulersTourTreeTraverse(tree, tree->getRight(position)) + ")";
            }

            return tour;
        }

        /**
         * Returns a vector of all ascii values in a string
         * 
         * @param str string to convert to ascii values
         * @return vector of ascii values
         */
        std::vector<int> getAsciiValues(std::string str) {
            std::vector<int> asciis;
            for(char s : str) {
                asciis.push_back((int) s);
            }
            return asciis;
        }

        /**
         * Convert an int to a string of a given number of arithmetic expressions
         * 
         * @param num number to convert
         * @param rounds of splitting to perform on numbers
         * @return string of odd arithemetic 
         */
        std::string getWeirdArithmetic(int num, int rounds = 1) {
            ArithmeticTreeMember root(false, num);

            Tree<ArithmeticTreeMember> equationTree(root);
            
            std::pair<int, int> p = getSpreadXOR(num, 200);

            std::cout << p.first << "," << p.second << std::endl;

            root.isOperator = true;
            root.value = OPERATOR::XOR;

            ArithmeticTreeMember left(false, p.first);
            ArithmeticTreeMember right(false, p.second);

            equationTree.setElement(equationTree.getRoot(), root); 
            equationTree.setLeft(equationTree.getRoot(), left);
            equationTree.setRight(equationTree.getRoot(), right);

            std::cout << equationTree.getRoot() << std::endl;
            std::cout << equationTree.getLeft(equationTree.getRoot()) << std::endl;
            std::cout << equationTree.getRight(equationTree.getRoot()) << std::endl;

            return EulersTourTreeTraverse(&equationTree, equationTree.getRoot());
        }

        /**
         * Returns true if a given number is prime
         * 
         * @param num number to check
         * @return true if given number is prime
         */
        bool isPrime(int num) {
            if(num == 1 || num == 2) return true;
            if(num % 2 == 0) return false;
            
            int max = ceil( sqrt( num + 1 ) );

            for(int i = 3; i < max; i+=2) {
                if(num % i == 0) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Get the prime factorization of a given number
         * 
         * @param num number to factorize
         * @return vector of primes 
         */
        std::vector<int> getPrimeFactorization(int num) {
            std::vector<int> factors;

            if(isPrime(num)) {
                factors.push_back(num);
            } else {
                int max = ceil( sqrt( num + 1 ) );

                for(int i = 2; i < max; i++) {
                    if(num % i == 0) {
                        std::vector<int> subFactors;
                        
                        // get prime factorization of divisor
                        subFactors = getPrimeFactorization(i);
                        factors.insert(factors.end(), subFactors.begin(), subFactors.end());

                        // get prime factorization of divided
                        subFactors = getPrimeFactorization(num / i);
                        factors.insert(factors.end(), subFactors.begin(), subFactors.end());

                        break;
                    }
                }
            }

            return factors;
        }

        /**
         * Spreads out a given number by addition
         * 
         * @param num number to spread
         * @return a vector of numbers that can be added up to original
         */
        std::pair<int, int> getSpreadAddition(int num) {
            
            if(num == 0) {
                return std::pair<int, int>(0, 0);
            }

            int operandA = rand() % num;
            int operandB = num - operandA;

            return std::pair<int, int>(operandA, operandB);

        }
        
        /**
         * Spreads out a given number by subtraction
         * 
         * @param num number to spread
         * @return a vector of numbers that can be subtracted to original
         */
        std::pair<int, int> getSpreadSubtraction(int num, int maxOverflow) {

            if(num == 0) {
                int operand = rand() % maxOverflow;
                return std::pair<int, int>(operand, operand);
            }
            
            int operandA = rand() % maxOverflow + (num + 1);
            int operandB = num + operandA;

            return std::pair<int, int>(operandB, operandA);

        }

        /**
         * Spreads out a given number by XOR
         * 
         * @param num number to spread
         * @return a vector of numbers that can be XOR'd to original
         */
        std::pair<int, int> getSpreadXOR(int num, int maxOverflow) {

            if(num == 0) {
                int operand = rand() % maxOverflow;
                return std::pair<int, int>(operand, operand);
            }

            int operandA = rand() % maxOverflow;
            int operandB = num ^ operandA;

            return std::pair<int, int>(operandA, operandB);

        }

    }

    std::string textObfuscate(std::string message) {
        srand(time(NULL));

        std::string obfuscated = message;

        return getWeirdArithmetic(10);
    }

}