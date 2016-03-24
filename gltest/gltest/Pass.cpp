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

Pass::Pass(ShaderProgram* shader, Scene* scene): shader(shader), scene(scene), targetFBO(NULL), numOfTexture(0)
{
    
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
	texture->BindToUnit(numOfTexture);
	BindUniformInt1(uniform_texture_name, numOfTexture);
	TextureUnitMapper[texture] = numOfTexture;
}

void Pass::Draw()
{
    shader->Use();
    
    if (targetFBO)
        targetFBO->Bind();
    
    RebindUniforms();

	for (auto item: TextureUnitMapper)
		item.first->BindToUnit(item.second);
        
    scene->Draw();
    
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