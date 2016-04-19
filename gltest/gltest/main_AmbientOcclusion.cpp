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
#include "FBO.hpp"
#include "Texture.hpp"
#include <iostream>
#include "rgbe.h"


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
void readHDR(const char* path, float* data, int& width, int& height);
glm::vec3 RGB2Linear(glm::vec3 rgb);
glm::vec3 Linear2RGB(glm::vec3 linear);


// ----------------- VARIABLE ZONE --------------------------
auto EyePos = glm::vec3(0.0f, 0.0f, 3.0f);
auto UpPos = glm::vec3(0.0f, 1.0f, 0.0f);
auto WatchPos = glm::vec3(0.0f, 0.0f, 0.0f);
auto ProjectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 20.0f);
auto ViewMatrix = glm::lookAt(EyePos, WatchPos, UpPos);
auto ViewInverseMatrix = glm::inverse(ViewMatrix);

// Sphere1
auto Sphere1ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Sphere1NormalMatrix = glm::transpose(glm::inverse(Sphere1ModelMatrix));
auto Sphere1Diffuse = glm::vec3(1.0);
auto Sphere1Specular = glm::vec3(1.0);
auto Sphere1Gloss = glm::vec3(0.1);
// Sphere2
auto Sphere2ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Sphere2NormalMatrix = glm::transpose(glm::inverse(Sphere1ModelMatrix));
auto Sphere2Diffuse = glm::vec3(1.0);
auto Sphere2Specular = glm::vec3(1.0);
auto Sphere2Gloss = glm::vec3(0.5);

// Sphere3
auto Sphere3ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, .25f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Sphere3NormalMatrix = glm::transpose(glm::inverse(Sphere1ModelMatrix));
auto Sphere3Diffuse = glm::vec3(1.0);
auto Sphere3Specular = glm::vec3(1.0);
auto Sphere3Gloss = glm::vec3(1.0);

// Dome
auto DomeModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f));
auto DomeNormalMatrix = glm::transpose(glm::inverse(DomeModelMatrix));

// Ground
auto GroundModelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
auto GroundNormalMatrix = glm::transpose(glm::inverse(GroundModelMatrix));
auto GroundDiffuse = glm::vec3(1.0, 1.0, 1.0);
auto GroundSpecular = glm::vec3(0.0);
auto GroundGloss = glm::vec3(1.0);

// -------------------- POINTERS ZONE ------------------------
auto EyePosPtr = glm::value_ptr(EyePos);
auto UpPosPtr = glm::value_ptr(UpPos);
auto WatchPosPtr = glm::value_ptr(WatchPos);
auto ProjectionMatrixPtr = glm::value_ptr(ProjectionMatrix);
auto ViewMatrixPtr = glm::value_ptr(ViewMatrix);
auto ViewInverseMatrixPtr = glm::value_ptr(ViewInverseMatrix);
auto Sphere1ModelMatrixPtr = glm::value_ptr(Sphere1ModelMatrix);
auto Sphere1NormalMatrixPtr = glm::value_ptr(Sphere1NormalMatrix);
auto Sphere1DiffusePtr = glm::value_ptr(Sphere1Diffuse);
auto Sphere1SpecularPtr = glm::value_ptr(Sphere1Specular);
auto Sphere1GlossPtr = glm::value_ptr(Sphere1Gloss);
auto Sphere2ModelMatrixPtr = glm::value_ptr(Sphere2ModelMatrix);
auto Sphere2NormalMatrixPtr = glm::value_ptr(Sphere2NormalMatrix);
auto Sphere2DiffusePtr = glm::value_ptr(Sphere2Diffuse);
auto Sphere2SpecularPtr = glm::value_ptr(Sphere2Specular);
auto Sphere2GlossPtr = glm::value_ptr(Sphere2Gloss);
auto Sphere3ModelMatrixPtr = glm::value_ptr(Sphere3ModelMatrix);
auto Sphere3NormalMatrixPtr = glm::value_ptr(Sphere3NormalMatrix);
auto Sphere3DiffusePtr = glm::value_ptr(Sphere3Diffuse);
auto Sphere3SpecularPtr = glm::value_ptr(Sphere3Specular);
auto Sphere3GlossPtr = glm::value_ptr(Sphere3Gloss);
auto DomeModelMatrixPtr = glm::value_ptr(DomeModelMatrix);
auto DomeNormalMatrixPtr = glm::value_ptr(DomeNormalMatrix);
auto GroundModelMatrixPtr = glm::value_ptr(GroundModelMatrix);
auto GroundNormalMatrixPtr = glm::value_ptr(GroundNormalMatrix);
auto GroundDiffusePtr = glm::value_ptr(GroundDiffuse);
auto GroundSpecularPtr = glm::value_ptr(GroundSpecular);
auto GroundGlossPtr = glm::value_ptr(GroundGloss);

