#pragma once

#include <memory>
#include <vector>

#include <camera.hpp>
#include <shader.hpp>
#include <entity.hpp>

class Scene {
private:
    std::unique_ptr<Camera> m_camera;
    std::vector<std::shared_ptr<Entity>> m_entities;

public:
    Scene() {}

    void setCamera(std::unique_ptr<Camera> camera) {
        m_camera = std::move(camera);
    }

    void add(std::shared_ptr<Entity> entity) {
        m_entities.push_back(entity);
    }

    void remove(unsigned int index) {
        if (index < m_entities.size()) {
            m_entities.erase(m_entities.begin() + index);
        }
    }

    void update() {
        m_camera->update();

        for (auto& entity : m_entities) {
            entity->update(); // no-op
            // todo: allow each entity to have its own update logic (scripting?)
        }
    }

    void draw() {
        glm::mat4 viewMatrix = m_camera->view();
        glm::mat4 projectionMatrix = m_camera->projection();

        for (const auto& entity : m_entities) {
            std::cout << entity->id << std::endl;
            entity->useShader(viewMatrix, projectionMatrix);
            entity->draw();
        }
    }
};
