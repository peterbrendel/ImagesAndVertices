#include <mouse.hpp>

std::vector<Mouse*> instances;

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
            instance->locked = (action != GLFW_RELEASE);
        }
    }
}

CursorMovement Mouse::getMovement() {
    CursorMovement payload = {
        x, y,
        x - lastX, y - lastY,
        locked
    };

    lastX = x;
    lastY = y;

    return payload;
}
