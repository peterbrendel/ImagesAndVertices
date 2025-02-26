#include <camera.hpp>

extern float deltaTime;

Camera::Camera(std::shared_ptr<Shader> shader, glm::vec2 resolution, float fov) : m_resolution(resolution), m_fov(fov), Entity(shader) {}
Camera::Camera(std::shared_ptr<Shader> shader, glm::vec2 resolution, float fov, glm::vec3 position) : m_resolution(resolution), m_fov(fov), Entity(shader, position) {}

void Camera::update() {
    CursorMovement drag = m_mouse.getMovement();

    if (drag.locked) {
        m_yaw += drag.offsetX * m_sensitivity;
        m_pitch += drag.offsetY * m_sensitivity;

        if (m_pitch > 89.0f) m_pitch = 89.0f;
        if (m_pitch < -89.0f) m_pitch = -89.0f;

        glm::vec3 camDirection = {
            cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
            sin(glm::radians(m_pitch)),
            sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))
        };

        m_front = glm::normalize(camDirection);
    }

    int forward  =  m_keyboard.getKey(GLFW_KEY_W);
    int backward = -m_keyboard.getKey(GLFW_KEY_S);
    int left     = -m_keyboard.getKey(GLFW_KEY_A);
    int right    =  m_keyboard.getKey(GLFW_KEY_D);
    int cup      =  m_keyboard.getKey(GLFW_KEY_SPACE);
    int down     = -m_keyboard.getKey(GLFW_KEY_LEFT_CONTROL);

    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

    direction += m_speed * (forward + backward) * m_front;
    direction += m_speed * (left + right) * glm::normalize(glm::cross(m_front, m_up));
    direction += m_speed * (cup + down) * m_up;

    m_position += direction * deltaTime;
}

void Camera::update(glm::vec3)
{
}

void Camera::draw() const
{
}

glm::mat4 Camera::view() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::projection() const {
    return glm::perspective(glm::radians(m_fov), m_resolution.x / m_resolution.y, 0.1f, 100.0f);
}
