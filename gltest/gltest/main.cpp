//
//  main.cpp
//  gltest
//
//  Created by Chenbo Li on 11/2/15.
//  Copyright © 2015 binarythink. All rights reserved.
//

#include "Path.h"
#include "Engine.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include <iostream>

#ifdef _WIN32
#include <GL/freeglut.h>
#else

#endif

Engine* engine;
ShaderProgram* program;

void Draw();
void mouseMove(int x, int y);
void mouseClick(int button, int state, int x, int y);
void mouseWheel(int, int dir, int, int);
void keyboardPress(unsigned char c, int x, int y);

int main(int argc, char * argv[]) {
    
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
    
    if (!program->AddFragmentShaderPath(path)) return 0;
    if (!program->Link()) return 0;
    program->BindAttribute();
    program->BindUniform();
    
    memset(path, 0, 256);
    strcat(path, MODEL_PATH);
    strcat(path, "bunny.ply");
    
    Mesh bunny;
    bunny.Load(path, program);
    
    Scene testScene;
    testScene.addObject(&bunny);
    testScene.setShader(program);
    
    engine->setScene(&testScene);
    
    #ifdef _Win32
    glutMouseWheelFunc(mouseWheel);
    #endif
    
    glutDisplayFunc(Draw);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);

	glutKeyboardUpFunc(keyboardPress);
    glutMainLoop();
    
    return 0;
}

void Draw()
{
    engine->render();
}

void mouseMove(int x, int y)
{
	engine->UpdateMouseStatus(x, y);
}

void mouseClick(int button, int state, int x, int y)
{
	engine->MouseClick(button, state, x, y);
}

void mouseWheel(int, int dir, int, int)
{
	engine->MouseWheel(dir);
}

void keyboardPress(unsigned char c, int, int)
{
	engine->keyRelease(c);
}