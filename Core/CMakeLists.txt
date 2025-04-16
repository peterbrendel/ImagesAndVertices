cmake_minimum_required(VERSION 4.0.1)
project(Core)

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG        v1.15.2
)

FetchContent_MakeAvailable(glfw glm spdlog)

find_package(OpenGL REQUIRED)

add_library(glad src/deps/glad/src/glad.c)

target_include_directories(glad SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/src/deps/glad/include)

add_library(
    ${PROJECT_NAME} SHARED
    src/setup.cpp
    src/classes/camera.cpp
    src/classes/keyboard.cpp
    src/classes/mouse.cpp
    src/classes/shader.cpp
    src/classes/shape.cpp
    src/classes/texture.cpp
    src/classes/shapes/cube.cpp
)

file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS "src/headers/**")
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_HEADERS})
source_group("Header Files" FILES ${PROJECT_HEADERS})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glad/include
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw spdlog OpenGL::GL glm::glm-header-only)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_ENVIRONMENT "$<$<CONFIG:Debug>:SPDLOG_LEVEL=debug>$<$<CONFIG:Release>:MY_VAR=release_value>"
)