#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera();
    Camera(glm::vec3 position,
		    glm::vec3 up,
		    GLfloat pitch,
		    GLfloat yaw,
		    GLfloat movementSpeed,
		    GLfloat turningSpeed);
    void keyControl(bool *keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);
    glm::mat4 calculateViewMatrix(void);
    ~Camera();
private:
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mRight;
    glm::vec3 mUp;
    glm::vec3 mWorldUp;

    GLfloat mPitch;
    GLfloat mYaw;

    GLfloat mMovementSpeed;
    GLfloat mTurningSpeed;

    void update(void);    
};
