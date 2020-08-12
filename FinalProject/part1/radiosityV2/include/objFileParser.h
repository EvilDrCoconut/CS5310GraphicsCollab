/** @file OBJ.h
 *  @brief Class for working with OBJ images
 *  
 *  Class for working with OBJ images specifically.
 *
 *  @bug No known bugs.
 */
#ifndef OBJFILEPARSER_H
#define OBJFILEPARSER_H

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <glad/glad.h>
#include <string>
#include <vector>

class OBJFILEPARSER{
public:
    // Constructor loads a filename with the .obj extension
    OBJFILEPARSER();
    // obj file parser
    void parseObjFile(std::string fileName);
    // mtllib file parser
    void parseMtlibFile(std::string fileName);
    // Destructor clears any memory that has been allocated
    ~OBJFILEPARSER();
    // Returns vertices 
    std::vector<GLfloat> getVextexVector();
    // Returns verts 
    std::vector<GLfloat> getVerts();
    // Returns indices 
    std::vector<GLuint> getVextexIndices();
    // Returns faces 
    std::vector<GLuint> getFaces();
    // get diffuse color map name
    std::string getDiffuseMapName();
    // get normal map name
    std::string getNormalMapName();
    // get the initial file path (this is same for all files used since 
    // they are expected to be in same folder)
    std::string getInitialFilePath(); 
    // read file name 
    void readFileName(std::string fileName);

private:    
    // variable to store line while reading file contents
    std::string line;
    // variable to store first element of line while reading file contents
    std::string type;
    // vector array for storing vertices of triangles 
    std::vector<GLfloat> TempVertices;
    // vector array for storing textures 
    std::vector<GLfloat> TempTextures;
    // vector to hold vertices and textures 
    std::vector<GLfloat> verts;
    // vector array for storing normals
    std::vector<GLfloat> TempNormals;
    // vector array for storing indices of vertices of triangles 
    std::vector<GLuint> VertexIndex;
    // vector array for storing indices of textures of triangles 
    std::vector<GLuint> TextureIndex; 
    // vector array for storing indices of normals of triangles 
    std::vector<GLuint> NormalIndex; 
    // vector storing faces which has vertex index and texture index
    // such that they are in sets of 5: x,y,z,s,t
    std::vector<GLuint> faces;
    // mtllib File Name
    std::string mtllibFileName;
    // material Name
    std::string materialName;
    // diffuse color map file name
    std::string diffuseColorMap;
    // normal map file name
    std::string normalMap;
    // variable to hodl the initial file path that's same for every file used
    std::string filePathTemp;

};



#endif


