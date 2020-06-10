#include <camera.hpp>

Camera::Camera() {

}

Camera::Camera(glm::vec3 startPos,
		    glm::vec3 startUp,
		    GLfloat startPitch,
		    GLfloat startYaw,
		    GLfloat movementSpeed,
		    GLfloat turningSpeed) {
    mPosition = startPos;
    mWorldUp = startUp;
    mPitch = startPitch;
    mYaw = startYaw;
    mFront = glm::vec3(0.0, 0.0, -1.0);

    mMovementSpeed = movementSpeed;
    mTurningSpeed = turningSpeed;

    update();
}

void Camera::update() {
    mFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront.y = sin(glm::radians(mPitch));
    mFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(mFront);

    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}

void Camera::keyControl(bool *keys, GLfloat deltaTime) {
	
    GLfloat velocity = mMovementSpeed * deltaTime;

    if(keys[GLFW_KEY_W]) {
	mPosition += mFront * velocity;
    }
    if(keys[GLFW_KEY_S]) {
	mPosition -= mFront * velocity;
    }
    if(keys[GLFW_KEY_A]) {
	mPosition -= mRight * velocity;
    }
    if(keys[GLFW_KEY_D]) {
	mPosition += mRight * velocity;
    }
    if(keys[GLFW_KEY_R]) {
	mPosition += mUp * velocity;
    }
    if(keys[GLFW_KEY_F]) {
	mPosition -= mUp * velocity;
    }
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    
   xChange *= mTurningSpeed;
   yChange *= mTurningSpeed;

   mPitch += yChange;
   mYaw += xChange;

   if(mPitch > 89.00) {
	mPitch = 89.00;
   }
   if(mPitch < -89.00) {
	mPitch = -89.00;
   }

   update();
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

Camera::~Camera() {

}
