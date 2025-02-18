#pragma once
#include <camera.hpp>

extern float deltaTime;

Camera::Camera(glm::vec3 position) : position(position) {
}

void Camera::update() {
    int forward  =  keyboard.getKey(GLFW_KEY_W);
    int backward = -keyboard.getKey(GLFW_KEY_S);
    int left     = -keyboard.getKey(GLFW_KEY_A);
    int right    =  keyboard.getKey(GLFW_KEY_D);
    int cup      =  keyboard.getKey(GLFW_KEY_SPACE);
    int down     = -keyboard.getKey(GLFW_KEY_LEFT_CONTROL);

    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
    float speed = 2.5f;

    direction += speed * (forward + backward) * front;
    direction += speed * (left + right) * glm::normalize(glm::cross(front, up));
    direction += speed * (cup + down) * up;

    position += direction * deltaTime;
}

glm::mat4 Camera::view() {
    update();

    return glm::lookAt(position, position + front, up);
}
