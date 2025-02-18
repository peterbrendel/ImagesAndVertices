#include <keyboard.hpp>
#include <iostream>

std::vector<Keyboard*> Keyboard::instances;

Keyboard::Keyboard(std::vector<int> keySubscription) {
    for (auto key : keySubscription) {
        keys[key] = false;
    }

    instances.push_back(this);
}

Keyboard::~Keyboard() {
    instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end());
}

void Keyboard::setup(GLFWwindow* window) {
    glfwSetKeyCallback(window, Keyboard::callback);
}

void Keyboard::setKey(int key, bool value) {
    auto it = keys.find(key);

    if (it != keys.end()) {
        keys[key] = value;
    }
}

int Keyboard::getKey(int key) {
    auto it = keys.find(key);

    return it != keys.end() ? keys[key] : false;
}

void Keyboard::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_REPEAT) return;

    for (auto keyboard : instances) {
        keyboard->setKey(key, action != GLFW_RELEASE);
    }
}
