#include <setup.hpp>
#include <spdlog/spdlog.h>

GLFWwindow* setupWindow(const int argc, const char* argv[]) {
	spdlog::cfg::load_env_levels();

	spdlog::info("Running with {} args", argc);
	for (int i = 0; i < argc; i++) {
		spdlog::info("arg[{0}] = {1}", i, argv[i]);
	}

    // Initialize glfw
	glfwInit();

	// Window Hints can be used to force dependency version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1920 / 2, 1080 / 2, "OpenGL", NULL, NULL);

	if (window == NULL) {
		spdlog::error("Failed to create GLFW");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	// Load OpenGL instruction pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		spdlog::error("Failed to initialize GLA");
        glfwTerminate();
		return NULL;
	}

	Keyboard::setup(window);
	Mouse::setup(window);

	return window;
}
