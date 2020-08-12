#include "Camera.h"

#include "glm/gtx/transform.hpp"

#include <iostream>

Camera& Camera::instance(){
    static Camera* instance = new Camera();
    return *instance;
}

void Camera::mouseLook(int mouseX, int mouseY){
    // Record our new position as a vector
    glm::vec2 newMousePosition(mouseX, mouseY);
    // Detect how much the mouse has moved since
    // the last time
    glm::vec2 mouseDelta = 0.01f*(newMousePosition-oldMousePosition)
;
    viewDirection = glm::mat3(glm::rotate(-mouseDelta.x, upVector)) *
viewDirection;
    
    // Update our old position after we have made changes 
    oldMousePosition = newMousePosition;
}

void Camera::moveForward(float speed){
    eyePosition.z -= speed;
}

void Camera::moveBackward(float speed){
    eyePosition.z += speed;
}

void Camera::moveLeft(float speed){
    eyePosition.x -= speed;
}

void Camera::moveRight(float speed){
    eyePosition.x += speed;
}

void Camera::moveUp(float speed){
    eyePosition.y += speed;
}

void Camera::moveDown(float speed){
    eyePosition.y -= speed;
}

float Camera::getEyeXPosition(){
    return eyePosition.x;
}

float Camera::getEyeYPosition(){
    return eyePosition.y;
}

float Camera::getEyeZPosition(){
    return eyePosition.z;
}

float Camera::getViewXDirection(){
    return viewDirection.x;
}

float Camera::getViewYDirection(){
    return viewDirection.y;
}

float Camera::getViewZDirection(){
    return viewDirection.z;
}

Camera::Camera(){
    std::cout << "Created a Single Camera!\n";
    eyePosition = glm::vec3(0.0f,0.0f, 0.0f);    
    viewDirection = glm::vec3(0.0f,0.0f, -1.0f);    
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);

}

glm::mat4 Camera::getWorldToViewmatrix() const{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt( eyePosition,
                        eyePosition + viewDirection,
                        upVector);
}
