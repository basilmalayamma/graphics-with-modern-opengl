#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TORANDIANS (3.14f/180.0f)

static const char *vShader = "     			    \n\
#version 330				   		    \n\
layout (location = 0) in vec3 pos;	            	    \n\
uniform mat4 model;			                    \n\
void main()				   	     	    \n\
{				   		            \n\
    gl_Position = model * vec4(0.4 * pos.x, 0.4 * pos.y, 0.4 * pos.z, 1.0);   \n\
}";

static const char *fShader = "     		    \n\
#version 330				   	    \n\
out vec4 colour;			            \n\
void main()				   	    \n\
{				   		    \n\
    colour = vec4(1.0f, 0.0f, 0.0f, 1.0);           \n\
}";

class openglApp {
public:
    int createWindowUsingGLFW(int width, int height);
    int initializeGLEW(void);
    void render(float triIncrement, float triMaxOffset);
    void createTriangle(void);
    void compileShaders(void);
    void addShaders(
		const char* shaderCode, 
		GLenum shaderType);
private:
    GLFWwindow *mMainWindow;
    int mBufferWidth, mBufferHeight;
    GLuint mVAO, mVBO, mShader;
    GLuint mUniformModel;
    bool mDirection = true;
    float mTriOffset = 0.0f;
    float mAngle = 0.0f;
};
