//
//  main.cpp
//  gltest
//
//  Created by Chenbo Li on 11/2/15.
//  Copyright � 2015 binarythink. All rights reserved.
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
auto EyePos = glm::vec3(0.0f, 0.0f, 3.0f);
auto UpPos = glm::vec3(0.0f, 1.0f, 0.0f);
auto WatchPos = glm::vec3(0.0f, 0.0f, 0.0f);
auto ProjectionMatrix = glm::perspective(45.0f, 1.0f, 0.5f, 10.0f);
auto ViewMatrix = glm::lookAt(EyePos, WatchPos, UpPos);
auto ViewInverseMatrix = glm::inverse(ViewMatrix);
auto AmbientLight = glm::vec3(1.0, 1.0, 1.0);

// Bunny1
auto Bunny1ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Bunny1NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny1Diffuse = glm::vec3(0.0, 0.5, 0.5);
auto Bunny1Specular = glm::vec3(0.5, 0.5, 0.0);
// Bunny2
auto Bunny2ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Bunny2NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny2Diffuse = glm::vec3(0.5, 0.5, 0.0);
auto Bunny2Specular = glm::vec3(0.5, 0.5, 0.0);
// Bunny3
auto Bunny3ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Bunny3NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny3Diffuse = glm::vec3(0.5, 0.0, 0.5);
auto Bunny3Specular = glm::vec3(0.5, 0.5, 0.0);

//Square1
auto Square1ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)) * glm::scale(glm::mat4(1.0f),glm::vec3(3.0f));
auto Square1NormalMatrix = glm::transpose(glm::inverse(Square1ModelMatrix));
auto Square1Diffuse = glm::vec3(1.0, 0.0, 0.0);
auto Square1Specular = glm::vec3(1.0, 1.0, 1.0);

auto Square2ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f),glm::vec3(3.0f)) * glm::rotate(glm::mat4(1.0f),glm::radians(90.0f),glm::vec3(0.0f,1.0f,0.0f));
auto Square2NormalMatrix = glm::transpose(glm::inverse(Square2ModelMatrix));
auto Square2Diffuse = glm::vec3(0.0, 1.0, 0.0);
auto Square2Specular = glm::vec3(1.0, 1.0, 1.0);

auto Square3ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
auto Square3NormalMatrix = glm::transpose(glm::inverse(Square3ModelMatrix));
auto Square3Diffuse = glm::vec3(0.0, 0.0, 1.0);
auto Square3Specular = glm::vec3(1.0, 1.0, 1.0);

auto Square4ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
auto Square4NormalMatrix = glm::transpose(glm::inverse(Square4ModelMatrix));
auto Square4Diffuse = glm::vec3(1.0, 0.5, 0.5);
auto Square4Specular = glm::vec3(1.0, 1.0, 1.0);

auto Square5ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
auto Square5NormalMatrix = glm::transpose(glm::inverse(Square5ModelMatrix));
auto Square5Diffuse = glm::vec3(0.5, 1.0, 0.5);
auto Square5Specular = glm::vec3(1.0, 1.0, 1.0);

auto Square6ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
auto Square6NormalMatrix = glm::transpose(glm::inverse(Square6ModelMatrix));
auto Square6Diffuse = glm::vec3(0.5, 0.5, 1.0);
auto Square6Specular = glm::vec3(1.0, 1.0, 1.0);

// Light1: Global light
auto Light1Pos = glm::vec3(2.0f);
auto Light1ModelMatrix = glm::translate(glm::mat4(1.0f), Light1Pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
auto Light1NormalMatrix = glm::transpose(glm::inverse(Light1ModelMatrix));
auto Light1Diffuse = glm::vec3(1.0, 1.0, 1.0);
auto Light1Specular = glm::vec3(1.0, 1.0, 1.0);

// For Shadow Pass
auto Light1ViewMatrix = glm::lookAt(Light1Pos, WatchPos, UpPos);
auto Light1ShadowMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)) * ProjectionMatrix * Light1ViewMatrix;

