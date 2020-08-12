#include "objFileParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>

// Constructor loads a filename with the .obj extension
OBJFILEPARSER::OBJFILEPARSER(){
}

void OBJFILEPARSER::readFileName(std::string fileName){
    parseObjFile(fileName);
}

void OBJFILEPARSER::parseObjFile(std::string fileName) {
    // Opens a file to output
    std::ifstream inFile;

    // Open the file
    inFile.open(fileName);

    // Throw an error if file doesn't open
    if(!inFile.is_open()){
        std::cout << "Error: cannot open the file! \n" <<
        "Tip: Make sure the filepath is correct." << std::endl;
        return; // Don't continue executing the program anymore
    }

    while(std::getline(inFile, line)){
        if(line == "" || line[0] == '#')// Skip and continue to next line
            continue;

        std::istringstream lineStream(line);
        lineStream >> type;

        // line starts with 'v'
        if(type == "v"){
            float Vertex[3];
            sscanf(line.c_str(), "%*s %f %f %f", &Vertex[0], &Vertex[1], &Vertex[2]);
            TempVertices.push_back(Vertex[0]);
            TempVertices.push_back(Vertex[1]);
            TempVertices.push_back(Vertex[2]);
        }

        // line starts with 'vt'
        if(type == "vt"){
            float Textures[2];
            sscanf(line.c_str(), "%*s %f %f", &Textures[0], &Textures[1]);
            TempTextures.push_back(Textures[0]);
            TempTextures.push_back(Textures[1]);
        }

        // line starts with 'vn'
        if(type == "vn"){
            float Normal[3];
            sscanf(line.c_str(), "%*s %f %f %f", &Normal[0], &Normal[1], &Normal[2]);
            TempNormals.push_back(Normal[0]);
            TempNormals.push_back(Normal[1]);
            TempNormals.push_back(Normal[2]);
        }

        // line starts with 'f'
        if(type == "f"){
            size_t n = std::count(line.begin(), line.end(), '/');
            if (n == 6){
                float FaceVertices[3];
                float FaceTextures[3];
                float FaceNormals[3];

                sscanf(line.c_str(), "%*s %f/%f/%f %f/%f/%f %f/%f/%f", &FaceVertices[0], &FaceTextures[0], &FaceNormals[0], &FaceVertices[1], &FaceTextures[1], &FaceNormals[1], &FaceVertices[2], &FaceTextures[2], &FaceNormals[2]);
                faces.push_back(FaceVertices[0]-1);
                faces.push_back(FaceNormals[0]-1);
                faces.push_back(FaceTextures[0]-1);
    
                faces.push_back(FaceVertices[1]-1);
                faces.push_back(FaceNormals[1]-1);
                faces.push_back(FaceTextures[1]-1);
                
                faces.push_back(FaceVertices[2]-1);
                faces.push_back(FaceNormals[2]-1);
                faces.push_back(FaceTextures[2]-1);
            }
            if (n == 8){
                float FaceVertices[4];
                float FaceTextures[4];
                float FaceNormals[4];

                sscanf(line.c_str(), "%*s %f/%f/%f %f/%f/%f %f/%f/%f %f/%f/%f", &FaceVertices[0], &FaceTextures[0], &FaceNormals[0], &FaceVertices[1], &FaceTextures[1], &FaceNormals[1], &FaceVertices[2], &FaceTextures[2], &FaceNormals[2], &FaceVertices[3], &FaceTextures[3], &FaceNormals[3]);
                
                faces.push_back(FaceVertices[0]-1);
                faces.push_back(FaceNormals[0]-1);
                faces.push_back(FaceTextures[0]-1);
    
                faces.push_back(FaceVertices[1]-1);
                faces.push_back(FaceNormals[1]-1);
                faces.push_back(FaceTextures[1]-1);
                
                faces.push_back(FaceVertices[2]-1);
                faces.push_back(FaceNormals[2]-1);
                faces.push_back(FaceTextures[2]-1);

                faces.push_back(FaceVertices[3]-1);
                faces.push_back(FaceNormals[3]-1);
                faces.push_back(FaceTextures[3]-1);
            }
        }

        if(type == "mtllib"){
            lineStream >> type;
            mtllibFileName = type;
            // std::cout << "mtllibFileName: " << mtllibFileName << std::endl;
            std::size_t found = fileName.find_last_of("/");
            // reference: http://www.cplusplus.com/reference/string/string/find_last_of/
            filePathTemp = fileName.substr(0,found);
            filePathTemp = filePathTemp + "/";
            // std::cout << "initial file path: " << filePathTemp << std::endl;
            std::string mtllibFilePath = filePathTemp + mtllibFileName;
            // std::cout << "mtllib file path: " << mtllibFilePath << std::endl;
            parseMtlibFile(mtllibFilePath);
        }

    }

    // for (int a = 0; a < 8; a++){
    //     std::cout << "f[" << a << "] = " << faces[a]+1 << std::endl;
    //     a++;
    //     std::cout << "f[" << a << "] = " << faces[a]+1 << std::endl;
    //     a++;
    //     std::cout << "f[" << a << "] = " << faces[a]+1 << std::endl;
    //     std::cout << " " << std::endl;
    // }

    // store verts in thsi order: vx, vy, vz, vnx, vny, vnz, s, t
    // where {vx, vy, vz} are vertex coordinates,
    //       {vnx, vny, vnz} are normal coordinates, and 
    //       {s, t} are texture coordinates
    int count = 0;
    for(int i = 0; i < faces.size(); i++){
            int a = faces[i]; // get vertex index
            int b = a*3;
            verts.push_back(TempVertices[b]);
            ++b;
            verts.push_back(TempVertices[b]);
            ++b;
            verts.push_back(TempVertices[b]);

            VertexIndex.push_back(count++);
    
            i +=1;
            int p = faces[i]; // get normal index
            int q = p*3;
            verts.push_back(TempNormals[q]);
            ++q;
            verts.push_back(TempNormals[q]);
            ++q;
            verts.push_back(TempNormals[q]);
    
            i +=1;
            int c = faces[i]; // get texture index
            int d = c*2;
            verts.push_back(TempTextures[d]);
            ++d;
            verts.push_back(TempTextures[d]);
    }

    // for (int a = 0; a < 20; a++){
    //     std::cout << "v[" << a << "] = " << verts[a] << std::endl;
    //     a++;
    //     std::cout << "v[" << a << "] = " << verts[a] << std::endl;
    //     a++;
    //     std::cout << "v[" << a << "] = " << verts[a] << std::endl;
    //     a++;
    //     std::cout << "vn[" << a << "] = " << verts[a] << std::endl;
    //     a++;
    //     std::cout << "vn[" << a << "] = " << verts[a] << std::endl;
    //     a++;
    //     std::cout << "vn[" << a << "] = " << verts[a] << std::endl;
    //     a++;
    //     std::cout << "vt[" << a << "] = " << verts[a] << std::endl;
    //     a++;
    //     std::cout << "vt[" << a << "] = " << verts[a] << std::endl;
    //     std::cout << " " << std::endl;
    // }

         // check if the last 5 values added to verts are already present
        int z = verts.size();

        for (int a = 0; a < verts.size(); a+=8){
            if(verts[z-7] == verts[++a] 
            &&verts[z-6] == verts[++a] 
            &&verts[z-5] == verts[++a] 
            &&verts[z-4] == verts[++a] 
            && verts[z-3] == verts[++a]
            && verts[z-2] == verts[++a]
            && verts[z-1] == verts[++a]
            && verts[z] == verts[++a]){
            // remove these values since they exist already
                verts.pop_back();
                verts.pop_back();
                verts.pop_back();
                verts.pop_back();
                verts.pop_back();
                verts.pop_back();
                verts.pop_back();
                verts.pop_back();
            }
        }
    // Close the file 
    inFile.close();
}

