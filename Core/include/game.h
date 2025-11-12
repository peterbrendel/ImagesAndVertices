#pragma once
#include <core_api.h>
#include <string>

class GLFWwindow;
namespace entt {
    class entity;
    class registry;
}
class Camera;

namespace Core {
    class CORE_API Game {
        friend class System;

    public:
        Game(std::string name, short width, short height);
        ~Game();
        void run();
        entt::entity createEntity();

        template<typename T>
        void addComponent(entt::entity e);
    private:
        // Window  
        GLFWwindow* m_Window;
        std::string m_Name;
        short m_Width, m_Height;

        void framebuffer_size_callback(int width, int height);
        void handleInput();

        // Time  
        float m_LastFrame = 0.0f;
        float m_DeltaTime = 0.0f;

        // Render
        Camera* camera;

        // ECS
        entt::registry* m_Registry;
    };
}
