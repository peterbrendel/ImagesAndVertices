#pragma once
#include <GLFW/glfw3.h>
#include <vector>

typedef struct CursorMovement
{
    float currentX, currentY;
    float offsetX, offsetY;
    bool locked;
} CursorMovement;

class Mouse
{
    float x = 0.0f, y = 0.0f;
    float lastX = 0.0f, lastY = 0.0f;
    bool locked = false;

    static std::vector<Mouse*> instances;

    static void posCallback(GLFWwindow* window, double xPos, double yPos);
    static void clickCallback(GLFWwindow* window, int button, int action, int mods);

public:
    Mouse();
    ~Mouse();
    static void setup(GLFWwindow* window);

    CursorMovement getMovement();
};
