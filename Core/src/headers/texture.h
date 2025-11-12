#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Core {
    class Texture
    {
    public:
        unsigned int m_textureId = 0;

        Texture(std::string path);
        void active(int index);
    };
}
