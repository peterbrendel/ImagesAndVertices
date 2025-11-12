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

FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt
    GIT_TAG        v3.15.0
)

FetchContent_MakeAvailable(glfw glm spdlog entt)

find_package(OpenGL REQUIRED)

add_library(glad src/deps/glad/src/glad.c)

target_include_directories(glad SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glad/include)

add_library(
    ${PROJECT_NAME} SHARED
    src/setup.cpp
    src/classes/camera.cpp
    src/classes/game.cpp
    src/classes/keyboard.cpp
    src/classes/mesh_loader.cpp
    # src/classes/mesh_renderer.cpp
    src/classes/mouse.cpp
    src/classes/player_movement.cpp
    src/classes/shader.cpp
    src/classes/texture.cpp
)

file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS "src/headers/**")
file(GLOB_RECURSE SHAREAD_HEADERS CONFIGURE_DEPENDS "include/**")
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_HEADERS})
source_group("Header Files" FILES ${PROJECT_HEADERS} ${SHARED_HEADERS})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw spdlog OpenGL::GL glm EnTT::EnTT)

target_compile_definitions(${PROJECT_NAME} PRIVATE CORE_BUILD_DLL GLFW_INCLUDE_NONE)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_ENVIRONMENT "$<$<CONFIG:Debug>:SPDLOG_LEVEL=debug>$<$<CONFIG:Release>:MY_VAR=release_value"
)
