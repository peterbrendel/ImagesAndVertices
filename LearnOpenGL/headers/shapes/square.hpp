#include "shape.hpp"
#include <glad/glad.h>

class Square : public Shape
{
public:
    Square(glm::vec3 position)
        : Shape(
            []()
            {
                return std::vector<float> {
                    -1.0f,  1.0f, 0.0f, // top left
                     1.0f,  1.0f, 0.0f, // top right
                    -1.0f, -1.0f, 0.0f, // bot left
                     1.0f, -1.0f, 0.0f  // bot right
                };
            }(),
            []() { return std::vector<int> {0, 1, 2, 1, 3, 2}; }())
    {
        m_position = position;
    }

};
