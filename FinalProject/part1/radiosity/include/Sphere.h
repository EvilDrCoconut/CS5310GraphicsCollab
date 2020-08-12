#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>  // Used for math operations
#include "ray.h"

class Sphere{
public:
    // Constructor for the sphere
    Sphere(glm::vec3 c, float r);

    // The purpose of this function is to do a 'boolean test'
    // to see if a 'ray' that is fired hits a sphere.
    // If showNormals is true, then show normals, else a solid color
    float hit_sphere(const Ray& r);
private:
    // Member functions (i.e. properties) of the sphere
    // Radius of the circle
    float radius;
    // The center of the sphere (i.e. its position)
    glm::vec3 center;
};


#endif
