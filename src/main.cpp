#include <iostream>
#include <string>

#include "args/parseArgs.hpp"
#include "obf/textObfuscate.hpp"

std::string getArgString(int argc, char** argv) {
    std::string args = "";

    for(int i = 1; i < argc; i++) {
        args += argv[i];
        if(i < argc - 1) args += " ";
    }

    return args;
}

int main(int argc, char** argv) {

    std::string args = getArgString(argc, argv);

    arg::flags options = arg::parse(args);

    std::string helpDialog = 
            "G2 - An obfuscated C message generator\n"
            "\n"
            "USAGE: G2 [OPTIONS] [TEXT]\n"
            "\n"
            "Options:\n"
            "--help, -h\n"
            "   show this help text and exit\n"
            "--text, -t\n"
            "   text to encode\n"
            "--filename, -o\n"
            "   (default out.c) name of output c file\n"
            "\n"
            "Copyright 2019 Jack Hance";


    if(options.error) std::cout << "ERROR : " << options.errorText << std::endl;
    if(options.helpSet || argc < 2 || options.error) {
        std::cout << helpDialog << std::endl;
        return 0;
    }

    if(options.textSet) {
        std::cout << obf::textObfuscate(options.text) << std::endl;
    }

}