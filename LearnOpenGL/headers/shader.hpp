#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Shader
{
public:
    unsigned int m_shaderProgram = 0;

    Shader(std::string, std::string);
    void use() const;
    void setUniform(std::string name, float value) const;
    void setUniform(std::string name, int value) const;
    void setUniform(std::string name, glm::vec3 value) const;
    void setUniform(std::string name, glm::mat4 value) const;
    void setUniform(std::string name, glm::mat3 value) const;

private:
    std::string loadShader(std::string, GLenum, unsigned int*);
    void link(unsigned int, unsigned int);
    void logCompilingError(unsigned int);
    void logLinkingError(unsigned int);
};
