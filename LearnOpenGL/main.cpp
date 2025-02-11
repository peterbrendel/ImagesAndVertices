#include "setup.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "shapes/triangle.hpp"
#include "shapes/square.hpp"
#include "shapes/cube.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

float x = 0.0f, y = 0.0f;
float d = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);

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

	double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;
    double deltaTime;

	double a=0;
    double speed = 0.6;

	while (!glfwWindowShouldClose(window)) {
		currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		handleInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// use program before set uniform
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(d), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(x, y, -3.0f));

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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		y -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		y += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		x += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		x -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		d -= 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		d += 0.5f;
	}
}