void OBJFILEPARSER::parseMtlibFile(std::string fileName){
    // Opens a file to output
    std::ifstream inFile;

    // Open the file
    inFile.open(fileName);

    // Throw an error if file doesn't open
    if(!inFile.is_open()){
        std::cout << "Error: cannot open the file! \n" <<
        "Tip: Make sure the filepath is correct." << std::endl;
        return; // Don't continue executing the program anymore
    }

    while(std::getline(inFile, line)){
    if(line == "" || line[0] == '#')// Skip and continue to next line
        continue;

    std::istringstream lineStream(line);
    lineStream >> type;

    if(type == "newmtl"){
        lineStream >> type;
        materialName = type;
    }

    if(type == "map_Kd"){
        lineStream >> type;
        diffuseColorMap = type;
        // std::cout << "diffuseColorMap" << diffuseColorMap << std::endl;
    }

    if(type == "map_Bump"){
        lineStream >> type;
        normalMap = type;
        // std::cout << "normalMap" << normalMap << std::endl;
    }

 }
    // Close the file 
    inFile.close();
}

// Destructor clears any memory that has been allocated
OBJFILEPARSER::~OBJFILEPARSER(){
}

std::vector<GLfloat> OBJFILEPARSER::getVextexVector(){
    return TempVertices;
}

std::vector<GLfloat> OBJFILEPARSER::getVerts(){
    return verts;
}

std::vector<GLuint> OBJFILEPARSER::getVextexIndices() {
    return VertexIndex;
}

std::vector<GLuint> OBJFILEPARSER::getFaces() {
    return faces;
}

std::string OBJFILEPARSER::getDiffuseMapName(){
    return diffuseColorMap;
}

std::string OBJFILEPARSER::getNormalMapName(){
    return normalMap;
}

std::string OBJFILEPARSER::getInitialFilePath(){
    return filePathTemp;
}


