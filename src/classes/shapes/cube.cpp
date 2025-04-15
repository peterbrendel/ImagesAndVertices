#include <shapes/cube.hpp>

unsigned int Cube::VBO = 0;

Cube::Cube(glm::vec3 position) {
    m_position = position;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    if (Cube::VBO == 0) {  // Ensure VBO is created only once
        glGenBuffers(1, &Cube::VBO);
        glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Cube::setTexture(std::shared_ptr<Texture> texture) {
    m_texture = texture;

    glBindVertexArray(VAO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Cube::draw() {
    if (m_texture != nullptr) {
        m_texture->active(0);
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
