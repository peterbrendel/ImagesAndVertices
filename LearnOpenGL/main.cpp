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

	Triangle triangles[] = {
		Triangle(glm::vec3(0.0f, 0.0f, 0.0f)),
		Triangle(glm::vec3(0.5f, 0.0f, 0.0f))
	};

	Square square = Square(glm::vec3(0.0f, 0.0f, 0.0f));
	square.m_scale *= glm::vec3(0.1f, 0.1f, 0.1f);

	triangles[0].m_position = glm::vec3(-0.9f, 0.0f, 0.0f);
	triangles[0].m_scale = glm::vec3(0.4f, 0.4f, 0.4f);

	triangles[1].m_position = glm::vec3(0.9f, 0.0f, 0.0f);
	triangles[1].m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	Cube cube = Cube(glm::vec3(1.5f, -0.5f, 0.0f));

	Texture textures[] = {
		Texture("assets/Boshy.png"),
		Texture("assets/awesomeface.png"),
		Texture("assets/container.jpg")
	};

	triangles[0].setTexture(std::make_shared<Texture>(textures[0]));
	triangles[1].setTexture(std::make_shared<Texture>(textures[1]));

	square.setTexture(std::make_shared<Texture>(textures[2]));

	cube.setTexture(std::make_shared<Texture>(textures[2]));
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

		// use program before set uniform
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view = camera.view();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(90.0f), ((float) width) / height, 0.1f, 100.0f);
		// projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

		shader.setUniform("model", model);
		shader.setUniform("view", view);
		shader.setUniform("projection", projection);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		for (auto&& t : triangles) {
			shader.setUniform("translation", t.m_position);
			shader.setUniform("scaling", t.m_scale);
			t.draw();
		}

		cube.m_position += glm::vec3((((double) rand() / (RAND_MAX)) * 2 - 1) * 10 * deltaTime, (((double) rand() / (RAND_MAX)) * 2 - 1) * 10 * deltaTime, 0.0f);

		shader.setUniform("translation", square.m_position);
		shader.setUniform("scaling", square.m_scale);

		square.draw();

		shader.setUniform("translation", cube.m_position);
		shader.setUniform("scaling", glm::vec3(1.0f, 1.0f, 1.0f));

		cube.draw();

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
