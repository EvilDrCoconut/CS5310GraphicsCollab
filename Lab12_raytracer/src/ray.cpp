#include <glm/glm.hpp>
#include "ray.h"

// Default constructor
Ray::Ray() {}

// Constructor a ray with
// a: origin of ray
// b: direction of ray
Ray::Ray(const glm::vec3& a, const glm::vec3& b){
    A = a;
    B = b;
}

// Return the origin of our ray 
glm::vec3 Ray::origin() const{
    return A;
} 

// Return the direction of our array
glm::vec3 Ray::direction() const{
    return B;
} 

// Figure out where our point is at some 't'
// This will be used to 'test' if some intersection occurred
// and thus if some color should be generated
glm::vec3 Ray:: point_at_parameter(float t) const{
    return A + t*B;
}

