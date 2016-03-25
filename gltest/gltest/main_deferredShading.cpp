//
//  main.cpp
//  gltest
//
//  Created by Chenbo Li on 11/2/15.
//  Copyright © 2015 binarythink. All rights reserved.
//
#define __MAIN_ENTRY
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
auto WatchPos = glm::vec3(0.0f, 0.0f, 0.0f);
auto ProjectionMatrix = glm::perspective(45.0f, 1.0f, 0.5f, 100.0f);
auto ViewMatrix = glm::lookAt(EyePos, WatchPos, UpPos);
auto ViewInverseMatrix = glm::inverse(ViewMatrix);
auto AmbientLight = glm::vec3(1.0, 1.0, 1.0);

// Bunny1
auto Bunny1ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f));
auto Bunny1NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny1Diffuse = glm::vec3(0.0, 0.5, 0.5);
auto Bunny1Specular = glm::vec3(0.5, 0.5, 0.0);
// Bunny2
auto Bunny2ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(20.0f));
auto Bunny2NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny2Diffuse = glm::vec3(0.5, 0.5, 0.0);
auto Bunny2Specular = glm::vec3(0.5, 0.5, 0.0);
// Bunny3
auto Bunny3ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(20.0f));
auto Bunny3NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny3Diffuse = glm::vec3(0.5, 0.0, 0.5);
auto Bunny3Specular = glm::vec3(0.5, 0.5, 0.0);


// Square
auto SquareModelMatrix = glm::mat4(1.0f);
auto SquareNormalMatrix = glm::transpose(glm::inverse(SquareModelMatrix));

