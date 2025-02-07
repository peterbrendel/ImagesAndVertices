#include "shaderManager.hpp"

int ShaderManager::loadShader(std::string path, GLenum shaderType) {
    std::ifstream ShaderStream(path);
    std::stringstream buffer;
    buffer << ShaderStream.rdbuf();

    shaderSources.insert({ shaderType, buffer.str() });
    shaders.insert({ shaderType, glCreateShader(shaderType) });

    const char *sourcePtr = shaderSources[shaderType].c_str();
    glShaderSource(shaders[shaderType], 1, &sourcePtr, NULL);
    glCompileShader(shaders[shaderType]);

    return compilingSucceeded(shaders[shaderType]);
}

unsigned int ShaderManager::program() {
    if (ready) return shaderProgram;
        
    shaderProgram = glCreateProgram();
    for (auto shader : shaders) {
        glAttachShader(shaderProgram, shader.second);
    }

    glLinkProgram(shaderProgram);

    if (linkingSucceeded(shaderProgram)) deleteSources();

    ready = true;

    return shaderProgram;
}

int ShaderManager::compilingSucceeded(unsigned int id) {
    int success;
    char infoLog[512];

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
    }

    return success;
}

int ShaderManager::linkingSucceeded(unsigned int id) {
    int success;
    char infoLog[512];

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
    }

    return success;
}

void ShaderManager::deleteSources() {
    shaderSources.clear();
    shaders.clear();
}
