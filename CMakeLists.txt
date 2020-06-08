cmake_minimum_required(VERSION 3.2)

project(opengl_app)

include_directories(
    include
)

add_executable(opengl_app
    src/mesh.cpp
    src/window.cpp
    src/shader.cpp
    test/app.cpp
)

target_link_libraries(opengl_app
    GLEW
    GL
    glfw
)

install(TARGETS opengl_app DESTINATION ${CMAKE_SOURCE_DIR}/bin)
