#pragma once

#include <map>
#include <string>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int m_shaderProgram = 0;

    Shader(std::string, std::string);
    void use();

private:
    std::string loadShader(std::string, GLenum, unsigned int*);
    void link(unsigned int, unsigned int);
    void logCompilingError(unsigned int);
    void logLinkingError(unsigned int);
};
