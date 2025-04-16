#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <shader.hpp>
#include <spdlog/spdlog.h>

using namespace Core;

std::map<std::string, unsigned int> Shader::m_shaderCache;

Shader::Shader(const std::string& vertPath, const std::string& fragPath) {
    unsigned int vertShader, fragShader;

    vertShader = loadShader(vertPath, GL_VERTEX_SHADER);
    fragShader = loadShader(fragPath, GL_FRAGMENT_SHADER);

    link(vertShader, fragShader);
}

unsigned int Shader::loadShader(const std::string& path, GLenum shaderType) {
    spdlog::debug(path);
    if (m_shaderCache.find(path) != m_shaderCache.end()) {
        return m_shaderCache[path];
    }
    
    std::ifstream ShaderStream(path);
    std::stringstream buffer;
    buffer << ShaderStream.rdbuf();

    unsigned int source = glCreateShader(shaderType);

    std::string shaderString = buffer.str();
    const char *sourcePtr = shaderString.c_str();

    glShaderSource(source, 1, &sourcePtr, NULL);
    glCompileShader(source);

    logCompilingError(source); // not sure yet if this should stop the program

    return m_shaderCache[path] = source;
}

void Shader::link(unsigned int vert, unsigned int frag) {
    m_shaderProgram = glCreateProgram();

    glAttachShader(m_shaderProgram, vert);
    glAttachShader(m_shaderProgram, frag);
   
    glLinkProgram(m_shaderProgram);

    logLinkingError(); // not sure yet if this should stop the program
}

void Shader::logCompilingError(unsigned int id) const {
    int success;

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512] = {0};
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        spdlog::debug(infoLog);
    }
}

void Shader::logLinkingError() const {
    int success;

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[512] = {0};
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        spdlog::debug(infoLog);
    }
}

void Shader::use() const {
    glUseProgram(m_shaderProgram);
}

GLint Shader::getUniform(const std::string& name) const {
    return glGetUniformLocation(m_shaderProgram, name.c_str());
}

void Shader::setUniform(const std::string& name, float value) const {
    glUniform1f(getUniform(name), value);
}

void Shader::setUniform(const std::string& name, int value) const {
    glUniform1i(getUniform(name), value);
}

void Shader::setUniform(const std::string& name, glm::vec3 value) const {
    glUniform3fv(getUniform(name), 1, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, glm::mat4 value) const {
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, glm::mat3 value) const {
    glUniformMatrix3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(value));
}
