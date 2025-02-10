#include "shape.hpp"
#include <glad/glad.h>

class Triangle : public Shape
{
public:
    Triangle(glm::vec3 position)
        : Shape(
            [position]()
            {
                return std::vector<float> {
                    position.x,        position.y + 0.1f, position.z,
                    position.x - 0.1f, position.y - 0.1f, position.z,
                    position.x + 0.1f, position.y - 0.1f, position.z
                };
            }(),
            []() { return std::vector<int> {0, 1, 2}; }())
    {

    }

};
