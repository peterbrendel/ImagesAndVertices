#include "shape.hpp"
#include <glad/glad.h>

class Triangle : public Shape
{
public:
    Triangle(glm::vec3 position)
        : Shape(
            []()
            {
                return std::vector<float> {
                     0.0f,  1.0f, 0.0f,
                    -1.0f, -1.0f, 0.0f,
                     1.0f, -1.0f, 0.0f
                };
            }(),
            []() { return std::vector<int> {0, 1, 2}; }())
    {
        m_position = position;
    }

};
