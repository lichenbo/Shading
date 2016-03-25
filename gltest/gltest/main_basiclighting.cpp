//
//  main.cpp
//  gltest
//
//  Created by Chenbo Li on 11/2/15.
//  Copyright © 2015 binarythink. All rights reserved.
//
//#define __MAIN_ENTRY
#ifdef __MAIN_ENTRY

#include "gl.h"

#include "Path.h"
#include "Engine.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "Pass.hpp"
#include "FBO.hpp"
#include "Texture.hpp"
#include <iostream>


#ifdef _WIN32
#include <GL/freeglut.h>
#else
#include <GLUT/glut.h>
#endif

Engine* engine;

void Draw();
void mouseMove(int x, int y);
void mouseClick(int button, int state, int x, int y);
void mouseWheel(int, int dir, int, int);
void keyboardPress(unsigned char c, int x, int y);


// ----------------- VARIABLE ZONE --------------------------

auto EyePos = glm::vec3(0.0f, 0.0f, 10.0f);
auto UpPos = glm::vec3(0.0f, 1.0f, 0.0f);
auto LightPos = glm::vec3(10.0f, 10.0f, 10.0f);
auto WatchPos = glm::vec3(0.0f, 0.0f, 0.0f);
auto ProjectionMatrix = glm::perspective(45.0f, 1.0f, 0.5f, 100.0f);
auto ViewMatrix = glm::lookAt(EyePos, WatchPos, UpPos);
auto ViewInverseMatrix = glm::inverse(ViewMatrix);

auto EyePosPtr = glm::value_ptr(EyePos);
auto UpPosPtr = glm::value_ptr(UpPos);
auto LightPosPtr = glm::value_ptr(LightPos);
auto WatchPosPtr = glm::value_ptr(WatchPos);
auto ProjectionMatrixPtr = glm::value_ptr(ProjectionMatrix);
auto ViewMatrixPtr = glm::value_ptr(ViewMatrix);
auto ViewInverseMatrixPtr = glm::value_ptr(ViewInverseMatrix);

auto BunnyModelMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(20.0f));
auto BunnyNormalMatrix = glm::transpose(glm::inverse(BunnyModelMatrix));
auto BunnyModelMatrixPtr = glm::value_ptr(BunnyModelMatrix);
auto BunnyNormalMatrixPtr = glm::value_ptr(BunnyNormalMatrix);

auto SquareModelMatrix = glm::mat4(1.0f);
auto SquareNormalMatrix = glm::transpose(glm::inverse(SquareModelMatrix));

// --------------------------------------------------------


int main(int argc, char * argv[]) {
    
    char path[256];
    engine = new Engine(argc, argv);
    
    ShaderProgram* basicShader = new ShaderProgram();
    
    GET_SHADER_PATH(path, 256, "basic.vert");
    if (!basicShader->AddVertexShaderPath(path)) return 0;
    GET_SHADER_PATH(path, 256, "basic.frag");
    if (!basicShader->AddFragmentShaderPath(path)) return 0;
    if (!basicShader->Link()) return 0;
    
    basicShader->SetAttribVertex("vertex_coord");
    basicShader->SetAttribNormal("normal_coord");
    
    //
    
    ShaderProgram* displayTexShader = new ShaderProgram();
    GET_SHADER_PATH(path, 256, "displayTexture.vert");
    if (!displayTexShader->AddVertexShaderPath(path)) return 0;
    GET_SHADER_PATH(path, 256, "displayTexture.frag");
    if (!displayTexShader->AddFragmentShaderPath(path)) return 0;
    if (!displayTexShader->Link()) return 0;
    
    displayTexShader->SetAttribVertex("vertex_coord");
    displayTexShader->SetAttribTexture("texture_coord");
    
    // --------------SHADER LOADING--------------------------
    
    GET_MODEL_PATH(path, 256, "bunny.ply");
    Mesh bunny;
    bunny.Load(path);
    
    Mesh Square;
    Square.LoadSquare();

    // ---------------MODEL LOADING--------------------------
    
    Scene bunnyScene;
    bunnyScene.addObject(&bunny);
    
    Scene canvasScene;
    canvasScene.addObject(&Square);
    // --------------SCENE LOADING --------------------------
    
    Pass directPass(basicShader, &bunnyScene);
    
    directPass.BindAttribNormal();
    directPass.BindAttribVertex();
    // --------------- BIND ATTRIBUTES ---------------------

    directPass.BindUniformMatrix4("ViewMatrix", &ViewMatrixPtr);
    directPass.BindUniformMatrix4("ViewInverseMatrix", &ViewInverseMatrixPtr);
    directPass.BindUniformMatrix4("ProjectionMatrix", &ProjectionMatrixPtr);
    // ------------- BIND PASS-WISE UNIFORMS---------------

    directPass.MeshBindUniformMatrix4(&bunny, "ModelMatrix", &BunnyModelMatrixPtr);
    directPass.MeshBindUniformMatrix4(&bunny, "NormalMatrix", &BunnyNormalMatrixPtr);
    // ------------BIND MESH-WISE UNIFORMS----------------
    
    FBO fbo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 1);
    
    directPass.SetTarget(&fbo);
    
    Pass renderPass(displayTexShader, &canvasScene);
    renderPass.BindAttribVertex();
    renderPass.BindAttribTexture();
    
    Texture* texture = fbo.GetTexture(0);
	renderPass.BindTexture("texture2D", texture);
    
    // ---------------PASS CONFIG --------------------------
    
    engine->addPass(&directPass);
    engine->addPass(&renderPass);
    
    // ----------------ENGINE------------------------------
    
    #ifdef _WIN32
    glutMouseWheelFunc(mouseWheel);
    #endif
    
    glutDisplayFunc(Draw);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);

	glutKeyboardUpFunc(keyboardPress);
    glutMainLoop();
    
    return 0;
}

void Update()
{
    ViewMatrix = glm::lookAt(EyePos, WatchPos, UpPos);
    ViewInverseMatrix = glm::inverse(ViewMatrix);
}

void Draw()
{
    Update();
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

#endif