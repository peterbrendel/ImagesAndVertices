#include <entity.hpp>

unsigned int Entity::entitiesCounter = 0;

Entity::Entity(std::shared_ptr<Shader> shader) : m_shaderPtr(shader) {
    id = ++entitiesCounter;
}

Entity::Entity(std::shared_ptr<Shader> shader, glm::vec3 position) : m_shaderPtr(shader), m_position(position) {
    id = ++entitiesCounter;
}

const glm::vec3& Entity::position() const {
    return m_position;
}

const glm::vec3& Entity::rotation() const {
    return m_rotation;
}

const glm::vec3& Entity::scale() const {
    return m_scale;
}

bool Entity::operator==(const Entity& other) const {
    return this->id == other.id;
}

void Entity::useShader(glm::mat4& viewMatrix, glm::mat4& projectionMatrix) const {
    m_shaderPtr->use();

    auto model = glm::translate(glm::mat4(1.0f), m_position);
    model = glm::scale(model, m_scale);
    m_shaderPtr->setUniform("model", model);

    auto normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * model)));
    m_shaderPtr->setUniform("normalMatrix", normalMatrix);

    m_shaderPtr->setUniform("view", viewMatrix);
    m_shaderPtr->setUniform("projection", projectionMatrix);

    m_shaderPtr->setUniform("translation", m_position);
    m_shaderPtr->setUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    m_shaderPtr->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
}