// --------------------------------------------------------

// readHDR as RGBA format 
void readHDR(const char* path, std::vector<float>& data, int& width, int& height)
{
    rgbe_header_info info;
    char errbuff[100] = {0};
    
    FILE* fp = fopen(path, "rb");
    if (!fp)
    {
        std::cout << "Can't open hdr file " << path << std::endl;
        exit(-1);
    }
    int rc = RGBE_ReadHeader(fp, &width, &height, &info, errbuff);
    if (rc!= RGBE_RETURN_SUCCESS)
    {
        std::cout << "RGBE Read error " << errbuff << std::endl;
    }
    float* rgb_data = new float[3*width*height];
    
    rc = RGBE_ReadPixels_RLE(fp, rgb_data, width, height);
    if (rc != RGBE_RETURN_SUCCESS)
    {
        std::cout << "RGBE read error " << errbuff << std::endl;
    }
    fclose(fp);
    
    data.resize(4*width*height);
    for (int i = 0; i < width*height; ++i)
    {
        data[4*i] = rgb_data[3*i];
        data[4*i+1] = rgb_data[3*i+1];
        data[4*i+2] = rgb_data[3*i+2];
        data[4*i+3] = info.exposure;
    }
    return;
}

typedef struct Hammersley_block
{
	float N;
	float hammersley[100*2];
} Hammersley_block;

char* buildHammersleyRandom(float N)
{
	struct Hammersley_block* block = (struct Hammersley_block*)malloc(sizeof(Hammersley_block));
	block->N = N;
    int kk;
    float p, u;
	int pos = 0;

	for (int k = 0; k < N; ++k)
	{
		for (p = 0.5f, kk = k, u = 0.0f; kk; p *= 0.5f, kk >>= 1)
			if (kk & 1)
				u += p;
		float v = (k + 0.5) / N;
		block->hammersley[pos++] = u;
		block->hammersley[pos++] = v;
	}
	return (char*)block;
}