// Light2: Local light
auto Light2Pos = glm::vec3(-0.5f);
auto Light2ModelMatrix = glm::translate(glm::mat4(1.0f), Light2Pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
auto Light2NormalMatrix = glm::transpose(glm::inverse(Light2ModelMatrix));
auto Light2Diffuse = glm::vec3(1.0, 1.0, 1.0);
auto Light2Specular = glm::vec3(0.0, 0.0, 1.0);
auto Light2Range = glm::vec3(1.0);

// Light3: Local light
auto Light3Pos = glm::vec3(0.25f);
auto Light3ModelMatrix = glm::translate(glm::mat4(1.0f), Light3Pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
auto Light3NormalMatrix = glm::transpose(glm::inverse(Light3ModelMatrix));
auto Light3Diffuse = glm::vec3(1.0, 1.0, 1.0);
auto Light3Specular = glm::vec3(0.0, 0.0, 1.0);
auto Light3Range = glm::vec3(1.0);


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
auto Light1PosPtr = glm::value_ptr(Light1Pos);
auto Light1ModelMatrixPtr = glm::value_ptr(Light1ModelMatrix);
auto Light1NormalMatrixPtr = glm::value_ptr(Light1NormalMatrix);
auto Light1DiffusePtr = glm::value_ptr(Light1Diffuse);
auto Light1SpecularPtr = glm::value_ptr(Light1Specular);
auto Light1ViewMatrixPtr = glm::value_ptr(Light1ViewMatrix);
auto Light1ShadowMatrixPtr = glm::value_ptr(Light1ShadowMatrix);
auto Light2PosPtr = glm::value_ptr(Light2Pos);
auto Light2ModelMatrixPtr = glm::value_ptr(Light2ModelMatrix);
auto Light2NormalMatrixPtr = glm::value_ptr(Light2NormalMatrix);
auto Light2DiffusePtr = glm::value_ptr(Light2Diffuse);
auto Light2SpecularPtr = glm::value_ptr(Light2Specular);
auto Light2RangePtr = glm::value_ptr(Light2Range);
auto Light3PosPtr = glm::value_ptr(Light3Pos);
auto Light3ModelMatrixPtr = glm::value_ptr(Light3ModelMatrix);
auto Light3NormalMatrixPtr = glm::value_ptr(Light3NormalMatrix);
auto Light3DiffusePtr = glm::value_ptr(Light3Diffuse);
auto Light3SpecularPtr = glm::value_ptr(Light3Specular);
auto Light3RangePtr = glm::value_ptr(Light3Range);
auto Square1ModelMatrixPtr = glm::value_ptr(Square1ModelMatrix);
auto Square1NormalMatrixPtr = glm::value_ptr(Square1NormalMatrix);
auto Square1DiffusePtr = glm::value_ptr(Square1Diffuse);
auto Square1SpecularPtr = glm::value_ptr(Square1Specular);
auto Square2ModelMatrixPtr = glm::value_ptr(Square2ModelMatrix);
auto Square2NormalMatrixPtr = glm::value_ptr(Square2NormalMatrix);
auto Square2DiffusePtr = glm::value_ptr(Square2Diffuse);
auto Square2SpecularPtr = glm::value_ptr(Square2Specular);
auto Square3ModelMatrixPtr = glm::value_ptr(Square3ModelMatrix);
auto Square3NormalMatrixPtr = glm::value_ptr(Square3NormalMatrix);
auto Square3DiffusePtr = glm::value_ptr(Square3Diffuse);
auto Square3SpecularPtr = glm::value_ptr(Square3Specular);
auto Square4ModelMatrixPtr = glm::value_ptr(Square4ModelMatrix);
auto Square4NormalMatrixPtr = glm::value_ptr(Square4NormalMatrix);
auto Square4DiffusePtr = glm::value_ptr(Square4Diffuse);
auto Square4SpecularPtr = glm::value_ptr(Square4Specular);
auto Square5ModelMatrixPtr = glm::value_ptr(Square5ModelMatrix);
auto Square5NormalMatrixPtr = glm::value_ptr(Square5NormalMatrix);
auto Square5DiffusePtr = glm::value_ptr(Square5Diffuse);
auto Square5SpecularPtr = glm::value_ptr(Square5Specular);
auto Square6ModelMatrixPtr = glm::value_ptr(Square6ModelMatrix);
auto Square6NormalMatrixPtr = glm::value_ptr(Square6NormalMatrix);
auto Square6DiffusePtr = glm::value_ptr(Square6Diffuse);
auto Square6SpecularPtr = glm::value_ptr(Square6Specular);
// --------------------------------------------------------


int main(int argc, char * argv[]) {

	char path[256];
	engine = new Engine(argc, argv);

	ShaderProgram* defergbufferShader = new ShaderProgram();
	FBO g_buffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 4);
	FBO shadow_buffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_WIDTH), 1);

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
    ambientShader->SetAttribTexture("texture_coordinate");

	ShaderProgram* shadowMapShader = new ShaderProgram();
	GET_SHADER_PATH(path, 256, "shadow.vert");
	if (!shadowMapShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_PATH(path, 256, "shadow.frag");
	if (!shadowMapShader->AddFragmentShaderPath(path)) return 0;
	if (!shadowMapShader->Link()) return 0;
	shadowMapShader->SetAttribVertex("vertex");

	ShaderProgram* shadowRenderShader = new ShaderProgram();
	GET_SHADER_PATH(path, 256, "shadowRender.vert");
	if (!shadowRenderShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_PATH(path, 256, "shadowRender.frag");
	if (!shadowRenderShader->AddFragmentShaderPath(path)) return 0;
	if (!shadowRenderShader->Link()) return 0;
	shadowRenderShader->SetAttribVertex("vertex");
	shadowRenderShader->SetAttribTexture("texture_coordinate");
    
    ShaderProgram* deferredBRDFShader = new ShaderProgram();
    GET_SHADER_PATH(path, 256, "deferredBRDF.vert");
    if (!deferredBRDFShader->AddVertexShaderPath(path)) return 0;
    GET_SHADER_PATH(path, 256, "deferredBRDF.frag");
    if (!deferredBRDFShader->AddFragmentShaderPath(path)) return 0;
    if (!deferredBRDFShader->Link()) return 0;
    deferredBRDFShader->SetAttribVertex("vertex");
    deferredBRDFShader->SetAttribTexture("texture_coordinate");

	// --------------SHADER LOADING--------------------------

	GET_MODEL_PATH(path, 256, "bunny_smooth.ply");
	Mesh bunny1, bunny2, bunny3;
	Mesh shadowBunny1, shadowBunny2, shadowBunny3;
    Mesh square1, square2, square3, square4, square5, square6;
    Mesh shadowSquare1, shadowSquare2, shadowSquare3, shadowSquare4, shadowSquare5, shadowSquare6;
	bunny1.Load(path);
	bunny2.Load(path);
	bunny3.Load(path);
	shadowBunny1.Load(path);
	shadowBunny2.Load(path);
	shadowBunny3.Load(path);
    
    
    square1.LoadSquare();
    square2.LoadSquare();
    square3.LoadSquare();
    square4.LoadSquare();
    square5.LoadSquare();
    square6.LoadSquare();
    shadowSquare1.LoadSquare();
    shadowSquare2.LoadSquare();
    shadowSquare3.LoadSquare();
    shadowSquare4.LoadSquare();
    shadowSquare5.LoadSquare();
    shadowSquare6.LoadSquare();

	GET_MODEL_PATH(path, 256, "sphere.ply");
	Mesh Light1, Light2, Light3;
	Light1.Load(path);
    Light2.Load(path);
    Light3.Load(path);

	Mesh AmbientFSQ;
	AmbientFSQ.LoadSquare();
    
    Mesh ShadowRenderFSQ;
    ShadowRenderFSQ.LoadSquare();
    
    Mesh DeferredBRDFFSQ;
    DeferredBRDFFSQ.LoadSquare();

	// ---------------MODEL LOADING--------------------------

	Scene bunnyScene;
	bunnyScene.addObject(&bunny1);
	bunnyScene.addObject(&bunny2);
	bunnyScene.addObject(&bunny3);
	bunnyScene.addObject(&Light1);
    bunnyScene.addObject(&Light2);
    bunnyScene.addObject(&Light3);
    bunnyScene.addObject(&square1);
    bunnyScene.addObject(&square2);
    bunnyScene.addObject(&square3);
    bunnyScene.addObject(&square4);
    bunnyScene.addObject(&square5);
    bunnyScene.addObject(&square6);


    Scene ambientScene;
	ambientScene.addObject(&AmbientFSQ);

	Scene shadowMapScene;
	shadowMapScene.addObject(&shadowBunny1);
	shadowMapScene.addObject(&shadowBunny2);
	shadowMapScene.addObject(&shadowBunny3);
    shadowMapScene.addObject(&shadowSquare1);
    shadowMapScene.addObject(&shadowSquare2);
    shadowMapScene.addObject(&shadowSquare3);
    shadowMapScene.addObject(&shadowSquare4);
    shadowMapScene.addObject(&shadowSquare5);
    shadowMapScene.addObject(&shadowSquare6);

    Scene shadowRenderScene;
    shadowRenderScene.addObject(&ShadowRenderFSQ);
    
    Scene deferredBRDFScene;
    deferredBRDFScene.addObject(&DeferredBRDFFSQ);

	// --------------SCENE LOADING --------------------------

	Pass gbufferPass(defergbufferShader, &bunnyScene);
	Pass ambientPass(ambientShader, &ambientScene);
	Pass shadowPass(shadowMapShader, &shadowMapScene);
	Pass shadowRenderPass(shadowRenderShader, &shadowRenderScene);
    Pass deferredBRDFPass1(deferredBRDFShader, &deferredBRDFScene);
    Pass deferredBRDFPass2(deferredBRDFShader, &deferredBRDFScene);

	gbufferPass.BindAttribNormal();
	gbufferPass.BindAttribVertex();
	ambientPass.BindAttribVertex();
    ambientPass.BindAttribTexture();
	shadowPass.BindAttribVertex();
	shadowRenderPass.BindAttribVertex();
	shadowRenderPass.BindAttribTexture();
    deferredBRDFPass1.BindAttribVertex();
    deferredBRDFPass1.BindAttribTexture();

	// --------------- BIND ATTRIBUTES ---------------------

	gbufferPass.BindUniformMatrix4("ViewMatrix", &ViewMatrixPtr);
	gbufferPass.BindUniformMatrix4("ProjectionMatrix", &ProjectionMatrixPtr);
	ambientPass.BindUniformVec3("ambientColor", &AmbientLightPtr);
	shadowPass.BindUniformMatrix4("ViewMatrix", &Light1ViewMatrixPtr);
	shadowPass.BindUniformMatrix4("ProjectionMatrix", &ProjectionMatrixPtr);
	shadowRenderPass.BindUniformMatrix4("shadowMatrix", &Light1ShadowMatrixPtr);
	shadowRenderPass.BindUniformVec3("lightPos", &Light1PosPtr);
	shadowRenderPass.BindUniformVec3("eyePos", &EyePosPtr);
	shadowRenderPass.BindUniformVec3("lightValue", &Light1DiffusePtr);
    deferredBRDFPass1.BindUniformVec3("lightPos", &Light2PosPtr);
    deferredBRDFPass1.BindUniformVec3("eyePos", &EyePosPtr);
    deferredBRDFPass1.BindUniformVec3("lightValue", &Light2DiffusePtr);
    deferredBRDFPass1.BindUniformVec3("range", &Light2RangePtr);
    deferredBRDFPass2.BindUniformVec3("lightPos", &Light3PosPtr);
    deferredBRDFPass2.BindUniformVec3("lightValue", &Light3DiffusePtr);
    deferredBRDFPass2.BindUniformVec3("range", &Light3RangePtr);

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
    gbufferPass.MeshBindUniformMatrix4(&Light2, "ModelMatrix", &Light2ModelMatrixPtr);
    gbufferPass.MeshBindUniformMatrix4(&Light2, "NormalMatrix", &Light2NormalMatrixPtr);
    gbufferPass.MeshBindUniformVec3(&Light2, "diffuse", &Light2DiffusePtr);
    gbufferPass.MeshBindUniformVec3(&Light2, "specular", &Light2SpecularPtr);
    gbufferPass.MeshBindUniformMatrix4(&Light3, "ModelMatrix", &Light3ModelMatrixPtr);
    gbufferPass.MeshBindUniformMatrix4(&Light3, "NormalMatrix", &Light3NormalMatrixPtr);
    gbufferPass.MeshBindUniformVec3(&Light3, "diffuse", &Light3DiffusePtr);
    gbufferPass.MeshBindUniformVec3(&Light3, "specular", &Light3SpecularPtr);
    gbufferPass.MeshBindUniformMatrix4(&square1, "ModelMatrix", &Square1ModelMatrixPtr);
    gbufferPass.MeshBindUniformMatrix4(&square1, "NormalMatrix", &Square1NormalMatrixPtr);
    gbufferPass.MeshBindUniformVec3(&square1, "diffuse", &Square1DiffusePtr);
    gbufferPass.MeshBindUniformVec3(&square1, "specular", &Square1SpecularPtr);
    gbufferPass.MeshBindUniformMatrix4(&square2, "ModelMatrix", &Square2ModelMatrixPtr);
    gbufferPass.MeshBindUniformMatrix4(&square2, "NormalMatrix", &Square2NormalMatrixPtr);
    gbufferPass.MeshBindUniformVec3(&square2, "diffuse", &Square2DiffusePtr);
    gbufferPass.MeshBindUniformVec3(&square2, "specular", &Square2SpecularPtr);
    gbufferPass.MeshBindUniformMatrix4(&square3, "ModelMatrix", &Square3ModelMatrixPtr);
    gbufferPass.MeshBindUniformMatrix4(&square3, "NormalMatrix", &Square3NormalMatrixPtr);
    gbufferPass.MeshBindUniformVec3(&square3, "diffuse", &Square3DiffusePtr);
    gbufferPass.MeshBindUniformVec3(&square3, "specular", &Square3SpecularPtr);
    gbufferPass.MeshBindUniformMatrix4(&square4, "ModelMatrix", &Square4ModelMatrixPtr);
    gbufferPass.MeshBindUniformMatrix4(&square4, "NormalMatrix", &Square4NormalMatrixPtr);
    gbufferPass.MeshBindUniformVec3(&square4, "diffuse", &Square4DiffusePtr);
    gbufferPass.MeshBindUniformVec3(&square4, "specular", &Square4SpecularPtr);
    gbufferPass.MeshBindUniformMatrix4(&square5, "ModelMatrix", &Square5ModelMatrixPtr);
    gbufferPass.MeshBindUniformMatrix4(&square5, "NormalMatrix", &Square5NormalMatrixPtr);
    gbufferPass.MeshBindUniformVec3(&square5, "diffuse", &Square5DiffusePtr);
    gbufferPass.MeshBindUniformVec3(&square5, "specular", &Square5SpecularPtr);
    gbufferPass.MeshBindUniformMatrix4(&square6, "ModelMatrix", &Square6ModelMatrixPtr);
    gbufferPass.MeshBindUniformMatrix4(&square6, "NormalMatrix", &Square6NormalMatrixPtr);
    gbufferPass.MeshBindUniformVec3(&square6, "diffuse", &Square6DiffusePtr);
    gbufferPass.MeshBindUniformVec3(&square6, "specular", &Square6SpecularPtr);

	shadowPass.MeshBindUniformMatrix4(&shadowBunny1, "ModelMatrix", &Bunny1ModelMatrixPtr);
	shadowPass.MeshBindUniformMatrix4(&shadowBunny2, "ModelMatrix", &Bunny2ModelMatrixPtr);
	shadowPass.MeshBindUniformMatrix4(&shadowBunny3, "ModelMatrix", &Bunny3ModelMatrixPtr);
    shadowPass.MeshBindUniformMatrix4(&shadowSquare1, "ModelMatrix", &Square1ModelMatrixPtr);
    shadowPass.MeshBindUniformMatrix4(&shadowSquare2, "ModelMatrix", &Square2ModelMatrixPtr);
    shadowPass.MeshBindUniformMatrix4(&shadowSquare3, "ModelMatrix", &Square3ModelMatrixPtr);
    shadowPass.MeshBindUniformMatrix4(&shadowSquare4, "ModelMatrix", &Square4ModelMatrixPtr);
    shadowPass.MeshBindUniformMatrix4(&shadowSquare5, "ModelMatrix", &Square5ModelMatrixPtr);
    shadowPass.MeshBindUniformMatrix4(&shadowSquare6, "ModelMatrix", &Square6ModelMatrixPtr);


	// ------------BIND MESH-WISE UNIFORMS----------------

	gbufferPass.SetTarget(&g_buffer);
	shadowPass.SetTarget(&shadow_buffer);

	Texture* positionTex = g_buffer.GetTexture(0);
	Texture* normalTex = g_buffer.GetTexture(1);
	Texture* diffuseTex = g_buffer.GetTexture(2);
	Texture* specularTex = g_buffer.GetTexture(3);
	Texture* shadowTex = shadow_buffer.GetTexture(0);

    ambientPass.BindTexture("diffuseTexture", diffuseTex);
	shadowRenderPass.BindTexture("shadowTexture", shadowTex);
	shadowRenderPass.BindTexture("positionTexture", positionTex);
	shadowRenderPass.BindTexture("normalTexture", normalTex);
	shadowRenderPass.BindTexture("diffuseTexture", diffuseTex);
	shadowRenderPass.BindTexture("specularTexture", specularTex);
    deferredBRDFPass1.BindTexture("positionTexture", positionTex);
    deferredBRDFPass1.BindTexture("normalTexture", normalTex);
    deferredBRDFPass1.BindTexture("diffuseTexture", diffuseTex);
    deferredBRDFPass1.BindTexture("specularTexture", specularTex);
    deferredBRDFPass2.BindTexture("positionTexture", positionTex);
    deferredBRDFPass2.BindTexture("normalTexture", normalTex);
    deferredBRDFPass2.BindTexture("diffuseTexture", diffuseTex);
    deferredBRDFPass2.BindTexture("specularTexture", specularTex);

	gbufferPass.SetBlend(false);
	gbufferPass.SetDepthTest(true);
    gbufferPass.SetClear(true);
	ambientPass.SetBlend(false);
	ambientPass.SetDepthTest(false);
    ambientPass.SetClear(true);
	shadowPass.SetBlend(false);
	shadowPass.SetDepthTest(true);
    shadowPass.SetClear(true);
	shadowRenderPass.SetBlend(true);
	shadowRenderPass.SetDepthTest(false);
    shadowRenderPass.SetClear(false);
    deferredBRDFPass1.SetBlend(true);
    deferredBRDFPass1.SetDepthTest(false);
    deferredBRDFPass1.SetClear(false);
    deferredBRDFPass2.SetBlend(true);
    deferredBRDFPass2.SetDepthTest(false);
    deferredBRDFPass2.SetClear(false);

	// ---------------PASS CONFIG --------------------------
	engine->addPass(&gbufferPass);
	engine->addPass(&ambientPass);
	engine->addPass(&shadowPass);
	engine->addPass(&shadowRenderPass);
    engine->addPass(&deferredBRDFPass1);
    engine->addPass(&deferredBRDFPass2);

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