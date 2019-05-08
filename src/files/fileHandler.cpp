#include "fileHandler.hpp"

namespace files {


    /**
     * Reads a given input file and returns it's contents as a string
     * 
     * @param file stream to read from
     * @return string of file contents
     */
    std::string getFileContents(std::istream* file) {
        // get length of stream
        file->seekg(0, file->end);
        int length = file->tellg();
        file->seekg(0, file->beg);

        char* buffer = new char[length];

        file->read(buffer, length);

        std::string content(buffer);

        return content;
    }

}