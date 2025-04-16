#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#include <keyboard.hpp>
#include <mouse.hpp>


GLFWwindow* setupWindow(const int argc, const char* argv[]);
