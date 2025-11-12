#include <mesh_renderer.h>

using namespace Core;

MeshRenderer::MeshRenderer(Game& game) : System(game) {}

void MeshRenderer::update(float deltaTime) {

    auto view = registry().view<const Components::Mesh, Components::Transform>();
    for (auto&& [entity, mesh, transform] : view.each()) {
        // Create a model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::scale(model, transform.scale);

        model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        // Set the shader uniforms
        shader.setMat4("model", model);
        shader.setVec3("viewPos", camera.getPosition());

        if (mesh.texture != nullptr) {
            mesh.texture->active(0);
        }
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
};
