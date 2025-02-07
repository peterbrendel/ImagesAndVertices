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

    return succeeded(shaders[shaderType], GL_COMPILE_STATUS);
}

unsigned int ShaderManager::getProgram() {
    if (ready) return shaderProgram;
        
    shaderProgram = glCreateProgram();
    for (auto shader : shaders) {
        glAttachShader(shaderProgram, shader.second);
    }

    glLinkProgram(shaderProgram);

    if (succeeded(shaderProgram, GL_LINK_STATUS)) deleteSources();

    ready = true;

    return shaderProgram;
}

int ShaderManager::succeeded(unsigned int id, GLenum query) {
    int success;
    char infoLog[512];

    glGetProgramiv(id, query, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ShaderManager error:\n" << infoLog << std::endl;
    }

    return success;
}

void ShaderManager::deleteSources() {
    shaderSources.clear();
    shaders.clear();
}
