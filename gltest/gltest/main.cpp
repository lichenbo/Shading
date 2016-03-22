//
//  main.cpp
//  gltest
//
//  Created by Chenbo Li on 11/2/15.
//  Copyright © 2015 binarythink. All rights reserved.
//

#include "gl.h"

#include "Path.h"
#include "Engine.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "Pass.hpp"
#include "FBO.hpp"
#include <iostream>


#ifdef _WIN32
#include <GL/freeglut.h>
#else
#include <GLUT/glut.h>
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
    bunny.SetModelTrans(glm::scale(glm::mat4(1.0f),glm::vec3(20.0f)));

    
    Scene testScene;
    testScene.addObject(&bunny);
    
    Pass directPass(program, &testScene);
    
    FBO fbo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 1);
    
    directPass.SetTarget(&fbo);
    
    engine->addPass(&directPass);
    
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


void addSpin(float delta_x)
{
    delta_x *= 0.01;
    EyePos = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)delta_x, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(EyePos,1.0f));
    
}

void addTilt(float delta_y)
{
    delta_y *= 0.01;
    EyePos = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)delta_y, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(EyePos,1.0f));
    
}

void addTrans(float delta_move)
{
    EyePos += glm::vec3(delta_move, 0.0f, 0.0f);
    WatchPos += glm::vec3(delta_move, 0.0f, 0.0f);
}

void addZoom(float dir)
{
    EyePos = glm::vec3(glm::translate(glm::mat4(1.0f), glm::vec3(dir, dir, dir)) * glm::vec4(EyePos, 1.0f));
}

void mouseMove(int x, int y)
{
	engine->UpdateMouseStatus(x, y, addSpin, addTilt);
}

void mouseClick(int button, int state, int x, int y)
{
	engine->MouseClick(button, state, x, y);
}

void mouseWheel(int, int dir, int, int)
{
	engine->MouseWheel(dir, addZoom);
}

void keyboardPress(unsigned char c, int, int)
{
	engine->keyRelease(c, addTrans);
}

