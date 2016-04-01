//
//  Pass.cpp
//  gltest
//
//  Created by Chenbo Li on 3/19/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "Pass.hpp"
#include "Scene.hpp"
#include "ShaderProgram.hpp"
#include "FBO.hpp"
#include "Texture.hpp"
#include <iostream>

int Pass::uniform_binding_point = 0;

Pass::Pass(ShaderProgram* shader, Scene* scene) : shader(shader), scene(scene), targetFBO(NULL), isBlend(false), isCullfaceBack(false), isCullfaceFront(false), isDepthTest(false), isClear(true), numOfTexture(0), numOfImage(0)
{
    
}

void Pass::GlobalBindUniformBlock(const char* block_name, char* buf, int sizeInBytes)
{
	GLuint blockID;
	glGenBuffers(1, &blockID);
	shader->BindUniformBlockToPoint(block_name, uniform_binding_point);
	glBindBufferBase(GL_UNIFORM_BUFFER, uniform_binding_point, blockID);
	glBufferData(GL_UNIFORM_BUFFER, sizeInBytes, buf, GL_STATIC_DRAW);
}

// Refresh Pass-Scope Uniforms on Every Pass Draw
void Pass::RebindUniforms()
{
    for (auto item : UniformMatrix4Mapper)
    {
        glUniformMatrix4fv(item.first, 1, GL_FALSE, *(item.second));
    }
    for (auto item : UniformVec3Mapper)
    {
        glUniform3fv(item.first, 1, *(item.second));
    }
    for (auto item : UniformInt1Mapper)
    {
        glUniform1i(item.first, item.second);
    }
    for (auto item : TextureUnitMapper)
    {
        item.first->BindToUnit(item.second);
    }
}

void Pass::BindTexture(const char* uniform_texture_name,Texture* texture)
{
	numOfTexture++;
	if (numOfTexture > GL_MAX_TEXTURE_UNITS)
	{
		std::cout << "Max texture units reached" << std::endl;
		return;
	}
	texture->BindToUnit(numOfTexture);
	BindUniformInt1(uniform_texture_name, numOfTexture);
	TextureUnitMapper[texture] = numOfTexture;
}

void Pass::BindImage(const char* uniform_image_name, Texture* texture)
{
#ifdef _WIN32
	numOfImage++;
	if (numOfImage > GL_MAX_IMAGE_UNITS)
	{
		std::cout << "Max image units reached" << std::endl;
		return;
	}
	texture->BindToImageUnit(numOfImage);
	BindUniformInt1(uniform_image_name, numOfImage);
	ImageUnitMapper[texture] = numOfImage;
#endif
}

void Pass::Draw()
{
	glViewport(0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH));
    shader->Use();
    
    if (targetFBO)
        targetFBO->Bind();
    
	if (isBlend)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
	if (isDepthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	if (!isCullfaceFront && !isCullfaceBack)
		glDisable(GL_CULL_FACE);
	if (isCullfaceFront)
	{
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
	}
	if (isCullfaceBack)
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
    if (isClear)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    RebindUniforms();

	for (auto item: TextureUnitMapper)
		item.first->BindToUnit(item.second);
        
	if (scene)
		scene->Draw();
	else
		shader->Compute(); // Compute shader
    
	for (auto item: TextureUnitMapper)
		item.first->Unbind();

    if (targetFBO)
        targetFBO->Unbind();
	
    shader->Unuse();
}

void Pass::BindAttribVertex()
{
    GLint loc = shader->GetAttribVertex();
    scene->BindVertex(loc);
}
void Pass::BindAttribNormal()
{
    GLint loc = shader->GetAttribNormal();
    scene->BindNormal(loc);
}
void Pass::BindAttribTangent()
{
    GLint loc = shader->GetAttribTangent();
    scene->BindTangent(loc);
}
void Pass::BindAttribTexture()
{
    GLint loc = shader->GetAttribTexture();
    scene->BindTexture(loc);
}


void Pass::SetTarget(FBO *fbo)
{
    this->targetFBO = fbo;
}

void Pass::SetBlend(bool status)
{
	this->isBlend = status;
}

void Pass::SetDepthTest(bool status)
{
	this->isDepthTest = status;
}

void Pass::SetCullfaceFront(bool status)
{
	this->isCullfaceFront = status;
}

void Pass::SetCullfaceBack(bool status)
{
	this->isCullfaceBack = status;
}

void Pass::SetClear(bool status)
{
    this->isClear = status;
}

void Pass::SetBlur(bool status)
{
	this->isBlur = status;
}
