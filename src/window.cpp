#include <iostream>
#include <window.hpp>

Window::Window() {
    mWidth = 800;
    mHeight = 600;
}

Window::Window(int width, int height) {
    mWidth = width;
    mHeight = height;
}

int Window::initialize(void) {
    if(!glfwInit()) {
	std::cout << "glfw initialize failed" << std::endl;
	glfwTerminate();
	return 1;	
    }

    //Setup GLFW window properties
    //1. OpenGL version
    //2. Core profile = no backward compatibility
    //3. Allow formward compatibity
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

    mMainWindow = glfwCreateWindow(mWidth, mHeight,
		   "My Window", NULL, NULL);
    if(mMainWindow) {
	std::cout << "Window creation successful" << std::endl;
    }
    else {
	std::cout << "Window creation unsuccessful" << std::endl;
	glfwTerminate();
	return 1;	
    }

    //Get the buffer size
    glfwGetFramebufferSize(mMainWindow, &mBufferWidth, &mBufferHeight);

    //Set context for GLFW to use
    glfwMakeContextCurrent(mMainWindow);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
	std::cout << "glew initialize failed" << std::endl;
	glfwDestroyWindow(mMainWindow);
	glfwTerminate();
	return 1;	
    }
}

int Window::getBufferWidth(void) {
    return mBufferWidth;
}

int Window::getBufferHeight(void) {
    return mBufferHeight;
}

int Window::getShouldClose(void) {
    glfwWindowShouldClose(mMainWindow);
}

void Window::swapBuffers(void) {
    glfwSwapBuffers(mMainWindow);
}

Window::~Window() {
    glfwDestroyWindow(mMainWindow);
    glfwTerminate();
}


