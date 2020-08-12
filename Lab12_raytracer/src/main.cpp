#include <glm/glm.hpp>  // Used for math operations

#include "Scene.h"
#include "Sphere.h"

// Main entry point to program
int main(){

    // Create a scene with our objects added to it.
    Scene myScene;
    // Create some sphere objects
    // The first parameter is the center, and the second the radius
    Sphere* sphere1 = new Sphere(glm::vec3(0.0f,0.0f,-1.0f),0.5f);
    // TODO: Add some more spheres!    
    // TODO: Add some spheres into your scene
    Sphere* sphere2 = new Sphere(glm::vec3(1.0f,0.0f,-1.0f),0.25f);
    Sphere* sphere3 = new Sphere(glm::vec3(1.0f,-75.0f,-75.0f),100.0f);
    myScene.addObject(sphere1);
    myScene.addObject(sphere2);
    myScene.addObject(sphere3);

    // Draw the PPM image
    myScene.drawPPM("sphere.ppm");   

    return 0;
}


