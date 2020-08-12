#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>  // Used for math operations
#include <iostream> // Used for I/O
#include <fstream>  // Used for file operations
#include <vector>   // Used for our world

#include "ray.h"
#include "camera.h"
#include "Sphere.h"

class Scene{
public:
 
    // Constructor for a scene
    Scene();
    // Destructor
    ~Scene();
    // Add another object to our ray tracer
    void addObject(Sphere* s);
    // Draw a color to the screen based on the ray
    glm::vec3 color(const Ray& r);
    // Output Scene as a PPM Image
    void drawPPM(const char* filename);
    // Output color vec
    glm::vec3 getColor(int objectIndex);

private:
    // Store all of the objects
    std::vector<Sphere*> Objects;
    // Create a camera for our scene
    Camera myCamera;    
};

#endif

