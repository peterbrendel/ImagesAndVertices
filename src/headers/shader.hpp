#pragma once
#include <map>
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

    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void use() const;
    void setUniform(const std::string&, float) const;
    void setUniform(const std::string&, int) const;
    void setUniform(const std::string&, glm::vec3) const;
    void setUniform(const std::string&, glm::mat4) const;
    void setUniform(const std::string&, glm::mat3) const;

private:
    static std::map<std::string, unsigned int> m_shaderCache;

    unsigned int loadShader(const std::string& path, GLenum shaderType);
    void link(unsigned int vertexShaderId, unsigned int fragmentShaderId);
    void logCompilingError(unsigned int shaderId) const;
    void logLinkingError() const;
    GLint getUniform(const std::string& name) const;
};
