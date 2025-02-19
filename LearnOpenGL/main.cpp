#include "setup.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "shapes/triangle.hpp"
#include "shapes/square.hpp"
#include "shapes/cube.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <mouse.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);

float lastFrame = 0;
float deltaTime = 0;

int main(int argc, const char* argv[]) {
	GLFWwindow* window = setupWindow();
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	// FramebufferSize in other words is the window drawing region
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader = Shader("shaders/main.vert", "shaders/main.frag");
	Shader lightShader = Shader("shaders/main.vert", "shaders/lightSource.frag");

	Cube cube = Cube(glm::vec3(0.0f, 0.0f, 0.0f));
	Cube lightCube = Cube(glm::vec3(3.0f, 3.0f, 0.0f));

	Texture textures[] = {
		Texture("assets/container.jpg")
	};

	cube.setTexture(std::make_shared<Texture>(textures[0]));
	//lightCube.setTexture(std::make_shared<Texture>(textures[0]));

	// Render loop
	shader.use();
	shader.setUniform("fTexture1", 0);

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		handleInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.view();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(90.0f), ((float) width) / height, 0.1f, 100.0f);

		// use program before set uniform
		shader.use();

		shader.setUniform("view", view);
		shader.setUniform("projection", projection);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		
		auto model = glm::translate(glm::mat4(1.0f), cube.m_position);
		model = glm::scale(model, glm::vec3(1.0f));
		shader.setUniform("model", model);

		auto normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
		shader.setUniform("normalMatrix", normalMatrix);

		shader.setUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader.setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setUniform("lightPos", lightCube.m_position);

		cube.draw();

		lightShader.use();

		model = glm::translate(glm::mat4(1.0f), lightCube.m_position);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setUniform("model", model);

		normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
		shader.setUniform("normalMatrix", normalMatrix);

		lightShader.setUniform("view", view);
		lightShader.setUniform("projection", projection);

		lightShader.setUniform("translation", lightCube.m_position);

		lightCube.draw();

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
