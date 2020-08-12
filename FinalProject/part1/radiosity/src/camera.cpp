#include "camera.h"

// Default constructor
Camera::Camera(){ 
    // Here we are setting up our viewport.
    // This is the lower left corner of our viewport
    lower_left_corner = glm::vec3(-2.0f,-1.0f, -1.0f);
    // The width of our viewport
    horizontal = glm::vec3(4.0f,0.0f,0.0f);
    // The height of our viewport
    vertical = glm::vec3(0.0f, 2.0f, 0.0f);
    // The origin where the camera sits
    origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

// Casts a ray from the camera.
Ray Camera::get_ray(float u, float v){
    return Ray(origin, lower_left_corner+ u*horizontal + v*vertical - origin);
}
