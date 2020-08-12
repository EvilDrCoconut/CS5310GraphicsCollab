
#include <glm/glm.hpp>  // Used for math operations
#include "Sphere.h"
#include "ray.h"

// Constructor for the sphere
Sphere::Sphere(glm::vec3 c, float r) : center(c), radius(r) { 

}

// The purpose of this function is to do a 'boolean test'
// to see if a 'ray' that is fired hits a sphere.
// If showNormals is true, then show normals, else a solid color
float Sphere::hit_sphere(const Ray& r){
    // Vector from the origin to the center
    glm::vec3 oc = r.origin() - center;
   
    // Here we need to figure out the vector 
    // form of the sphere. 
    float a = glm::dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = glm::dot(oc, oc) - radius*radius;
    float discriminant = (b * b) - (4.0f*a*c);
    // No interesections
    if(discriminant <0 ){
        return -1.0f; // There are no solutions
    }
    else{   
        // Return the solution
        // 'the solution' being where exactly we hit the sphere.
        return (-b - sqrt(discriminant))/(2.0f*a);
    }
}
