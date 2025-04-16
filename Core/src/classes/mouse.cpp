#include <mouse.hpp>

using namespace Core;

std::vector<Mouse*> Mouse::instances;

Mouse::Mouse() {
    instances.push_back(this);
}

Mouse::~Mouse() {
    instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end());
}

void Mouse::setup(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, Mouse::posCallback);
    glfwSetMouseButtonCallback(window, Mouse::clickCallback);
}

void Mouse::posCallback(GLFWwindow* window, double xPos, double yPos) {
    for (Mouse* instance : instances) {
        instance->x = (float) xPos;
        instance->y = (float) yPos;
    }
}

void Mouse::clickCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_2) {
        for (Mouse* instance : instances) {
            bool locked = (action != GLFW_RELEASE);
            instance->locked = locked;
            if (!locked) {
                instance->x = 0.0f;
                instance->y = 0.0f;
                instance->lastX = 0.0f;
                instance->lastY = 0.0f;
            }
        }
        auto mode = (action != GLFW_RELEASE) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
        glfwSetInputMode(window, GLFW_CURSOR, mode);
    }
}

CursorMovement Mouse::getMovement() {
    CursorMovement payload = {
        x, y,
        x - lastX, lastY - y,
        locked
    };

    lastX = x;
    lastY = y;

    return payload;
}
