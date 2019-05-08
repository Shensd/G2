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
        void flagParseHelp(std::string flagText, struct flags* flagPool) {
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
            // Text input and file input cannot be used at the same time
            if(flagPool->inFilenameSet) {
                flagPool->error = true;
                flagPool->errorText = "Text input and file input cannot be used at the same time";
                return;
            }

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
         * set if given content cannot be translated into an output filename
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseOutFilename(std::string flagText, std::string content, struct flags* flagPool ) {
            if(content == "") {
                flagPool->error = true;
                flagPool->errorText = "File name flag set but not file name given";
                return;
            }

            flagPool->outFilenameSet = true;
            flagPool->outFilename = content;
        }

        /**
         * Filename flag parser, given content is converted into a type, error flag
         * set if given content cannot be translated into an input filename
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseInFilename(std::string flagText, std::string content, struct flags* flagPool ) {
            // no file name given
            if(content == "") {
                flagPool->error = true;
                flagPool->errorText = "File name flag set but not file name given";
                return;
            }

            std::ifstream temp(content);

            // file doesn't exist
            if(!temp.is_open()) {
                flagPool->error = true;
                flagPool->errorText = "Input file " + content + " not found";
                return;
            }

            // file input and text input cannot be used at the same time
            if(flagPool->textSet) {
                flagPool->error = true;
                flagPool->errorText = "File input and text input cannot be used at the same time";
                return;
            }

            temp.close();

            flagPool->inFilenameSet = true;
            flagPool->inFilename = content;
        }

        /**
         * Set the intensity for text obfuscation
         * 
         * @param flagText text of flag
         * @param content next block of text in commard arg string
         * @param flagPool struct of already set flags
         */
        void flagParseIntensity(std::string flagText, std::string content, struct flags* flagPool ) {
            if(content == "") {
                flagPool->error = true;
                flagPool->errorText = "Intesity flag set but no amount given";
            }

            int intensity = 1;

            try {
                intensity = std::stoi(content);
            } catch(std::exception e) {
                flagPool->error = true;
                flagPool->errorText = "Given itensity is not a valid number";
            }

            flagPool->intensitySet = true;
            flagPool->intensity = intensity;
        }

        /**
         * Set if whitespace randomization should be performed
         * 
         * @param flagText text of flag
         * @param content next block of text in commard arg string
         * @param flagPool struct of already set flags
         */
        void flagParseWhitespace(std::string flagText, struct flags* flagPool) {
            flagPool->whitespaceSet = true;
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

        /**
         * Returns true if the given argument is a tack flag (a primary argument
         * denoted with a tack infront of it, eg --help)
         *
         * @param arg argument to test
         * @return true if tack flag
         */
        bool isTackFlag(std::string arg) {
            return arg[0] == '-';
        }

        /**
         * Get the content of a tack flag (aka, strip leading tacks)
         * 
         * @param arg argument to grab flag content from
         * @return flag content
         */
        std::string getTackFlagContent(std::string arg) {
            std::vector<std::string> parts = split(arg, '-');

            return parts[parts.size() - 1];
        }

        /**
         * Return the content for an argument, or an empty string if there is 
         * none
         * 
         * @param rawArgs arguments to grab content from
         * @param index index of argument to grab content for
         * @return content if found, an empty string otherwise
         */
        std::string getArgArgument(std::vector<std::string> rawArgs, int index) {
            std::string content;
            if(index < rawArgs.size() - 1) {
                content = rawArgs[index + 1];
            } else {
                content = "";
            }

            return content;
        }

        /**
         * Parse a tack flag at a given index and return if next flag needs to 
         * be skipped
         * 
         * @param rawArgs raw arguments to read from
         * @param index current position in argument parsing
         * @param flagPool flag struct to read results into
         * @return true if next flag was eaten
         */
        bool parseTackArg(std::vector<std::string> rawArgs, int index, struct flags* flagPool) {
            std::string currentArg = rawArgs[index];

            std::string flagText = getTackFlagContent(currentArg);

            // check if flag function if it exists in the map
            auto iter = flagFuncs.find(flagText);
            if(iter != flagFuncs.end()) {

                std::string content = getArgArgument(rawArgs, index);

                // now call associated function pointer
                iter->second(flagText, content, flagPool);
                
                return true;
            } else {

                // if a flag that requires content isn't found, try to process
                // as a no content flag
                auto iter = flagFuncsNoContent.find(flagText);

                if(iter != flagFuncsNoContent.end()) {
                    iter->second(flagText, flagPool);
                } else {
                    // that flag doesnt have an entry in the function map
                    flagPool->error = true;
                    flagPool->errorText = "Unknown flag " + currentArg;
                } 
            }

            return false;
        }

        /**
         * Parsed a set of given raw arguments into a flags structure
         * 
         * @param rawArgs raw arguments to parse
         * @param flagPool flags struct to read results into
         */
        void runFlagFuncs(std::vector<std::string> rawArgs, struct flags* flagPool) {

            for(int i = 0; i < rawArgs.size(); i++) {
                std::string currentArg = rawArgs[i];

                // is tack flag, pull flag text
                if(isTackFlag(currentArg)) {
                    bool skipNext = parseTackArg(rawArgs, i, flagPool);

                    if(skipNext) i++;
                // given token is not a tack flag, but if text is not set
                // then it will be set by default
                } else {
                    if(!flagPool->textSet) {
                        flagPool->textSet = true;
                        flagPool->text = currentArg;
                    }
                }

                // check if the error flag was set at any point and immediately
                // exit if it was
                if(flagPool->error) break;
            }
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
    flags parse(std::vector<std::string> rawArgs) {

        // create flag parse map
        flagFuncs = {
            {"text", &flagParseText},
            {"t", &flagParseText},

            {"type", &flagParseType},
            {"y", &flagParseType},

            {"out", &flagParseOutFilename},
            {"o", &flagParseOutFilename},

            {"in", &flagParseInFilename},
            {"i", &flagParseInFilename},

            {"intensity", &flagParseIntensity}
        };

        flagFuncsNoContent = {
            {"help", &flagParseHelp},
            {"h", &flagParseHelp},

            {"whitespace", &flagParseWhitespace},
            {"w", &flagParseWhitespace}
        };

        struct flags parsedFlags;

        runFlagFuncs(rawArgs, &parsedFlags);

        return parsedFlags;
    }

}