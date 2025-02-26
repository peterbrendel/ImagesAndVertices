#pragma once

#include <entity.hpp>
#include <keyboard.hpp>
#include <mouse.hpp>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>

class Camera : Entity
{
    glm::vec3 m_target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec2 m_resolution;

    float m_fov;
    float m_pitch = 0.0f, m_yaw = -90.0f;
    float m_speed = 2.5f;
    float m_sensitivity = 0.2f;

    Keyboard m_keyboard = Keyboard({GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL});
    Mouse m_mouse = Mouse();

public:

    Camera(std::shared_ptr<Shader> shader, glm::vec2 resolution, float fov);
    Camera(std::shared_ptr<Shader> shader, glm::vec2 resolution, float fov, glm::vec3 position);

    void update() override;
    void update(glm::vec3) override;
    void draw() const override;

    glm::mat4 view() const;
    glm::mat4 projection() const;
};
