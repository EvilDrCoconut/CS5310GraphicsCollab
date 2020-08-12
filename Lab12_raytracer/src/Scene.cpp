#include "Scene.h"

// Constructor for a scene
Scene::Scene(){
}

// Destructor
Scene::~Scene(){
    for(unsigned int i=0; i < Objects.size(); ++i){
        delete Objects[i]; 
    }
}


// Add another object to our ray tracer
void Scene::addObject(Sphere* s){
    Objects.push_back(s);
}

// Draw a color to the screen based on the ray
glm::vec3 Scene::color(const Ray& r){
    // Keep track of the closest object that
    // we have intersected with. You can think
    // of this exactly like the Z-Buffer.
    float closest_t = 10000.0f;
    // The final output color
    glm::vec3 outColor(0.0f,0.0f,0.0f);
    
    // Now check to see if the ray hits any object in our scene
    // We will only want to output the color of the 'closest T.
    for(unsigned int i=0; i < Objects.size(); ++i){
        float t = Objects[i]->hit_sphere(r);
        
        // TODO:
        // Implement calcuation of normals
        // Implement shading
        // make sure to draw only closest_t!
        if(t  > 0.0f){ // there was a successful intersection
            glm::vec3 normal(r.point_at_parameter(t) - Objects[i]->center);
            normal = glm::normalize(normal);
            // If this 't' is lower than the previous, then update the final outColor
            if(t < closest_t){
                closest_t = t;
                outColor = 0.5f*(glm::vec3(normal.x+1, normal.y+1, normal.z+1));
                outColor *= getColor(i);
            }
        }
    }
    // If we otherwise do not intersect with our sphere, then
    // we just draw a black background.    
    return outColor;
}

glm::vec3 Scene::getColor(int objectIndex){
    if (objectIndex == 0){
        return glm::vec3(1.0f,0.0f,0.0f); // Red color
    }
    if (objectIndex == 1){
        return glm::vec3(0.0f,0.0f,1.0f); // Blue color
    }
    if (objectIndex == 2){
        return glm::vec3(0.0f,1.0f,0.0f); // Green color
    }
    return glm::vec3(1.0f,0.0f,0.0f); // default Red color
}

// This function draws our image.
// The image is drawn in the PPM Format
void Scene::drawPPM(const char* filename){
    // Create a file for which to draw our output to.
    std::ofstream myFile;
    myFile.open(filename);
        
    // Dimensions of the image in X and Y for the "window".
    int nx = 800;
    int ny = 400;
    myFile << "P3\n" << nx << " " << ny << "\n255\n";


    // Draw each pixel
    for(int j = ny-1; j >=0; j--){
        for(int i =0; i < nx; i++){
            // Here we are normalizing our cooridinates across our window.
            // i.e. they will range between 0 and 1
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            // You can always print out the results if you do not believe it!
            // std::cout << u << "," << v << "\n";

            // Rays are cast starting from the origin of our camera
            Ray r = myCamera.get_ray(u,v);
            // Return the color from our scene for which
            // the ray intersects 
            glm::vec3 col = color(r);
            // Render the pixel color
            // Note we write these values out as
            // integers instead of floats
            int int_r = int(255.99*col.x);
            int int_g = int(255.99*col.y);
            int int_b = int(255.99*col.z);
            myFile << int_r << " " << int_g << " " << int_b << "\n"; 
        }
    }

    // Always remember to close your file!
    myFile.close();
}

