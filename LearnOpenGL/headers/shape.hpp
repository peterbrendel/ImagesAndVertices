#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include <texture.hpp>

class Shape
{
    std::vector<float> m_vertexData;
    std::vector<int> m_indices;
    std::shared_ptr<Texture> m_texture;

    unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;
    unsigned int m_attribs = 0;

    void setBuffers();

public:
    Shape(std::vector<float>&& vertexData, std::vector<int>&& indices);
    void draw();
    void setTexture(std::shared_ptr<Texture> texture_ptr);
};
