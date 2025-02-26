#include <setup.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <camera.hpp>
#include <entities/cube.hpp>
#include <scene.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	std::shared_ptr<Shader> shader = std::make_shared<Shader>("shaders/main.vert", "shaders/main.frag");
	std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("shaders/main.vert", "shaders/lightSource.frag");

	std::vector<std::shared_ptr<Texture>> textures = {
		std::make_shared<Texture>("assets/container.jpg")
	};

	Cube cube = Cube(shader, glm::vec3(0.0f, 0.0f, 0.0f));
	cube.setTexture(textures[0]);

	Cube lightCube = Cube(lightShader, glm::vec3(1.2f, 1.0f, 2.0f));

	shader->use();
	shader->setUniform("fTexture1", 0);
	shader->setUniform("lightPos", lightCube.position());

	Scene scene = Scene();

	scene.setCamera(
		std::make_unique<Camera>(
			shader,
			glm::vec2(width, height),
			90.0f,
			glm::vec3(0.0f, 0.0f, 0.0f)
		)
	);

	scene.add(std::make_shared<Cube>(cube));
	scene.add(std::make_shared<Cube>(lightCube));

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		handleInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		scene.update();
		scene.draw();

		lightCube.update(cube.position() + glm::vec3(cos(currentFrame * 1.5f), sin(currentFrame * 1.5f), -cos(currentFrame * 1.5f) * 2));

		cube.update(cube.position() + glm::vec3(3 * 0.5 * deltaTime, 0, 0 ));

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
