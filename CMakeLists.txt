cmake_minimum_required(VERSION 4.0.1)
project(ImagesAndVertices)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Core)
add_subdirectory(Application)

# set_target_properties(${PROJECT_NAME} PROPERTIES
#     VS_DEBUGGER_ENVIRONMENT "$<$<CONFIG:Debug>:SPDLOG_LEVEL=debug>$<$<CONFIG:Release>:MY_VAR=release_value>"
# )

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)