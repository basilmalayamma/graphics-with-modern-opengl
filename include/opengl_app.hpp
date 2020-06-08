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
out vec4 vCol;				            	    \n\
uniform mat4 model;			                    \n\
uniform mat4 projection;		                    \n\
void main()				   	     	    \n\
{				   		            \n\
    gl_Position = projection * model * vec4(pos, 1.0);	    \n\
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);		    \n\
}";

static const char *fShader = "     		    \n\
#version 330				   	    \n\
in vec4 vCol;				            \n\
out vec4 colour;			            \n\
void main()				   	    \n\
{				   		    \n\
    colour = vCol;			            \n\
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
    GLuint mVAO, mVBO, mIBO, mShader;
    GLuint mUniformModel, mUniformProjection;
    bool mDirection = true;
    float mTriOffset = 0.0f;
    float mAngle = 0.0f;
    float mScaleSize = 0.0f;
};
