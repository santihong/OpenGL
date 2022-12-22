#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class Utils {
public:
    static std::string readFile(const char* filePath);
    static GLuint loadShader(const char* vertex_path, const char* fragment_path);
};

#endif
