#include <opengl_app.hpp>

int openglApp::createWindowUsingGLFW(int width, int height) {
    //Initialize GLFW lib
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

    mMainWindow = glfwCreateWindow(width, height,
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
    return 0;
}

int openglApp::initializeGLEW(void) {
    //Allow modern extensions
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
	std::cout << "glew initialize failed" << std::endl;
	glfwDestroyWindow(mMainWindow);
	glfwTerminate();
	return 1;	
    }
    return 0;
}

void openglApp::render(float triIncrement, float triMaxOffset) {
    //Setup view port size
    glViewport(0, 0, mBufferWidth, mBufferHeight);

    //Loop until window closed
    while(!glfwWindowShouldClose(mMainWindow)) {
	//Get handle of using input
	glfwPollEvents();

	if(mDirection) {
	    mTriOffset += triIncrement;
	    mScaleSize += 0.001f;
	}
	else {
	    mTriOffset -= triIncrement;
	    mScaleSize -= 0.001f;
	}

	if(abs(mTriOffset) >= triMaxOffset) {
	    mDirection = !mDirection;
	}

	mAngle += 0.1f;
	if(mAngle > 360.0) {
	    mAngle = 0.0f;
	}

	//clear window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(mShader);

	//order is important, change the order to see the difference
	glm::mat4 model(1.0f);
	model = glm::rotate(model, mAngle * TORANDIANS, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(mTriOffset, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(mScaleSize, 0.4f, 1.0f));

	glUniformMatrix4fv(mUniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(mVAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Unbind
	glBindVertexArray(0);
	glUseProgram(0);

	glfwSwapBuffers(mMainWindow);
    }
}

void openglApp::createTriangle(void) {
    GLfloat vertices[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		    vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void openglApp::compileShaders() {
    mShader = glCreateProgram();
    if(!mShader) {
	std::cout << "Error creating shader program" << std::endl;
	return;
    }

    addShaders(vShader, GL_VERTEX_SHADER);
    addShaders(fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(mShader);
    glGetProgramiv(mShader, GL_LINK_STATUS, &result);
    if(!result) {
	glGetProgramInfoLog(mShader, sizeof(eLog), NULL, eLog);
	std::cout << "Error linking shader: " << eLog << std::endl;
	return;
    }

    glValidateProgram(mShader);
    glGetProgramiv(mShader, GL_VALIDATE_STATUS, &result);
    if(!result) {
	glGetProgramInfoLog(mShader, sizeof(eLog), NULL, eLog);
	std::cout << "Error validating shader: " << eLog << std::endl;
	return;
    }

    mUniformModel = glGetUniformLocation(mShader, "model");
}

void openglApp::addShaders(
		const char* shaderCode, 
		GLenum shaderType) {
    GLuint theshader = glCreateShader(shaderType);
    const GLchar *thecode[1];
    thecode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theshader, 1, thecode, codeLength);
    glCompileShader(theshader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theshader, GL_COMPILE_STATUS, &result);
    if(!result) {
	glGetShaderInfoLog(theshader, sizeof(eLog), NULL, eLog);
	std::cout << "Error compiling shader: " << eLog << std::endl;
	return;
    }

    glAttachShader(mShader, theshader);
}
