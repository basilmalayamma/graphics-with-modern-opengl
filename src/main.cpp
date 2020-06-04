#include <opengl_app.hpp>

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

int main() {
    openglApp app;
    if(app.createWindowUsingGLFW(WIDTH, HEIGHT)) {
	std::cout << "creating window using GLFW Failed" << std::endl;
    }
    if(app.initializeGLEW()) {
	std::cout << "GLEW initialize failed" << std::endl;
    }
    app.compileShaders();
    app.createTriangle();
    app.render();
    return 0;
}
