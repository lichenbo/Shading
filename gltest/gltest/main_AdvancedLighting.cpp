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
auto AmbientLight = glm::vec3(0.5, 0.5, 0.5) * glm::float32(4.0);

// Bunny1
auto Bunny1ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Bunny1NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny1Diffuse = glm::vec3(1.0);
auto Bunny1Specular = glm::vec3(1.0);
// Bunny2
auto Bunny2ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Bunny2NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny2Diffuse = glm::vec3(1.0);
auto Bunny2Specular = glm::vec3(1.0);
// Bunny3
auto Bunny3ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
auto Bunny3NormalMatrix = glm::transpose(glm::inverse(Bunny1ModelMatrix));
auto Bunny3Diffuse = glm::vec3(1.0);
auto Bunny3Specular = glm::vec3(1.0);

// Dome
auto DomeModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f));
auto DomeNormalMatrix = glm::transpose(glm::inverse(DomeModelMatrix));

// Light1: Global light
auto Light1Pos = glm::vec3(2.0f);
auto Light1ModelMatrix = glm::translate(glm::mat4(1.0f), Light1Pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
auto Light1NormalMatrix = glm::transpose(glm::inverse(Light1ModelMatrix));
auto Light1Diffuse = glm::vec3(1.0, 1.0, 1.0);
auto Light1Specular = glm::vec3(1.0, 1.0, 1.0);

// For Shadow Pass
auto Light1ViewMatrix = glm::lookAt(Light1Pos, WatchPos, UpPos);
auto Light1ShadowMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)) * ProjectionMatrix * Light1ViewMatrix;
auto BlurFactor = glm::vec3(1.0f);

