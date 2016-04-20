//
//  main.cpp
//  gltest
//
//  Created by Chenbo Li on 11/2/15.
//  Copyright ? 2015 binarythink. All rights reserved.
//
#define __MAIN_ENTRY
#ifdef __MAIN_ENTRY

#include "gl.h"

#include "Path.h"
#include "Engine.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "Pass.hpp"
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
auto EyePos = glm::vec3(0.0f, 0.0f, 3.0f);
auto UpPos = glm::vec3(0.0f, 1.0f, 0.0f);
auto WatchPos = glm::vec3(0.0f, 0.0f, 0.0f);
auto ProjectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 20.0f);
auto ViewMatrix = glm::lookAt(EyePos, WatchPos, UpPos);
auto ViewInverseMatrix = glm::inverse(ViewMatrix);

// Fire
//auto FireControlPoints = std::vector<glm::vec3>();

// -------------------- POINTERS ZONE ------------------------
auto EyePosPtr = glm::value_ptr(EyePos);
auto UpPosPtr = glm::value_ptr(UpPos);
auto WatchPosPtr = glm::value_ptr(WatchPos);
auto ProjectionMatrixPtr = glm::value_ptr(ProjectionMatrix);
auto ViewMatrixPtr = glm::value_ptr(ViewMatrix);
auto ViewInverseMatrixPtr = glm::value_ptr(ViewInverseMatrix);


// --------------------------------------------------------

int main(int argc, char * argv[]) {

	std::vector<glm::vec3> FireControlPoints;
	FireControlPoints.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	FireControlPoints.push_back(glm::vec3(1.0f, 0.0f, 0.2f));
	FireControlPoints.push_back(glm::vec3(-1.0f, 0.0f, 0.6f));
	FireControlPoints.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	char path[256];
	engine = new Engine(argc, argv);

	ShaderProgram* fireShader = new ShaderProgram();
	GET_SHADER_VOLFIRE_PATH(path, 256, "fire.vert");
	if (!fireShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_VOLFIRE_PATH(path, 256, "fire.geom");
	if (!fireShader->AddGeometryShaderPath(path)) return 0;
	GET_SHADER_VOLFIRE_PATH(path, 256, "fire.frag");
	if (!fireShader->AddFragmentShaderPath(path)) return 0;
	if (!fireShader->Link()) return 0;
	fireShader->SetAttribVertex("vertex_coord");
	fireShader->SetAttribNormal("vertex_normal");

	// --------------SHADER LOADING--------------------------

	Mesh Fire;
	Fire.LoadBSpline(FireControlPoints, 2);
	// ---------------MODEL LOADING--------------------------

	Scene FireScene;
	FireScene.addObject(&Fire);

	// --------------SCENE LOADING --------------------------

	Pass directPass(fireShader, &FireScene);

	directPass.BindAttribNormal();
	directPass.BindAttribVertex();

	// --------------- BIND ATTRIBUTES ---------------------

	directPass.BindUniformMatrix4("ViewMatrix", &ViewMatrixPtr);
	directPass.BindUniformMatrix4("ProjectionMatrix", &ProjectionMatrixPtr);
    directPass.BindUniformVec3("eyePos", &EyePosPtr);


	// ------------- BIND PASS-WISE UNIFORMS---------------

	// ---------------PASS CONFIG --------------------------
	engine->addPass(&directPass);


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