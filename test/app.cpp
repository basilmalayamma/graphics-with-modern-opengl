#include <shader.hpp>
#include <mesh.hpp>
#include <window.hpp>

#include <string.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define TORANDIANS (3.14f/180.0f)

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

float triIncrement = 0.005f;
float triMaxOffset = 0.7f;

bool mDirection = true;
float mTriOffset = 0.0f;
float mAngle = 0.0f;
float mScaleSize = 0.0f;

std::vector<mesh*> meshList;
std::vector<shader*> shaderList;

static const char *vShader = "../resources/shader.vs";
static const char *fShader = "../resources/shader.fs"; 

int main() {

    Window window;
    window.initialize();

    shader *shader1 = new shader();
    shader1->createFromFiles(vShader, fShader);
    shaderList.push_back(shader1);

    unsigned int indices[] = {
	0, 1, 3,
	0, 1, 2,
	0, 3, 2,
	2, 3, 1
    };

    GLfloat vertices[] = {
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	0.0f, -1.0f, 1.0f,
	0.0f, 1.0f, 0.0f
    };

    mesh *mesh1 = new mesh();
    mesh1->createMesh(indices, vertices, 
		    sizeof(indices), sizeof(vertices));
    meshList.push_back(mesh1);

    mesh *mesh2 = new mesh();
    mesh2->createMesh(indices, vertices, 
		    sizeof(indices), sizeof(vertices));
    meshList.push_back(mesh2);

    glEnable(GL_DEPTH_TEST);

    int bufferWidth = window.getBufferWidth();
    int bufferHeight = window.getBufferHeight();

    //Setup view port size
    glViewport(0, 0, bufferWidth, bufferHeight);

    GLfloat aspect_ratio = 
	    (GLfloat)bufferWidth/(GLfloat)bufferHeight;
    glm::mat4 projection = glm::perspective(
		    45.0f, aspect_ratio, 1.0f, 100.0f);

    GLuint mUniformProjection = shaderList[0]->getUniformProjection();
    GLuint mUniformModel = shaderList[0]->getUniformModel();

    //Loop until window closed
    while(!window.getShouldClose()) {
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

	mAngle += 0.5f;
	if(mAngle > 360.0) {
	    mAngle = 0.0f;
	}

	//clear window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderList[0]->useShader();

	//order is important, change the order to see the difference
	glm::mat4 model(1.0f);
	//model = glm::rotate(
	//		model, mAngle * TORANDIANS,
	//		glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(
			model, glm::vec3(mTriOffset, -0.5f, -2.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

	glUniformMatrix4fv(
			mUniformModel, 1, GL_FALSE,
			glm::value_ptr(model));

	meshList[0]->renderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(
			model, glm::vec3(-mTriOffset, 0.5f, -2.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

	glUniformMatrix4fv(
			mUniformModel, 1, GL_FALSE,
			glm::value_ptr(model));
	meshList[1]->renderMesh();

	glUniformMatrix4fv(
			mUniformProjection, 1, GL_FALSE,
			glm::value_ptr(projection));

	glUseProgram(0);

	window.swapBuffers();
    }

    return 0;
}
