cmake_minimum_required(VERSION 4.0.1)
project(Application)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Core)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_ENVIRONMENT "$<$<CONFIG:Debug>:SPDLOG_LEVEL=debug>$<$<CONFIG:Release>:MY_VAR=release_value>"
)
