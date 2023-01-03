#include "Shader.h"
#include "Utils.h"

#include <iostream>
using namespace std;

Shader::Shader(const char* vertexPath, const char* fragPath) {
    const string vertexShaderStr = Utils::readFile(vertexPath);
    const string fragShaderStr = Utils::readFile(fragPath);
    const char* vertexShaderSource = vertexShaderStr.c_str();
    const char* fragShaderSource = fragShaderStr.c_str();

    cout << "Compiling vertex shader" << endl;
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return;
    }

    cout << "Compiling fragment shader" << endl;
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return;
    }

    std::cout << "Linking program" << std::endl;
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
        return;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec4f(const std::string& name, float v0, float v1, float v2, float v3) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3);
}