// Light1
auto Light1Pos = glm::vec3(10.0f, 10.0f, 10.0f);
auto Light1ModelMatrix = glm::translate(glm::mat4(1.0f), Light1Pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
auto Light1NormalMatrix = glm::transpose(glm::inverse(Light1ModelMatrix));
auto Light1Diffuse = glm::vec3(1.0, 1.0, 1.0);
auto Light1Specular = glm::vec3(1.0, 1.0, 1.0);

// -------------------- POINTERS ZONE ------------------------
auto EyePosPtr = glm::value_ptr(EyePos);
auto UpPosPtr = glm::value_ptr(UpPos);
auto WatchPosPtr = glm::value_ptr(WatchPos);
auto ProjectionMatrixPtr = glm::value_ptr(ProjectionMatrix);
auto ViewMatrixPtr = glm::value_ptr(ViewMatrix);
auto ViewInverseMatrixPtr = glm::value_ptr(ViewInverseMatrix);
auto AmbientLightPtr = glm::value_ptr(AmbientLight);
auto Bunny1ModelMatrixPtr = glm::value_ptr(Bunny1ModelMatrix);
auto Bunny1NormalMatrixPtr = glm::value_ptr(Bunny1NormalMatrix);
auto Bunny1DiffusePtr = glm::value_ptr(Bunny1Diffuse);
auto Bunny1SpecularPtr = glm::value_ptr(Bunny1Specular);
auto Bunny2ModelMatrixPtr = glm::value_ptr(Bunny2ModelMatrix);
auto Bunny2NormalMatrixPtr = glm::value_ptr(Bunny2NormalMatrix);
auto Bunny2DiffusePtr = glm::value_ptr(Bunny2Diffuse);
auto Bunny2SpecularPtr = glm::value_ptr(Bunny2Specular);
auto Bunny3ModelMatrixPtr = glm::value_ptr(Bunny3ModelMatrix);
auto Bunny3NormalMatrixPtr = glm::value_ptr(Bunny3NormalMatrix);
auto Bunny3DiffusePtr = glm::value_ptr(Bunny3Diffuse);
auto Bunny3SpecularPtr = glm::value_ptr(Bunny3Specular);
auto SquareModelMatrixPtr = glm::value_ptr(SquareModelMatrix);
auto SquareNormalMatrixPtr = glm::value_ptr(SquareNormalMatrix);
auto Light1PosPtr = glm::value_ptr(Light1Pos);
auto Light1ModelMatrixPtr = glm::value_ptr(Light1ModelMatrix);
auto Light1NormalMatrixPtr = glm::value_ptr(Light1NormalMatrix);
auto Light1DiffusePtr = glm::value_ptr(Light1Diffuse);
auto Light1SpecularPtr = glm::value_ptr(Light1Specular);
// --------------------------------------------------------


int main(int argc, char * argv[]) {

	char path[256];
	engine = new Engine(argc, argv);

	ShaderProgram* defergbufferShader = new ShaderProgram();
	FBO fbo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 4);

	GET_SHADER_PATH(path, 256, "defergbuffer.vert");
	if (!defergbufferShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_PATH(path, 256, "defergbuffer.frag");
	if (!defergbufferShader->AddFragmentShaderPath(path)) return 0;
	if (!defergbufferShader->Link()) return 0;

	defergbufferShader->SetAttribVertex("vertex_coord");
	defergbufferShader->SetAttribNormal("normal_coord");

	//
	ShaderProgram* ambientShader = new ShaderProgram();
	GET_SHADER_PATH(path, 256, "deferAmbientLight.vert");
	if (!ambientShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_PATH(path, 256, "deferAmbientLight.frag");
	if (!ambientShader->AddFragmentShaderPath(path)) return 0;
	if (!ambientShader->Link()) return 0;
	ambientShader->SetAttribVertex("vertex_coord");

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
	Mesh bunny1, bunny2, bunny3;
	bunny1.Load(path);
	bunny2.Load(path);
	bunny3.Load(path);

	GET_MODEL_PATH(path, 256, "sphere.ply");
	Mesh Light1;
	Light1.Load(path);

	Mesh Square;
	Square.LoadSquare();

	// ---------------MODEL LOADING--------------------------

	Scene bunnyScene;
	bunnyScene.addObject(&bunny1);
	bunnyScene.addObject(&bunny2);
	bunnyScene.addObject(&bunny3);
	bunnyScene.addObject(&Light1);

	Scene canvasScene;
	canvasScene.addObject(&Square);
	// --------------SCENE LOADING --------------------------

	Pass gbufferPass(defergbufferShader, &bunnyScene);
	Pass ambientPass(ambientShader, &canvasScene);
	Pass renderPass(displayTexShader, &canvasScene);

	gbufferPass.BindAttribNormal();
	gbufferPass.BindAttribVertex();
	ambientPass.BindAttribVertex();
	renderPass.BindAttribVertex();
	renderPass.BindAttribTexture();

	// --------------- BIND ATTRIBUTES ---------------------

	gbufferPass.BindUniformMatrix4("ViewMatrix", &ViewMatrixPtr);
	gbufferPass.BindUniformMatrix4("ViewInverseMatrix", &ViewInverseMatrixPtr);
	gbufferPass.BindUniformMatrix4("ProjectionMatrix", &ProjectionMatrixPtr);
	ambientPass.BindUniformVec3("ambientColor", &AmbientLightPtr);
	// ------------- BIND PASS-WISE UNIFORMS---------------

	gbufferPass.MeshBindUniformMatrix4(&bunny1, "ModelMatrix", &Bunny1ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&bunny1, "NormalMatrix", &Bunny1NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&bunny1, "diffuse", &Bunny1DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&bunny1, "specular", &Bunny1SpecularPtr);
	gbufferPass.MeshBindUniformMatrix4(&bunny2, "ModelMatrix", &Bunny2ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&bunny2, "NormalMatrix", &Bunny2NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&bunny2, "diffuse", &Bunny2DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&bunny2, "specular", &Bunny2SpecularPtr);
	gbufferPass.MeshBindUniformMatrix4(&bunny3, "ModelMatrix", &Bunny3ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&bunny3, "NormalMatrix", &Bunny3NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&bunny3, "diffuse", &Bunny3DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&bunny3, "specular", &Bunny3SpecularPtr);
	gbufferPass.MeshBindUniformMatrix4(&Light1, "ModelMatrix", &Light1ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&Light1, "NormalMatrix", &Light1NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&Light1, "diffuse", &Light1DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&Light1, "specular", &Light1SpecularPtr);
	renderPass.MeshBindUniformMatrix4(&Square, "ModelMatrix", &SquareModelMatrixPtr);

	// ------------BIND MESH-WISE UNIFORMS----------------

	gbufferPass.SetTarget(&fbo);

	Texture* texture = fbo.GetTexture(0);
	renderPass.BindTexture("texture2D", texture);

	// ---------------PASS CONFIG --------------------------

	engine->addPass(&gbufferPass);
	engine->addPass(&renderPass);
	//engine->addPass(&ambientPass);

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
	EyePos = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)delta_x, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(EyePos, 1.0f));

}

void addTilt(float delta_y)
{
	delta_y *= 0.01;
	EyePos = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)delta_y, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(EyePos, 1.0f));

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