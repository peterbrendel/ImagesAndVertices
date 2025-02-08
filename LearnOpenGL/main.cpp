#include "setup.hpp"
#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);

int main(int argc, const char* argv[]) {
	GLFWwindow* window = setupWindow();

	// FramebufferSize in other words is the window drawing region
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader orangeShader = Shader("shaders/example1.vert", "shaders/example1.frag");
	Shader yellowShader = Shader("shaders/example1.vert", "shaders/exercise3.frag");

	// Orange triangle

	float orangeTriangleVertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int VAOOrange;
	glGenVertexArrays(1, &VAOOrange);
	glBindVertexArray(VAOOrange);

	unsigned int VBOOrange;
	glGenBuffers(1, &VBOOrange);
	glBindBuffer(GL_ARRAY_BUFFER, VBOOrange);
	glBufferData(GL_ARRAY_BUFFER, sizeof(orangeTriangleVertices), orangeTriangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Yellow triangle

	float yellowTriangleVertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f
	};

	unsigned int VAOYellow;
	glGenVertexArrays(1, &VAOYellow);
	glBindVertexArray(VAOYellow);

	unsigned int VBOYellow;
	glGenBuffers(1, &VBOYellow);
	glBindBuffer(GL_ARRAY_BUFFER, VBOYellow);
	glBufferData(GL_ARRAY_BUFFER, sizeof(yellowTriangleVertices), yellowTriangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Render loop

	while (!glfwWindowShouldClose(window)) {
		handleInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(orangeShader.m_shaderProgram, "ourColor");
		
		// use program before set uniform
		orangeShader.use();
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAOOrange);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		yellowShader.use();
		glBindVertexArray(VAOYellow);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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
