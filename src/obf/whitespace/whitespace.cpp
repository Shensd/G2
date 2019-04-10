#include "whitespace.hpp"

namespace obf {

    // private namespace
    namespace {
        std::string replace(std::string str, std::string original, std::string replacement, int start) {
            if(start < 0) start = 0;

            int position = str.find(original, start);

            while(position != std::string::npos) {
                str.insert(position + 1, replacement);
                str.erase(position, 1);

                position = str.find(original, position + replacement.size());
            }

            return str;
        }
    }

    /**
     * Randomize the whitespace of a given string, converts spaces, tabs, and newlines
     * into random mixes of eachother 
     * 
     * @param str string to randomize the whitespace of
     * @param intensity how intense to make the randomization
     * @return a string with much worse whitespace
     */
    std::string randomizeWhitespace(std::string str, int intensity) {
        if(intensity < 1) intensity = 1;

        std::string whitespaces[] = {" ", "\t", "\n"};

        for(int i = 0; i < intensity; i++) {
            int pos = rand() % str.size();

            str = replace(
                str, 
                whitespaces[rand() % 3], 
                whitespaces[rand() % 3], 
                pos
            );
        }

        return str;
    }

}