#include "setup.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "shapes/triangle.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);

int main(int argc, const char* argv[]) {
	GLFWwindow* window = setupWindow();

	// FramebufferSize in other words is the window drawing region
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader shader = Shader("shaders/example1.vert", "shaders/example1.frag");

	Triangle triangles[] = {
		Triangle(glm::vec3(0.0f, 0.0f, 0.0f)),
		Triangle(glm::vec3(0.5f, 0.0f, 0.0f))
	};

	Texture textures[] = {
		Texture("assets/Boshy.png"),
		Texture("assets/awesomeface.png")
	};

	triangles[0].setTexture(std::make_shared<Texture>(textures[0]));
	triangles[1].setTexture(std::make_shared<Texture>(textures[1]));

	// Render loop
	shader.use();
	shader.setUniform("fTexture1", 0);

	while (!glfwWindowShouldClose(window)) {
		handleInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// use program before set uniform
		shader.use();

		for (auto&& t : triangles) {
			t.draw();
		}

		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void handleInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
