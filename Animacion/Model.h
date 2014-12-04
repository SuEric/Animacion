//
//  Model.h
//  Animacion
//
//  Created by sueric on 26/09/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#ifndef Animacion_Model_h
#define Animacion_Model_h

#define MAX_VERTICES 80000

#include "3dModelBasicStructs.h"

#include <fbxsdk.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class Model
{
private:
    char Name[25];
    
    vertex vertices[MAX_VERTICES];
    texturecoords txt[MAX_VERTICES];
    
    float *normals;
    int numNormals;
    
    int *indices;
    int numIndices;
    
    int numVertices;
    
public:
    
    Model(char*);
    ~Model();
    
    void ShowDetails();
    
    char* GetModelName();
    void  SetModelName(char*);
    void  GetFbxInfo(FbxNode*);
    void  RenderModel();
};

#endif
