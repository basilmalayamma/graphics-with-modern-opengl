#include <shader.hpp>
#include <mesh.hpp>
#include <window.hpp>
#include <camera.hpp>

#include <string.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

std::vector<mesh*> meshList;
std::vector<shader*> shaderList;

static const char *vShader = "../resources/shader.vs";
static const char *fShader = "../resources/shader.fs"; 

int main() {

    Window window;
    window.initialize();
    Camera camera(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.5f);

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
		    sizeof(indices)/sizeof(indices[0]),
		    sizeof(vertices)/sizeof(vertices[0]));
    meshList.push_back(mesh1);

    mesh *mesh2 = new mesh();
    mesh2->createMesh(indices, vertices, 
		    sizeof(indices)/sizeof(indices[0]),
		    sizeof(vertices)/sizeof(vertices[0]));
    meshList.push_back(mesh2);

    glEnable(GL_DEPTH_TEST);

    int bufferWidth = window.getBufferWidth();
    int bufferHeight = window.getBufferHeight();

    GLfloat deltaTime = 0.0f;
    GLfloat lastTime = glfwGetTime();

    //Setup view port size
    glViewport(0, 0, bufferWidth, bufferHeight);

    GLfloat aspect_ratio = 
	    (GLfloat)bufferWidth/(GLfloat)bufferHeight;
    glm::mat4 projection = glm::perspective(
		    45.0f, aspect_ratio, 1.0f, 100.0f);

    GLuint uniformProjection = shaderList[0]->getUniformProjection();
    GLuint uniformModel = shaderList[0]->getUniformModel();
    GLuint uniformView = shaderList[0]->getUniformView();

    //Loop until window closed
    while(!window.getShouldClose()) {
	//Get handle of using input
	glfwPollEvents();
	
	//clear window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderList[0]->useShader();

	GLfloat currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	camera.keyControl(window.getKeys(), deltaTime);
	camera.mouseControl(window.getXChange(), window.getYChange());

	//order is important, change the order to see the difference
	glm::mat4 model(1.0f);
	model = glm::translate(
			model, glm::vec3(0.0f, -0.5f, -2.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

	glUniformMatrix4fv(
			uniformModel, 1, GL_FALSE,
			glm::value_ptr(model));

	glUniformMatrix4fv(
			uniformProjection, 1, GL_FALSE,
			glm::value_ptr(projection));

	glUniformMatrix4fv(
			uniformView, 1, GL_FALSE,
			glm::value_ptr(camera.calculateViewMatrix()));
	meshList[0]->renderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(
			model, glm::vec3(0.0f, 0.5f, -2.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

	glUniformMatrix4fv(
			uniformModel, 1, GL_FALSE,
			glm::value_ptr(model));
	meshList[1]->renderMesh();


	glUseProgram(0);

	window.swapBuffers();
    }

    return 0;
}
