#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera{
public:
    // Default Constructor
    Camera();

    // Casts a ray from the camera.
    // We can use this ray to then
    // test for intersection. If the ray would 
    // intersect with a shape, we return where
    // that intersection occurs
    // u and v would correspond to values of:
    // [-2,2] for 'u' as an example, and
    // [-1,1] for v.
    Ray get_ray(float u, float v);

private:
    // Here we are setting up our scene
    glm::vec3 lower_left_corner;
    // The width of our scene
    glm::vec3 horizontal;
    // The height of our scene
    glm::vec3 vertical;
    // The origin where the camera sits
    glm::vec3 origin;
};


#endif



