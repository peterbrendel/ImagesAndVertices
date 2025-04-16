#pragma once
#include <GLFW/glfw3.h>
#include <map>
#include <vector>

namespace Core {
    class Keyboard
    {
        std::map<int, bool> keys;
        static std::vector<Keyboard*> instances;

        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void setKey(int key, bool value);
    public:
        Keyboard(std::vector<int> keySubscription);
        static void setup(GLFWwindow* window);

        int getKey(int key);

        ~Keyboard();
    };
}