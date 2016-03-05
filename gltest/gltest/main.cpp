//
//  main.cpp
//  gltest
//
//  Created by Chenbo Li on 11/2/15.
//  Copyright © 2015 binarythink. All rights reserved.
//

#include "Engine.hpp"
#include "Mesh.hpp"
#include <iostream>

#ifdef _WIN32
#include <GL/freeglut.h>
#else

#endif

Engine* engine;
ShaderProgram* program;

void Draw();

int main(int argc, char * argv[]) {
    
    const char * SHADER_PATH = "Shader/";
    
    engine = new Engine(argc, argv);
    program = new ShaderProgram();
    
    char path[256];
    memset(path, 0, 256);
    strcat(path, SHADER_PATH);
    strcat(path, "basic.vert");
    
    if (!program->AddVertexShaderPath(path))
    {
        return 0;
    }
    
    memset(path, 0, 256);
    strcat(path, SHADER_PATH);
    strcat(path, "basic.frag");
    
    if (!program->AddFragmentShaderPath(path))
    {
        return 0;
    }
    if (!program->Link())
    {
        return 0;
    }
    
    Mesh m;
    engine->addMesh(&m);
    
    glutDisplayFunc(Draw);
    glutMainLoop();
    
    return 0;
}

void Draw()
{
    engine->render(program);
}