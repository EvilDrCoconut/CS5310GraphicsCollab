#include "Object.h"
#include "objFileParser.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// This assert inserts a breakpoint in your code!
// That way we can get the line number and file.
// #define ASSERT(x) if(!(x)) __debugbreak(); (__debugbreak() is only available
// on MSVC)
#define GLCall(x) GLClearErrorStates(); x ; GLCheckError(#x,__LINE__);

// New error handling routine
static void GLClearErrorStates(){
    // Return all of the errors that occur.
    while(glGetError() != GL_NO_ERROR){
        ;
    }
}

// Returns false if an error occurs
static bool GLCheckError(const char* function, int line){
    while(GLenum error = glGetError()){
        // __LINE__ is a special preprocessor macro that
        // Can tell us what line any errors occurred on.
        std::cout << "[OpenGL Error]" << error << "|" << function << " Line: " << line << "\n";
        return false;
    }
    return true;
}

Object::Object(){
    init(); 
}

Object::Object(std::string file){
    setFileName(file);
    std::cout << "file: " << file << std::endl;
    currentObject.readFileName(file);
    initObject(); 
}

Object::~Object(){
    
}

void Object::setFileName(std::string inputFileName){    
    fileName = inputFileName;
}

void Object::LoadTexture(std::string fileName){
        // Load our actual textures
        diffuseMap.LoadTexture(fileName);
}

// Initialization of object
// This could be called in the constructor, or
// it is more typicaly to 'explicitly' call this
// so we create our objects at the correct time
void Object::init(){
        // Setup brickgeometry
        // Be careful not to forget comma's after each line
        // (except the last line of course)!	
		brickgeometry.addVertex(-1.0f,-1.0f,0.0f);   // Position and Normal
        brickgeometry.addTexture(0.0f,0.0f);         // Texture
		            
        brickgeometry.addVertex(1.0f,-1.0f,0.0f);   // Position and Normal
        brickgeometry.addTexture(1.0f, 0.0f);        // Texture

	    brickgeometry.addVertex(1.0f,1.0f,0.0f);    // Position and Normal
       	brickgeometry.addTexture(1.0f, 1.0f);        // Texture
            
        brickgeometry.addVertex(-1.0f,1.0f,0.0f);   // Position and Normal
        brickgeometry.addTexture(0.0f, 1.0f);        // Texture
		// Make our triangles and populate our
		// indices data structure	
		brickgeometry.makeTriangle(0,1,2);
		brickgeometry.makeTriangle(2,3,0);
	
		brickgeometry.gen();

        // Create a buffer and set the stride of information
        myBuffer.CreateBufferNormalMapLayout(14,
											brickgeometry.getSize(),
											brickgeometry.getIndicesSize(),
											brickgeometry.getData(),
											brickgeometry.getIndicesData());

        
        // Setup shaders
        std::string vertexShader = myShader.LoadShader("./shaders/vert.glsl");
        std::string fragmentShader = myShader.LoadShader("./shaders/frag.glsl");
        // Actually create our shader
        myShader.CreateShader(vertexShader,fragmentShader);     
}

