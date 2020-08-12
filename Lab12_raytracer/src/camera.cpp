#include "camera.h"
#include<iostream>

// Default constructor
Camera::Camera(){ 
    // Here we are setting up our viewport.
    // The width of our viewport
    horizontal = glm::vec3(4.0f,0.0f,0.0f);
    // The height of our viewport
    vertical = glm::vec3(0.0f, 2.0f, 0.0f);
    // The origin where the camera sits
    origin = glm::vec3(0.0f, 0.0f, 1.0f); // looking from

    float fov = 30;  
    float view_angle = fov * M_PI / 180;
    float aspect_ratio = 2.0f;
    float half_height = 2.0f*tan(view_angle/2.0f);
    float half_width = aspect_ratio * half_height;

    // define where we are looking
    glm::vec3 up = glm::vec3(0,1,0);
    glm::vec3 lookAt = glm::vec3(1.0,0.0,-10.0);
    auto w = glm::normalize(origin-lookAt);
    auto u = glm::normalize(glm::cross(up,w));
    auto v = glm::cross(w,u);

    // This is the lower left corner of our viewport
    // lower_left_corner = glm::vec3(-2.0f,-1.0f, -1.0f);
    lower_left_corner = origin - half_width*u - half_height*v - w;
    horizontal = 2.0f*half_width*u;
    vertical = 2.0f*half_height*v;
}

// Casts a ray from the camera.
Ray Camera::get_ray(float u, float v){
    return Ray(origin, lower_left_corner+ u*horizontal + v*vertical - origin);
}

