#include <player_movement.h>

using namespace Core;

PlayerMovement::PlayerMovement(Game& game) : System(game) {
    keyboard = new Keyboard({ GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_SPACE });
}

PlayerMovement::~PlayerMovement() {
    delete keyboard;
}

void PlayerMovement::update(float deltaTime) {
    float speed = 2.0f;

    int forward = keyboard->getKey(GLFW_KEY_W);
    int backward = -keyboard->getKey(GLFW_KEY_S);
    int left = -keyboard->getKey(GLFW_KEY_A);
    int right = keyboard->getKey(GLFW_KEY_D);
    int cup = keyboard->getKey(GLFW_KEY_SPACE);
    int down = -keyboard->getKey(GLFW_KEY_LEFT_CONTROL);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    auto view = registry().view<const Components::Controllable, Components::Transform>();
    for (auto&& [entity, controllable, transform] : view.each()) {
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::vec3 front = glm::normalize(transform.rotation);

        direction += speed * (forward + backward) * front;
        direction += speed * (left + right) * glm::normalize(glm::cross(front, up));
        direction += speed * (cup + down) * up;

        transform.position += direction * deltaTime;
    }
};
