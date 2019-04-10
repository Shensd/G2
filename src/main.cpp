#include <iostream>
#include <fstream>
#include <string>

#include "args/parseArgs.hpp"
#include "obf/textObfuscate.hpp"
#include "obf/whitespace/whitespace.hpp"

std::vector<std::string> getArgString(int argc, char** argv) {
    std::vector<std::string> args;

    for(int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }

    return args;
}

int main(int argc, char** argv) {
    std::vector<std::string> args = getArgString(argc, argv);

    arg::flags options = arg::parse(args);

    // TODO 
    // Add obfuscation types (whitespace, equations)
    // Add ability to obfuscate exisiting c programs
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
            "   (use - for stdout) name of output c file\n"
            "--intensity, -i\n"
            "   numeric value to determine how intense the obfuscation should be\n"
            "--whitespace, -w\n"
            "   set to randomize whitespace\n"
            "\n"
            "Copyright 2019 Jack Hance";


    if(options.error) std::cout << "ERROR : " << options.errorText << std::endl;
    if(options.helpSet || argc < 2 || options.error) {
        std::cout << helpDialog << std::endl;
        return 0;
    }

    if(options.textSet) {
        std::string obfuscated = obf::textObfuscate(options.text, options.intensity);

        if(options.whitespaceSet) {
            obfuscated = obf::randomizeWhitespace(obfuscated, 50);
        }

        if(options.filenameSet) {
            if(options.filename == "-") {
                std::cout << obfuscated << std::endl;
            } else {
                std::ofstream out(options.filename.c_str());
                out << obfuscated;
                out << "\n";
                out.close();
            }
        } else {
            std::cout << obfuscated << std::endl;
        }

    }

}