// Light2: Local light
auto Light2Pos = glm::vec3(-0.5f);
auto Light2ModelMatrix = glm::translate(glm::mat4(1.0f), Light2Pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
auto Light2NormalMatrix = glm::transpose(glm::inverse(Light2ModelMatrix));
auto Light2Diffuse = glm::vec3(1.0, 1.0, 1.0);
auto Light2Specular = glm::vec3(1.0, 1.0, 1.0);
auto Light2Range = glm::vec3(1.0);

// Light3: Local light
auto Light3Pos = glm::vec3(0.25f);
auto Light3ModelMatrix = glm::translate(glm::mat4(1.0f), Light3Pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
auto Light3NormalMatrix = glm::transpose(glm::inverse(Light3ModelMatrix));
auto Light3Diffuse = glm::vec3(1.0, 1.0, 1.0);
auto Light3Specular = glm::vec3(1.0, 1.0, 1.0);
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
auto DomeModelMatrixPtr = glm::value_ptr(DomeModelMatrix);
auto DomeNormalMatrixPtr = glm::value_ptr(DomeNormalMatrix);
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
auto BlurFactorPtr = glm::value_ptr(BlurFactor);
// --------------------------------------------------------

float* buildGaussianWeight(int w, float s)
{
	float* weights = new float[2 * w + 1];

	for (int i = 0; i < 2 * w + 1; ++i)
	{
		weights[i] = exp(-0.5*((w - i) / s)*((w - i) / s)) / (2.50662827463 * s);
	}
	float sum = 0.0f;
	for (int i = 0; i < w; ++i)
	{
		sum += weights[i];
	}
	weights[w] = 1.0 - 2 * sum;
	return weights;
}

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
	FBO g_buffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 4);
	FBO shadow_buffer(1024, 1024, 1);

	GET_SHADER_IMAGELIGHT_PATH(path, 256, "defergbufferDome.vert");
	if (!defergbufferShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "defergbufferDome.frag");
	if (!defergbufferShader->AddFragmentShaderPath(path)) return 0;
	if (!defergbufferShader->Link()) return 0;

	defergbufferShader->SetAttribVertex("vertex_coord");
	defergbufferShader->SetAttribNormal("normal_coord");

	ShaderProgram* ambientShader = new ShaderProgram();
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "deferAmbientLight.vert");
	if (!ambientShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "deferAmbientLight.frag");
	if (!ambientShader->AddFragmentShaderPath(path)) return 0;
	if (!ambientShader->Link()) return 0;
	ambientShader->SetAttribVertex("vertex_coord");
	ambientShader->SetAttribTexture("texture_coordinate");

	ShaderProgram* shadowMapShader = new ShaderProgram();
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "expShadow.vert");
	if (!shadowMapShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "expShadow.frag");
	if (!shadowMapShader->AddFragmentShaderPath(path)) return 0;
	if (!shadowMapShader->Link()) return 0;
	shadowMapShader->SetAttribVertex("vertex");

	ShaderProgram* shadowRenderShader = new ShaderProgram();
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "expShadowRender.vert");
	if (!shadowRenderShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "expShadowRender.frag");
	if (!shadowRenderShader->AddFragmentShaderPath(path)) return 0;
	if (!shadowRenderShader->Link()) return 0;
	shadowRenderShader->SetAttribVertex("vertex");
	shadowRenderShader->SetAttribTexture("texture_coordinate");
    
	ShaderProgram* deferredBRDFShader = new ShaderProgram();
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "deferIBL.vert");
	if (!deferredBRDFShader->AddVertexShaderPath(path)) return 0;
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "deferIBL.frag");
	if (!deferredBRDFShader->AddFragmentShaderPath(path)) return 0;
	if (!deferredBRDFShader->Link()) return 0;
	deferredBRDFShader->SetAttribVertex("vertex");
	deferredBRDFShader->SetAttribTexture("texture_coordinate");

	ShaderProgram* blurShaderHorizontal = new ShaderProgram();
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "gaussianBlurHorizontal.comp");
	blurShaderHorizontal->SetComputeShaderPath(path);

	ShaderProgram* blurShaderVertical = new ShaderProgram();
	GET_SHADER_IMAGELIGHT_PATH(path, 256, "gaussianBlurVertical.comp");
	blurShaderVertical->SetComputeShaderPath(path);


	// --------------SHADER LOADING--------------------------

	GET_MODEL_PATH(path, 256, "bunny_smooth.ply");
	Mesh bunny1, bunny2, bunny3;
	Mesh shadowBunny1, shadowBunny2, shadowBunny3;
	Mesh dome;
    Mesh shadowDome;
    
	bunny1.Load(path);
	bunny2.Load(path);
	bunny3.Load(path);
	shadowBunny1.Load(path);
	shadowBunny2.Load(path);
	shadowBunny3.Load(path);


	GET_MODEL_PATH(path, 256, "sphere.ply");
	Mesh Light1, Light2, Light3;
	Light1.Load(path);
	Light2.Load(path);
	Light3.Load(path);
    dome.Load(path);
    shadowDome.Load(path);

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
    bunnyScene.addObject(&dome);


	Scene ambientScene;
	ambientScene.addObject(&AmbientFSQ);

	Scene shadowMapScene;
	shadowMapScene.addObject(&shadowBunny1);
	shadowMapScene.addObject(&shadowBunny2);
	shadowMapScene.addObject(&shadowBunny3);
    shadowMapScene.addObject(&shadowDome);

	Scene shadowRenderScene;
	shadowRenderScene.addObject(&ShadowRenderFSQ);

	Scene deferredBRDFScene;
	deferredBRDFScene.addObject(&DeferredBRDFFSQ);

	// --------------SCENE LOADING --------------------------

	Pass gbufferPass(defergbufferShader, &bunnyScene);
	Pass ambientPass(ambientShader, &ambientScene);
	Pass shadowPass(shadowMapShader, &shadowMapScene);
	Pass blurHorizontalPass(blurShaderHorizontal, NULL);
	Pass blurVerticalPass(blurShaderVertical, NULL);
	Pass shadowRenderPass(shadowRenderShader, &shadowRenderScene);
	Pass deferredBRDFPass1(deferredBRDFShader, &deferredBRDFScene);
	Pass deferredBRDFPass2(deferredBRDFShader, &deferredBRDFScene);

	gbufferPass.BindAttribNormal();
	gbufferPass.BindAttribVertex();
    gbufferPass.BindAttribTexture();
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
    gbufferPass.BindUniformVec3("eyePos", &EyePosPtr);

	ambientPass.BindUniformVec3("ambientColor", &AmbientLightPtr);
	shadowPass.BindUniformMatrix4("ViewMatrix", &Light1ViewMatrixPtr);
	shadowPass.BindUniformMatrix4("ProjectionMatrix", &ProjectionMatrixPtr);
	shadowPass.BindUniformVec3("blurFactor", &BlurFactorPtr);
    shadowRenderPass.BindUniformMatrix4("shadowMatrix", &Light1ShadowMatrixPtr);

	shadowRenderPass.BindUniformVec3("eyePos", &EyePosPtr);
	shadowRenderPass.BindUniformVec3("lightValue", &Light1DiffusePtr);
	shadowRenderPass.BindUniformVec3("blurFactor", &BlurFactorPtr);

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
    gbufferPass.MeshBindUniformInt1(&bunny1, "isDome", 0);
	gbufferPass.MeshBindUniformMatrix4(&bunny2, "ModelMatrix", &Bunny2ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&bunny2, "NormalMatrix", &Bunny2NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&bunny2, "diffuse", &Bunny2DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&bunny2, "specular", &Bunny2SpecularPtr);
    gbufferPass.MeshBindUniformInt1(&bunny2, "isDome", 0);

	gbufferPass.MeshBindUniformMatrix4(&bunny3, "ModelMatrix", &Bunny3ModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&bunny3, "NormalMatrix", &Bunny3NormalMatrixPtr);
	gbufferPass.MeshBindUniformVec3(&bunny3, "diffuse", &Bunny3DiffusePtr);
	gbufferPass.MeshBindUniformVec3(&bunny3, "specular", &Bunny3SpecularPtr);
    gbufferPass.MeshBindUniformInt1(&bunny3, "isDome", 0);

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
	gbufferPass.MeshBindUniformMatrix4(&dome, "ModelMatrix", &DomeModelMatrixPtr);
	gbufferPass.MeshBindUniformMatrix4(&dome, "NormalMatrix", &DomeNormalMatrixPtr);
    gbufferPass.MeshBindUniformInt1(&dome, "isDome", 1);
	
	shadowPass.MeshBindUniformMatrix4(&shadowBunny1, "ModelMatrix", &Bunny1ModelMatrixPtr);
	shadowPass.MeshBindUniformMatrix4(&shadowBunny2, "ModelMatrix", &Bunny2ModelMatrixPtr);
	shadowPass.MeshBindUniformMatrix4(&shadowBunny3, "ModelMatrix", &Bunny3ModelMatrixPtr);
	shadowPass.MeshBindUniformMatrix4(&shadowDome, "ModelMatrix", &DomeModelMatrixPtr);

	// ------------BIND MESH-WISE UNIFORMS----------------
    int blurWidth = 10; // kenel half width
    float h = 2 * blurWidth + 1; // What's this?
    float* blurKernel = buildGaussianWeight(blurWidth, h / 2.0);
    blurHorizontalPass.GlobalBindUniformBlock("blurKernel", (char*)blurKernel, sizeof(float)*(2 * blurWidth + 1));
    blurVerticalPass.GlobalBindUniformBlock("blurKernel", (char*)blurKernel, sizeof(float)*(2 * blurWidth + 1));
	gbufferPass.SetTarget(&g_buffer);
	shadowPass.SetTarget(&shadow_buffer);

	char* block = buildHammersleyRandom(20);
	shadowRenderPass.GlobalBindUniformBlock("HammersleyBlock", block, sizeof(Hammersley_block));
	
    
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
	Texture* shadowTex = shadow_buffer.GetTexture(0);

	Texture* blurredShadowHorizontal = new Texture(shadowTex->Width(), shadowTex->Height());
	Texture* blurredShadowVertical = new Texture(shadowTex->Width(), shadowTex->Height());
	blurShaderHorizontal->SetupComputeShader(shadowTex->Width() / 128, shadowTex->Height(), 1);
	blurShaderVertical->SetupComputeShader(shadowTex->Width(), shadowTex->Height() / 128, 1);
	blurHorizontalPass.BindUniformInt1("kernelWidth", blurWidth);
	blurVerticalPass.BindUniformInt1("kernelWidth", blurWidth);

	blurHorizontalPass.BindImage("src", shadowTex);
	blurHorizontalPass.BindImage("dst", blurredShadowHorizontal);
	blurVerticalPass.BindImage("src", blurredShadowHorizontal);
	blurVerticalPass.BindImage("dst", blurredShadowVertical);

	ambientPass.BindTexture("diffuseTexture", diffuseTex);
    ambientPass.BindTexture("domeIrrTexture", domeIrrTex);
	ambientPass.BindTexture("normalTexture", normalTex);
    gbufferPass.BindTexture("domeTexture", domeTex);

#ifdef _WIN32
	shadowRenderPass.BindTexture("shadowTexture", blurredShadowVertical);
#elif defined __APPLE__
	shadowRenderPass.BindTexture("shadowTexture", shadowTex);
#endif

	shadowRenderPass.BindTexture("positionTexture", positionTex);
	shadowRenderPass.BindTexture("normalTexture", normalTex);
	shadowRenderPass.BindTexture("specularTexture", specularTex);
    shadowRenderPass.BindTexture("domeTexture", domeTex);
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
#ifdef __WIN32
	engine->addPass(&blurHorizontalPass); // Compute shader
	engine->addPass(&blurVerticalPass); // Compute shader
#endif
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