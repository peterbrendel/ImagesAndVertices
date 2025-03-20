cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)
set_property(${PROJECT} TARGET PROPERTY CXX_STANDARD 20)


set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/glm")

# Set up paths for macOS Homebrew
if(APPLE)
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/;${CMAKE_PREFIX_PATH}")
endif()

# Find GLFW and OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# find GLM
find_package(glm CONFIG REQUIRED)

# Add GLAD source file
add_library(glad src/deps/glad/src/glad.c)

# Make sure the glad include path is recognized via angle brackets
target_include_directories(glad SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/src/deps/glad/include)

# Define executable target
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/setup.cpp
    src/classes/camera.cpp
    src/classes/keyboard.cpp
    src/classes/mouse.cpp
    src/classes/shader.cpp
    src/classes/shape.cpp
    src/classes/texture.cpp
    src/classes/shapes/cube.cpp
    )

# Include project headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/deps/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/headers)

# Link GLAD to the executable target
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# Link GLFW and OpenGL to the executable target
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)

# Link GLM to the executable target
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm-header-only)

# macOS specific settings
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()

# Windows-specific settings
if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()
