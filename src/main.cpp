#include <opengl_app.hpp>

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

float triIncrement = 0.005f;
float triMaxOffset = 0.7f;

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
    app.render(triIncrement, triMaxOffset);
    return 0;
}