int main(int argc, char * argv[]) {

	char path[256];
	engine = new Engine(argc, argv);

	ShaderProgram* defergbufferShader = new ShaderProgram();
	FBO g_buffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 6);

	GET_SHADER_AO_PATH(path, 256, "defergbufferDome.vert");
	if (!defergbufferShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_AO_PATH(path, 256, "defergbufferDome.frag");
	if (!defergbufferShader->AddFragmentShaderPath(path)) return 0;
	if (!defergbufferShader->Link()) return 0;

	defergbufferShader->SetAttribVertex("vertex_coord");
	defergbufferShader->SetAttribNormal("normal_coord");

	ShaderProgram* ambientShader = new ShaderProgram();
	GET_SHADER_AO_PATH(path, 256, "deferAmbientLight.vert");
	if (!ambientShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_AO_PATH(path, 256, "deferAmbientLight.frag");
	if (!ambientShader->AddFragmentShaderPath(path)) return 0;
	if (!ambientShader->Link()) return 0;
	ambientShader->SetAttribVertex("vertex_coord");
	ambientShader->SetAttribTexture("texture_coordinate");

	ShaderProgram* iblSpecularShader = new ShaderProgram();
	GET_SHADER_AO_PATH(path, 256, "IBLSpecular.vert");
	if (!iblSpecularShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_AO_PATH(path, 256, "IBLSpecular.frag");
	if (!iblSpecularShader->AddFragmentShaderPath(path)) return 0;
	if (!iblSpecularShader->Link()) return 0;
	iblSpecularShader->SetAttribVertex("vertex");
	iblSpecularShader->SetAttribTexture("texture_coordinate");
    
	// --------------SHADER LOADING--------------------------

	GET_MODEL_PATH(path, 256, "bunny_smooth.ply");
	Mesh sphere1, sphere2, sphere3;
    sphere1.Load(path);
    sphere2.Load(path);
    sphere3.Load(path);
	GET_MODEL_PATH(path, 256, "sphere.ply");
	Mesh dome;
    dome.Load(path);
	
	Mesh Ground;
	Ground.LoadSquare();

	Mesh AmbientFSQ;
	AmbientFSQ.LoadSquare();

	Mesh SpecularFSQ;
	SpecularFSQ.LoadSquare();

	// ---------------MODEL LOADING--------------------------

	Scene SphereScene;
	SphereScene.addObject(&sphere1);
	SphereScene.addObject(&sphere2);
	SphereScene.addObject(&sphere3);
    SphereScene.addObject(&dome);
	SphereScene.addObject(&Ground);

	Scene ambientScene;
	ambientScene.addObject(&AmbientFSQ);

	Scene iblSpecularScene;
	iblSpecularScene.addObject(&SpecularFSQ);

	// --------------SCENE LOADING --------------------------

	Pass gbufferPass(defergbufferShader, &SphereScene);
	Pass ambientPass(ambientShader, &ambientScene);
	Pass iblSpecularPass(iblSpecularShader, &iblSpecularScene);
	gbufferPass.SetTarget(&g_buffer);

	gbufferPass.BindAttribNormal();
	gbufferPass.BindAttribVertex();
    gbufferPass.BindAttribTexture();
	ambientPass.BindAttribVertex();
	ambientPass.BindAttribTexture();
	iblSpecularPass.BindAttribVertex();
	iblSpecularPass.BindAttribTexture();

	// --------------- BIND ATTRIBUTES ---------------------

	gbufferPass.BindUniformMatrix4("ViewMatrix", &ViewMatrixPtr);
	gbufferPass.BindUniformMatrix4("ProjectionMatrix", &ProjectionMatrixPtr);
    gbufferPass.BindUniformVec3("eyePos", &EyePosPtr);

	ambientPass.BindUniformInt1("windowHeight", glutGet(GLUT_WINDOW_HEIGHT));
	ambientPass.BindUniformInt1("windowWidth", glutGet(GLUT_WINDOW_WIDTH));

	iblSpecularPass.BindUniformVec3("eyePos", &EyePosPtr);


	// ------------- BIND PASS-WISE UNIFORMS---------------

	gbufferPass.MeshBindUniformMatrix4(&sphere1, "ModelMatrix", &Sphere1ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&sphere1, "NormalMatrix", &Sphere1NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&sphere1, "diffuse", &Sphere1DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&sphere1, "specular", &Sphere1SpecularPtr);
    gbufferPass.MeshBindUniformInt1(&sphere1, "isDome", 0);
    gbufferPass.MeshBindUniformVec3(&sphere1, "gloss", &Sphere1GlossPtr);
    
	gbufferPass.MeshBindUniformMatrix4(&sphere2, "ModelMatrix", &Sphere2ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&sphere2, "NormalMatrix", &Sphere2NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&sphere2, "diffuse", &Sphere2DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&sphere2, "specular", &Sphere2SpecularPtr);
    gbufferPass.MeshBindUniformInt1(&sphere2, "isDome", 0);
	gbufferPass.MeshBindUniformVec3(&sphere2, "gloss", &Sphere2GlossPtr);


	gbufferPass.MeshBindUniformMatrix4(&sphere3, "ModelMatrix", &Sphere3ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&sphere3, "NormalMatrix", &Sphere3NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&sphere3, "diffuse", &Sphere3DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&sphere3, "specular", &Sphere3SpecularPtr);
    gbufferPass.MeshBindUniformInt1(&sphere3, "isDome", 0);
	gbufferPass.MeshBindUniformVec3(&sphere3, "gloss", &Sphere3GlossPtr);


	gbufferPass.MeshBindUniformMatrix4(&dome, "ModelMatrix", &DomeModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&dome, "NormalMatrix", &DomeNormalMatrixPtr);
    gbufferPass.MeshBindUniformInt1(&dome, "isDome", 1);
	
	gbufferPass.MeshBindUniformMatrix4(&Ground, "ModelMatrix", &GroundModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&Ground, "NormalMatrix", &GroundNormalMatrixPtr);
	gbufferPass.MeshBindUniformInt1(&Ground, "isDome", 0);
	gbufferPass.MeshBindUniformVec3(&Ground, "diffuse", &GroundDiffusePtr);
    
    // ------------ BIND MESH-WISE UNIFORMS ----------------
	char* block = buildHammersleyRandom(20);
	iblSpecularPass.GlobalBindUniformBlock("HammersleyBlock", block, sizeof(Hammersley_block));
    // ------------BIND GLOBAL UNIFROMS -------------------

    GET_HDR_PATH(path, 256, "Alexs_Apt_2k.hdr");
    std::vector<float> hdrImage;
    int width, height;
    readHDR(path, hdrImage, width, height);
    Texture* domeTex = new Texture(width,height);
    domeTex->LoadData(&hdrImage[0]);
    
    GET_HDR_PATH(path, 256, "Alexs_Apt_2k.irr.hdr");
    readHDR(path, hdrImage, width, height);
    Texture* domeIrrTex = new Texture(width,height);
    domeIrrTex->LoadData(&hdrImage[0]);
    
	Texture* positionTex = g_buffer.GetTexture(0);
	Texture* normalTex = g_buffer.GetTexture(1);
	Texture* diffuseTex = g_buffer.GetTexture(2);
	Texture* specularTex = g_buffer.GetTexture(3);
	Texture* glossTex = g_buffer.GetTexture(4);
	Texture* depthTex = g_buffer.GetTexture(5);

    gbufferPass.BindTexture("domeTexture", domeTex);

	ambientPass.BindTexture("diffuseTexture", diffuseTex);
    ambientPass.BindTexture("domeIrrTexture", domeIrrTex);
	ambientPass.BindTexture("normalTexture", normalTex);
	ambientPass.BindTexture("positionTexture", positionTex);
	ambientPass.BindTexture("depthTexture", depthTex);

	iblSpecularPass.BindTexture("positionTexture", positionTex);
	iblSpecularPass.BindTexture("normalTexture", normalTex);
	iblSpecularPass.BindTexture("specularTexture", specularTex);
    iblSpecularPass.BindTexture("domeTexture", domeTex);
	iblSpecularPass.BindTexture("glossTexture", glossTex);
	
	gbufferPass.SetBlend(false);
	gbufferPass.SetDepthTest(true);
	gbufferPass.SetClear(true);
	ambientPass.SetBlend(false);
	ambientPass.SetDepthTest(false);
	ambientPass.SetClear(true);
	iblSpecularPass.SetBlend(true);
	iblSpecularPass.SetDepthTest(false);
	iblSpecularPass.SetClear(false);

	// ---------------PASS CONFIG --------------------------
	engine->addPass(&gbufferPass);
	engine->addPass(&ambientPass);
	engine->addPass(&iblSpecularPass);

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