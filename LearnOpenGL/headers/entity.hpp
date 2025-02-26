#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

#include <shader.hpp>

class Entity {
    static unsigned int entitiesCounter;

protected:
    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_scale    = { 1.0f, 1.0f, 1.0f };

    std::shared_ptr<Shader> m_shaderPtr;

public:
    unsigned int id;
    Entity(std::shared_ptr<Shader> shader);
    Entity(std::shared_ptr<Shader> shader, glm::vec3 position);

    const glm::vec3& position() const;
    const glm::vec3& rotation() const;
    const glm::vec3& scale() const;

    bool operator==(const Entity& other) const;

    virtual void update() = 0;
    virtual void update(glm::vec3 offset) = 0;
    virtual void draw() const = 0;

    void useShader(glm::mat4& viewMatrix, glm::mat4& projectionMatrix) const;
};
