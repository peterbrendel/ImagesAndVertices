#pragma once
#include <keyboard.hpp>
#include <mouse.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace Core {
    class Camera
    {
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        float pitch = 0.0f, yaw = -90.0f;
        float speed = 2.5f;
        float sensitivity = 0.2f;
        float aspectRatio;

        Keyboard keyboard = Keyboard({ GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL });
        Mouse mouse = Mouse();

        void update();
    public:

        Camera(glm::vec3 position, float aspecRatio);

        glm::mat4 view();
        glm::mat4 projection() const;
    };
}
