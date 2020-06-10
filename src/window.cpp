#include <iostream>
#include <window.hpp>

Window::Window() {
    mWidth = 800;
    mHeight = 600;
    mMainWindow = NULL;
    mBufferWidth = 0;
    mBufferHeight = 0;
    for(int i = 0; i < 1024; i++) {
	mKeys[i] = 0;
    }
    mMouseFirstMove = true;
    mLasty = 0;
    mLastx = 0;
    mXChange = 0;
    mYChange = 0;
}

Window::Window(int width, int height) {
    mWidth = width;
    mHeight = height;
    mMainWindow = NULL;
    mBufferWidth = 0;
    mBufferHeight = 0;
    for(int i = 0; i < 1024; i++) {
	mKeys[i] = 0;
    }
    mMouseFirstMove = true;
    mLasty = 0;
    mLastx = 0;
    mXChange = 0;
    mYChange = 0;
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

    createCallbacks();
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

void Window::createCallbacks(void) {
    glfwSetWindowUserPointer(mMainWindow, this);
    glfwSetKeyCallback(mMainWindow, handleKeys);
    glfwSetCursorPosCallback(mMainWindow, handleMouse);
    glfwSetInputMode(mMainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
 
void Window::handleKeys(
		GLFWwindow *window,
		int key,
		int code,
		int action,
		int mode) {
    Window *thisWindow = static_cast<Window*>(
		    glfwGetWindowUserPointer(window));
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else {
	if(key > 0 && key < 1024) {
	    if(action == GLFW_PRESS) {
	        thisWindow->mKeys[key] = true;
		std::cout << "Pressed key " << key << std::endl;
	    }
	    else if(action == GLFW_RELEASE) {
	        thisWindow->mKeys[key] = false;
		std::cout << "Released key " << key << std::endl;
	    }
	}
    }
}

void Window::handleMouse(
		GLFWwindow *window,
		double xpos,
		double ypos) {
    Window *thisWindow = static_cast<Window*>(
		    glfwGetWindowUserPointer(window));
    if(thisWindow->mMouseFirstMove) {
	thisWindow->mLastx = xpos;
	thisWindow->mLasty = ypos;
	thisWindow->mMouseFirstMove = false;
    }

    thisWindow->mXChange = xpos - thisWindow->mLastx;
    thisWindow->mYChange = ypos - thisWindow->mLasty;

    thisWindow->mLastx = xpos;
    thisWindow->mLasty = ypos;
}

bool* Window::getKeys(void) {
    return mKeys;
}
double Window::getXChange(void) {
    double theChange = mXChange;
    mXChange = 0;
    return theChange;
}

double Window::getYChange(void) {
    double theChange = mYChange;
    mYChange = 0;
    return theChange;
}

Window::~Window() {
    glfwDestroyWindow(mMainWindow);
    glfwTerminate();
    for(int i = 0; i < 1024; i++) {
	mKeys[i] = 0;
    }
    mMainWindow = NULL;
    mBufferWidth = 0;
    mBufferHeight = 0;
    mMouseFirstMove = true;
    mLasty = 0;
    mLastx = 0;
    mXChange = 0;
    mYChange = 0;
}


