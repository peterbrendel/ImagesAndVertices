#include <game.h>
#include <GLFW/glfw3.h>
#include <string>  
#include <vector>
#include <entt/entt.hpp>
#include <components.h>
#include <camera.h>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <glad/glad.h>
#include <shader.h>

using namespace Core;

Game::Game(std::string name, short width, short height) : m_Name(name), m_Width(width), m_Height(height) {
	spdlog::cfg::load_env_levels();

	if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW");
		return;
	}

	// Window Hints can be used to force dependency version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);

	if (m_Window == NULL) {
		spdlog::error("Failed to create GLFW");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);

	// Load OpenGL instruction pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		spdlog::error("Failed to initialize GLA");
		glfwTerminate();
		return;
	}

	spdlog::info("Supported GLSL version is {}", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	auto callback = [](GLFWwindow* window, int width, int height) {
		static_cast<Game*>(glfwGetWindowUserPointer(window))->framebuffer_size_callback(width, height);
	};
	glfwSetFramebufferSizeCallback(m_Window, callback);

    camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), (float)m_Width / (float)m_Height);
}

Game::~Game() {
	glfwTerminate();
	delete camera;
}

void Game::run() {
	Shader shader = Shader("assets/shaders/main.vert", "assets/shaders/main.frag");
	Shader lightShader = Shader("assets/shaders/main.vert", "assets/shaders/lightSource.frag");

	while (!glfwWindowShouldClose(m_Window)) {
		float currentFrame = (float)glfwGetTime();
		m_DeltaTime = currentFrame - m_LastFrame;
		m_LastFrame = currentFrame;

		handleInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		auto view = camera->view();
		auto proj = camera->projection();
		shader.use();
        shader.setUniform("view", view);
        shader.setUniform("projection", proj);


		
		glBindVertexArray(0);
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}

void Game::framebuffer_size_callback(int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::handleInput() {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
}

inline entt::entity Game::createEntity() {
	return m_Registry->create();
}

template<typename T>
inline void Game::addComponent(entt::entity e) {
    m_Registry.emplace<T>(e);
}
