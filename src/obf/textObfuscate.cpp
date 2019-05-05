#include "textObfuscate.hpp"

namespace obf {

    // private namespace
    namespace _helper {

        /**
         * Traverse a tree of ArithmeticTreeMembers eulers tour style and return
         * the intepreted string
         * 
         * @param tree tree to travers
         * @param position starting position to traverse from
         * @return string of traversed tree
         */
        std::string EulersTourTreeTraverse(Tree<ArithmeticTreeMember>* tree, Position<ArithmeticTreeMember>* position) {

            // TODO 
            // CHAR ARITHMETIC
            // MOVE FUNC TO OWN CLASS

            std::string tour = "";

            if(tree->getLeft(position) != nullptr) {
                tour += "(" + EulersTourTreeTraverse(tree, tree->getLeft(position));
            }

            ArithmeticTreeMember temp = position->getElement();
            if(temp.isOperator) {
                tour += " ";
                tour += ((char) temp.value);
                tour += " ";
            } else {
                tour += " " + std::to_string(temp.value) + " ";
                //tour += std::to_string(temp.value);
            }

            if(tree->getRight(position) != nullptr) {
                tour += EulersTourTreeTraverse(tree, tree->getRight(position)) + ")";
            }

            return tour;
        }

        /**
         * Genreate a random equation tree for a given number
         * 
         * @param num number to create equation for
         * @param maxOverflow overflow for individual spread functions
         * @return a tree of ArithemeticTreeMembers describing an equation for the number
         */
        Tree<ArithmeticTreeMember>* randomBreak(int num, int maxOverflow) {

            int choice = rand() % 5;
            
            std::pair<int, int> p;
            ArithmeticTreeMember root;
            root.isOperator = true;
            switch(choice) {
                case 0:
                    root.value = OPERATOR::ADD;
                    p = getSpreadAddition(num);
                    break;
                case 1:
                    root.value = OPERATOR::SUBTRACT;
                    p = getSpreadSubtraction(num, maxOverflow);
                    break;
                case 2:
                    root.value = OPERATOR::MULTIPLY;
                    p = getSpreadMultiplication(num);
                    break;
                case 3:
                    root.value = OPERATOR::DIVIDE;
                    p = getSpreadDivision(num, maxOverflow);
                    break;
                default:
                case 4:
                    root.value = OPERATOR::XOR;
                    p = getSpreadXOR(num, maxOverflow);
            }

            ArithmeticTreeMember left(false, p.first);
            ArithmeticTreeMember right(false, p.second);

            Tree<ArithmeticTreeMember> *equationTree = new Tree<ArithmeticTreeMember>(root);
            equationTree->setLeft(equationTree->getRoot(), left);
            equationTree->setRight(equationTree->getRoot(), right);

            return equationTree;
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
         * Get a random number node from a given starting point
         * 
         * @param tree tree to grab random position from
         * @param startPoint position on tree to start search from
         * @return random position on tree of type number
         */
        Position<ArithmeticTreeMember>* getRandomNumberNode(Tree<ArithmeticTreeMember>* tree, Position<ArithmeticTreeMember>* startPoint) {
            int side = (rand() % 2 == 0) ? SIDE::LEFT : SIDE::RIGHT;

            Position<ArithmeticTreeMember>* temp;
            // pick from left side
            if(side == SIDE::LEFT) {
                temp = tree->getLeft(startPoint);
            // pick from right side
            } else {
                temp = tree->getRight(startPoint);
            }

            if(!temp->getElement().isOperator) {
                return temp;
            } else {
                return getRandomNumberNode(tree, temp);
            }
        }

        /**
         * Convert an int to a string of a given number of arithmetic expressions
         * 
         * @param num number to convert
         * @param rounds of splitting to perform on numbers
         * @return string of odd arithemetic 
         */
        std::string getWeirdArithmetic(int num, int rounds) {
            if(rounds < 1) rounds = 1;

            Tree<ArithmeticTreeMember> *equationTree = randomBreak(num, 200);

            for(int i = 0; i < rounds; i++) {
                
                Position<ArithmeticTreeMember>* decompose = getRandomNumberNode(equationTree, equationTree->getRoot());

                equationTree->setTree(
                    decompose, 
                    randomBreak(decompose->getElement().value, 200)
                );

            }

            return EulersTourTreeTraverse(equationTree, equationTree->getRoot());
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
         * @return a pair of numbers that can be added up to original
         */
        std::pair<int, int> getSpreadAddition(int num) {
            
            if(num == 0) {
                return std::pair<int, int>(0, 0);
            }

            int operandA = (rand() % num) + 1;
            int operandB = num - operandA;

            return std::pair<int, int>(operandA, operandB);

        }
        
        /**
         * Spreads out a given number by subtraction
         * 
         * @param num number to spread
         * @return a pair of numbers that can be subtracted to original
         */
        std::pair<int, int> getSpreadSubtraction(int num, int maxOverflow) {

            if(num == 0) {
                int operand = rand() % maxOverflow;
                return std::pair<int, int>(operand, operand);
            }
            
            int operandA = rand() % maxOverflow + (num);
            int operandB = num + operandA;

            return std::pair<int, int>(operandB, operandA);

        }

        /**
         * Spreads out a given number by multiplication
         * 
         * @param num number to spread
         * @return a pair of numbers that can be multiplied to get the original
         */
        std::pair<int, int> getSpreadMultiplication(int num) {
            return std::pair<int, int>(1, num);
        }

        /**
         * Spreads out a given number by division
         * 
         * @param num number to spread
         * @param maxOverflow cap for expansion
         * @return a pair of numbers that can be divided to get the original
         */
        std::pair<int, int> getSpreadDivision(int num, int maxOverflow) {
            if(num == 0) {
                int operand = (rand() % maxOverflow) + 1;
                return std::pair<int, int>(0, operand);
            }

            int operandB = (rand() % maxOverflow) + 1;
            int operandA = num * operandB;

            return std::pair<int, int>(operandA, operandB);
        }

        /**
         * Spreads out a given number by XOR
         * 
         * @param num number to spread
         * @return a pair of numbers that can be XOR'd to original
         */
        std::pair<int, int> getSpreadXOR(int num, int maxOverflow) {

            if(num == 0) {
                int operand = (rand() % maxOverflow) + 1;
                return std::pair<int, int>(operand, operand);
            }

            int operandA = (rand() % maxOverflow) + 1;
            int operandB = num ^ operandA;

            return std::pair<int, int>(operandA, operandB);

        }

    }

    /**
     * Obfuscate a given string into a string of a C char array
     * 
     * @param message message to encode
     * @return string of C char array syntax
     */
    std::string textObfuscate(std::string message, int intensity) {
        srand(time(NULL));

        if(intensity < 1) intensity = 1;

        std::string obfuscated = "#include <stdio.h>\nint main(){char msg[] = {";

        std::vector<int> asciis = _helper::getAsciiValues(message);

        for(int i = 0; i < asciis.size(); i++) {
            obfuscated += _helper::getWeirdArithmetic(asciis.at(i), intensity);
            if(i < asciis.size() - 1) {
                obfuscated += ",";
            }
        }

        obfuscated += "};for(int i = 0; i < " + std::to_string(message.size()) + "; i++) {printf(\"%c\", msg[i]);}}";

        return obfuscated;
    }

}