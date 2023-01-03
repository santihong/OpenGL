#include "Utils.h"
#include <iostream>
#include <fstream>
using namespace std;

string Utils::readFile(const char* filePath) {
    std::string content;
    std::ifstream fs(filePath, std::ios::in);

    if (!fs.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fs.eof()) {
        getline(fs, line);
        content.append(line + "\n");
    }

    fs.close();
    return content;
}
