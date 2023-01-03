#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class Utils {
public:
    static std::string readFile(const char* filePath);
};

#endif
