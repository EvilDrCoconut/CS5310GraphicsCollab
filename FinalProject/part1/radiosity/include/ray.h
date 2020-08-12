#ifndef RAY_H
#define RAY_H

// This is our basic 'ray' class.
// A 'ray' is shot out from the camera
// We can think of a 'ray' as something that computes a color along a direction.
//
// 
// In general rays have the form:
// 
// p(t) = A + t * B
// 
// p    is the 3D position along the line over some 't' (t can be thought of like
//      time)
//      P itelf thus, is a point moving along a line.
// A    is the ray origin
// B    is the ray direction
//
// As an aside: Remember when you learned the slope formular in 2D?
//              Think of y(x) = b + mx for a 2D line as a ray in 2D
//
//
  
#include <glm/glm.hpp>  // Used for math operations

// A ray class, for representing the equation: P(t) = A+ (t*b)
class Ray{
    public: 
        // Default constructor
        Ray();
        // Constructor a ray with
        // a: origin of ray
        // b: direction of ray
        Ray(const glm::vec3& a, const glm::vec3& b);   
        // Return the origin of our ray 
        glm::vec3 origin() const;
        // Return the direction of our array
        glm::vec3 direction() const;
        // Figure out where our point is at some 't'
        // This will be used to 'test' if some intersection occurred
        // and thus if some color should be generated
        glm::vec3 point_at_parameter(float t) const;

    private:
        glm::vec3 A; // Origin of our ray
        glm::vec3 B; // Direction of our ray
};


#endif
