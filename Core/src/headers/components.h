#include <glm/glm.hpp>
#include <vector>
#include <texture.h>

namespace Core {
    namespace Components {

        typedef struct Transform {
            glm::vec3 position = { .0f, .0f, .0f };
            glm::vec3 rotation = { .0f, .0f, .0f };
            glm::vec3 scale = { 1, 1, 1 };
        } Transform;

        typedef struct Mesh {
            GLuint VAO;
            GLuint VBO;
            GLuint EBO;
            GLsizei indexCount;
            Texture* tex;
        } Mesh;

        typedef struct Controllable {
            int id;
        } Controllable;

    }
}
