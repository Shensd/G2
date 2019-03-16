#include "parseArgs.hpp"

namespace arg {

    // private namespace
    namespace {

        /**
         * Help flag parser, sets the help flag to true
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseHelp(std::string flagText, std::string content, struct flags* flagPool) {
            flagPool->helpSet = true;
        }

        /**
         * Text flag parser, if content is given then text is set, error
         * flag set if no content is given
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseText(std::string flagText, std::string content, struct flags* flagPool) {
            if(content != "") {
                flagPool->textSet = true;
                flagPool->text = content;
            } else {
                flagPool->error = true;
                flagPool->errorText = "Text flag was set but no text given";
            }
        }

        /**
         * Type flag parser, given content is converted into a type, error flag
         * set if given content cannot be translated into a input type
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseType(std::string flagText, std::string content, struct flags* flagPool) {
            if(content == "") {
                flagPool->error = true;
                flagPool->errorText = "Type flag was set but no text given";
                return;
            }

            std::string cl = toLower(content);

            if(cl == "text") {
                flagPool->typeSet = true;
                flagPool->type = TEXT;
            } else if(cl == "image") {
                flagPool->typeSet = true;
                flagPool->type = IMAGE;
            } else {
                flagPool->error = true;
                flagPool->errorText = "Type flag set but invalid type " + content + " given";
            }
        }

        /**
         * Filename flag parser, given content is converted into a type, error flag
         * set if given content cannot be translated into a input type
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseFilename(std::string flagText, std::string content, struct flags* flagPool ) {
            if(content == "") {
                flagPool->error = true;
                flagPool->errorText = "File name flag set but not file name given";
                return;
            }

            flagPool->filenameSet = true;
            flagPool->filename = content;
        }

        /**
         * splits a string by a given delim and returns the result in a vector
         * 
         * @param str string to be split
         * @param delim delimiter to split the string by
         * @returns vector of split string
         */
        std::vector<std::string> split(std::string str, char delim=' ') {
            std::vector<std::string> tokens;

            std::string temp = "";
            for(int i = 0; i < str.length(); i++) {
                
                if(str[i] == delim) {
                    tokens.push_back(temp);

                    temp = "";
                } else if(i == str.length() - 1) {
                    temp += str[i];

                    tokens.push_back(temp);
                } else {
                    temp += str[i];
                }
            }

            return tokens;
        }
        
        /**
         * Performs a given function on each item in a vector
         * 
         * @param arr vector to perform function on
         * @param func function to perform on each item
         */
        template<class T, typename F> std::vector<T> vectorMap(std::vector<T> arr, F func) {
            std::vector<T> tempArr;
            for(T a : arr) {
                tempArr.push_back(func(a));
            }
            return tempArr;
        }

        /**
         * Convert a string to lowercase
         * 
         * @param str string to convert
         * @return string in lowercase form
         */
        std::string toLower(std::string str) {
            for(int i = 0; i < str.size(); i++) {
                str[i] = std::tolower(str[i]);
            }
            return str;
        }
    }

    /**
     * Parses a given command line string and returns a flags structure of
     * set flags, if the `errorSet` is true then there was an error during 
     * parsing, the error message is under `error`
     * 
     * @param rawArgs command line arg string
     * @return a flag structure of set args
     */
    flags parse(std::string rawArgs) {
        struct flags parsedFlags;

        // create flag parse map
        flagFuncs = {
            {"help", &flagParseHelp},
            {"h", &flagParseHelp},

            {"text", &flagParseText},
            {"t", &flagParseText},

            {"type", &flagParseType},
            {"y", &flagParseType},

            {"filename", &flagParseFilename},
            {"o", &flagParseFilename}
        };

        // split our given command string into pieces 
        std::vector<std::string> spl = split(rawArgs);

        for(int i = 0; i < spl.size(); i++) {
            std::string s = spl[i];

            // is tack flag, pull flag text
            if(s[0] == '-') {
                std::vector<std::string> parts = split(s, '-');
                std::string flagText = parts[parts.size() - 1];

                auto flagFunc = flagFuncs.find(flagText)->second;
                
                // only call flag parsed func if an associated one is found
                if(flagFunc != nullptr) {
                    std::string content;
                    if(i < spl.size() - 1) {
                        content = spl[i + 1];
                    } else {
                        content = "";
                    }

                    flagFunc(flagText, content, &parsedFlags);
                    
                    // increment i to skip next token since it was used by 
                    // the current flag
                    i++;
                } else {
                    parsedFlags.error = true;
                    parsedFlags.errorText = "Unknown flag " + s;
                }
            // given token is not a tack flag, but if text is not set
            // then it will be set by default
            } else {
                if(!parsedFlags.textSet) {
                    parsedFlags.textSet = true;
                    parsedFlags.text = s;
                }
            }

            // check if the error flag was set at any point and immediately
            // exit if it was

            if(parsedFlags.error) break;
        }

        return parsedFlags;
    }

}