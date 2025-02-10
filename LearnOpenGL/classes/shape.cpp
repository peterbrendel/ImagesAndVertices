#include "shape.hpp"
#include <glad/glad.h>
#include <iostream>
#include <gl/GL.h>

Shape::Shape(std::vector<float>&& vertexData, std::vector<int>&& indices)
    : m_vertexData(std::move(vertexData)),
      m_indices(std::move(indices)) {
    // one vertex has only 3 positional data

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(int), m_indices.data(), GL_STATIC_DRAW);

    // positional data
    m_attribs += 3;

    setBuffers();
}

void Shape::setBuffers() {

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_attribs * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    if (m_texture != nullptr) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, m_attribs * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    glBindVertexArray(0);
}

void Shape::draw() {
    if (m_texture != nullptr) {
        m_texture->active(0);
    }

    glBindVertexArray(m_VAO);

    glDrawElements(GL_TRIANGLES, m_indices.size() * sizeof(int), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Shape::setTexture(std::shared_ptr<Texture> texture_ptr) {
    m_texture = texture_ptr;

    std::vector<float> updatedVertexData;

    for (int i = 0; i < m_vertexData.size(); i += 3) {
        updatedVertexData.push_back(m_vertexData[i]);
        updatedVertexData.push_back(m_vertexData[i+1]);
        updatedVertexData.push_back(m_vertexData[i+2]);

        // calculate uv
        updatedVertexData.push_back((m_vertexData[i] + 1.0f) / 2.0f);
        updatedVertexData.push_back((m_vertexData[i+1] + 1.0f) / 2.0f);
    }

    m_vertexData.clear();
    m_vertexData = std::move(updatedVertexData);

    // texture uv data
    m_attribs += 2;

    setBuffers();
}
