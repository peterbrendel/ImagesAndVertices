#include "shader.hpp"

Shader::Shader(std::string vertPath, std::string fragPath) {
    unsigned int vertShader, fragShader;
    std::string vertSource = loadShader(vertPath, GL_VERTEX_SHADER, &vertShader);
    std::string fragSource = loadShader(fragPath, GL_FRAGMENT_SHADER, &fragShader);

    link(vertShader, fragShader);
}

std::string Shader::loadShader(std::string path, GLenum shaderType, unsigned int* source) {
    std::ifstream ShaderStream(path);
    std::stringstream buffer;
    buffer << ShaderStream.rdbuf();

    *source = glCreateShader(shaderType);

    std::string shaderString = buffer.str();
    const char *sourcePtr = shaderString.c_str();
    glShaderSource(*source, 1, &sourcePtr, NULL);
    glCompileShader(*source);

    logCompilingError(*source);

    return shaderString;
}

void Shader::link(unsigned int vert, unsigned int frag) {
    m_shaderProgram = glCreateProgram();

    glAttachShader(m_shaderProgram, vert);
    glAttachShader(m_shaderProgram, frag);
   
    glLinkProgram(m_shaderProgram);

    logLinkingError(m_shaderProgram);
}

void Shader::logCompilingError(unsigned int id) {
    int success;
    char infoLog[512];

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
}

void Shader::logLinkingError(unsigned int id) {
    int success;
    char infoLog[512];

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
}

void Shader::use() {
    glUseProgram(m_shaderProgram);
}
