#pragma once

#include <map>
#include <string>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderManager
{
    unsigned int shaderProgram = 0;
    std::map<GLenum, unsigned int> shaders;
    std::map<GLenum, std::string> shaderSources;

private:
    bool ready = false;

public:
    ShaderManager() { }
    int loadShader(std::string, GLenum);
    unsigned int program();

private:
    int compilingSucceeded(unsigned int);
    int linkingSucceeded(unsigned int);
    void deleteSources();
};
