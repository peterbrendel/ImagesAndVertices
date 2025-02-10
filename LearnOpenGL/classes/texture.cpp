#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string path) {
    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char* data;
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data) {
        std::cout << "Failed to load texture from " << path << std::endl;
        stbi_image_free(data);
        return;
    }

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + (channels == 4), width, height, 0, GL_RGB + (channels == 4), GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::active(int index) {
    //assert(index >= 0 && index < 16);

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

