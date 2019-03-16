#ifndef PARSE_ARGS_HPP
#define PARSE_ARGS_HPP

#include <string>
#include <vector>
#include <functional>
#include <map>

namespace arg {
    enum inputFormat {
        IMAGE,
        TEXT
    };

    struct flags {
        bool helpSet = false;
        
        bool textSet = false;
        std::string text = "";

        bool typeSet = false;
        inputFormat type = TEXT;

        bool filenameSet = false;
        std::string filename = "out.c";

        bool error = false;
        std::string errorText = "";
    };

    // private namespace
    namespace {

        // flag parse funcs
        void flagParseHelp(std::string flagText, std::string content, struct flags* flagPool );
        void flagParseText(std::string flagText, std::string content, struct flags* flagPool );
        void flagParseType(std::string flagText, std::string content, struct flags* flagPool );
        void flagParseFilename(std::string flagText, std::string content, struct flags* flagPool );

        // flag parse func map
        std::map<std::string, void(*)(std::string, std::string, struct flags*)> flagFuncs;

        // split helper function
        std::vector<std::string> split(std::string str, char delim);

        // vector map helper function
        template<class T, typename F> std::vector<T> vectorMap(std::vector<T> arr, F func);

        // string to lower helper function
        std::string toLower(std::string str);
    };

    flags parse(std::string rawArgs);
};   

#endif // !PARSE_ARGS_HPP