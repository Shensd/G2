#include <iostream>
#include <fstream>
#include <string>

#include "args/parseArgs.hpp"
#include "obf/textObfuscate.hpp"
#include "obf/whitespace/whitespace.hpp"
#include "files/fileHandler.hpp"

#define DEFAULT_INTENSITY 50

std::vector<std::string> getArgString(int argc, char** argv) {
    std::vector<std::string> args;

    for(int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }

    return args;
}

void printHelpText(void) {
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
            "--in, -i\n"
            "   name of input file\n"
            "--out, -o\n"
            "   (use - for stdout) name of output c file\n"
            "--intensity\n"
            "   numeric value to determine how intense the obfuscation should be\n"
            "--whitespace, -w\n"
            "   set to randomize whitespace\n"
            "\n"
            "Copyright 2019 Jack Hance";

    std::cout << helpDialog << std::endl;
}

int main(int argc, char** argv) {
    std::vector<std::string> args = getArgString(argc, argv);

    arg::flags options = arg::parse(args);

    if(options.error) std::cout << "ERROR : " << options.errorText << std::endl;
    if(options.helpSet || argc < 2 || options.error) {
        printHelpText();
        return 0;
    }

    std::string content;

    // use of both file input and text input caught during arg parsing
    if(options.textSet) content = options.text;
    if(options.inFilenameSet) {
        std::ifstream input(options.inFilename);
        content = files::getFileContents(&input);
        input.close();
    }

    std::string obfuscated = obf::textObfuscate(content, options.intensity);

    if(options.whitespaceSet) {
        int intensity = DEFAULT_INTENSITY;
        if(options.intensitySet) intensity = options.intensity;
        obfuscated = obf::randomizeWhitespace(obfuscated, intensity);
    }

    if(options.outFilenameSet) {
        if(options.outFilename == "-") {
            std::cout << obfuscated << std::endl;
        } else {
            std::ofstream out(options.outFilename.c_str());
            out << obfuscated;
            out << "\n";
            out.close();
        }
    } else {
        std::cout << obfuscated << std::endl;
    }

}