#pragma once
#include <entt/entt.hpp>
#include <game.h>

namespace Core {
    class System {
    public:
        System(Game& game) : m_Game(game) {};
        virtual ~System() = default;
        virtual void update(float deltaTime) = 0;
        inline entt::registry& registry() {
            return m_Game.m_Registry;
        }
    private:
        Game& m_Game;
    };
}
