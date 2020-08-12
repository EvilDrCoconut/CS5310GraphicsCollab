#ifndef OBJECT_H
#define OBJECT_H

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <glad/glad.h>
#include <vector>
#include <string>

#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"
#include "Transform.h"
#include "Geometry.h"
#include "BrickGeometry.h"
#include "objFileParser.h"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Purpose:
// An abstraction to create multiple objects
//
//
class Object{
public:
    // Object Constructor
    Object();
    // Another Object Constructor
    Object(std::string file);
    // Object destructor
    ~Object();
    // Initialization routine
    void init();
    void initObject();
    // Updates and transformatinos applied to object
    void update(unsigned int screenWidth, unsigned int screenHeight);
    // How to draw the object
    void render(int flagObj);
    // Returns an objects transform
    Transform& getTransform();
    // sets file name
    void setFileName(std::string file);
    // Loads a specific texture
    void LoadTexture(std::string fileName);
private:
	// Helper method for when we are ready to draw or update our object
	void Bind();
    // For now we have one shader per object.
    Shader myShader;
    // For now we have one buffer per object.
    Buffer myBuffer;
    // For now we have one diffuse map and one normal map per object
    Texture diffuseMap;
    // Store normal map
    Texture normalMap;
    // Store the objects transformations
    Transform transform; 
    // Store the 'camera'
    glm::mat4 projectionMatrix;
	// Store the objects Geometry
	Geometry geometry;
    // Store the objects Geometry for Brick room
	BrickGeometry brickgeometry;
    // stores file name 
    std::string fileName;
    // current object that is received from obj parser
    OBJFILEPARSER currentObject;
};


#endif