void Object::initObject(){

        std::vector<GLfloat> temp = currentObject.getVerts();

        for (int i = 0; i < temp.size(); i++){
            float a = temp[i];
            ++i;
            float b = temp[i];
            ++i;
            float c = temp[i];
            // std::cout << "x,y,z = " << a << ", " << b << ", " << c << ", " << std::endl;
            geometry.addVertex(a,b,c);
            ++i; 
            float u = temp[i];
            ++i;
            float v = temp[i];
            ++i;
            float w = temp[i];
            geometry.addNormal(u,v,w);
            ++i;
            float d = temp[i];
            ++i;
            float e = temp[i];
            // std::cout << "s,t   = " << d << ", " << e << std::endl;
            geometry.addTexture(d,e);
        }

        std::vector<GLuint> tempIndices = currentObject.getVextexIndices(); 

	    for (int i = 0; i < tempIndices.size(); i++){
            int a = tempIndices[i];
            ++i;
            int b = tempIndices[i];
            ++i;
            int c = tempIndices[i];
            geometry.makeTriangle(a,b,c);
        }

		geometry.gen();

        // Create a buffer and set the stride of information
        myBuffer.CreateBufferNormalMapLayout(14,
											geometry.getSize(),
											geometry.getIndicesSize(),
											geometry.getData(),
											geometry.getIndicesData());

        // Load our actual textures
        std::string startingFilePath = currentObject.getInitialFilePath();
        std::string diffuseMapFileName = currentObject.getDiffuseMapName();
        std::string diffuseMapFilePath = startingFilePath + diffuseMapFileName;
        std::string normalMapFileName = currentObject.getNormalMapName();
        std::string normalMapFilePath = startingFilePath + normalMapFileName;
        diffuseMap.LoadTexture(diffuseMapFilePath);
        normalMap.LoadTexture(normalMapFilePath);
        // Setup shaders
        std::string vertexShader = myShader.LoadShader("./shaders/vert.glsl");
        std::string fragmentShader = myShader.LoadShader("./shaders/frag.glsl");
        // Actually create our shader
        myShader.CreateShader(vertexShader,fragmentShader);
       
}


// Bind everything we need in our object
// Generally this is called in update() and render()
// before we do any actual work with our object
void Object::Bind(){
        // Make sure we are updating the correct 'buffers'
        myBuffer.Bind();
		// Diffuse map is 0 by default, but it is good to set it explicitly
        diffuseMap.Bind(0);
		// TODO:
		// We need to set the texture slot explicitly for the normal map  
		normalMap.Bind(1);
  		// Select our appropriate shader
	    myShader.Bind();
}


void Object::update(unsigned int screenWidth, unsigned int screenHeight){
		Bind();
		// TODO: Read and understand
        // For our object, we apply the texture in the following way
        // Note that we set the value to 0, because we have bound
        // our texture to slot 0.
        myShader.setUniform1i("u_DiffuseMap",0); 
        // If we want to load another texture, we assign it to another slot
		myShader.setUniform1i("u_NormalMap",1);
 
         // Here we apply the 'view' matrix which creates perspective.
        // The first argument is 'field of view'
        // Then perspective
        // Then the near and far clipping plane.
        // Note I cannot see anything closer than 0.1f units from the screen.
        // TODO: In the future this type of operation would be abstracted away
        //       in a camera class.
        projectionMatrix = glm::perspective(45.0f,(float)screenWidth/(float)screenHeight,0.1f,20.0f);
        // Set the uniforms in our current shader
        myShader.setUniformMatrix4fv("modelTransformMatrix", &transform.getInternalMatrix()[0][0]);
        myShader.setUniformMatrix4fv("view",
                                    &Camera::instance().getWorldToViewmatrix()[0][0]);
        myShader.setUniformMatrix4fv("projectionMatrix", &projectionMatrix[0][0]);

		// Set in a light source position
		myShader.setUniform3f("lightPos",-7.0f,0.8f,-4.0f);	
		// Set a view and a vector
		myShader.setUniform3f("viewPos",0.0f,0.0f,0.0f);
}

void Object::render(int flagObj){
    if(flagObj == 1){
	    Bind();
		//Render data
    	glDrawElements(GL_TRIANGLES,
					geometry.getIndicesSize(), // The number of indicies, not triangles.
					GL_UNSIGNED_INT, // Make sure the data type matches
					nullptr);       // Offset pointer to the data. nullptr because we are currently bound:	
    }
    if(flagObj == 2){
	    Bind();
		//Render data
    	glDrawElements(GL_TRIANGLES,
					brickgeometry.getIndicesSize(), // The number of indicies, not triangles.
					GL_UNSIGNED_INT, // Make sure the data type matches
					nullptr);       // Offset pointer to the data. nullptr because we are currently bound:	
    }
}

// Returns the actual transform stored in our object
// which can then be modified
Transform& Object::getTransform(){
    return transform; 
}
