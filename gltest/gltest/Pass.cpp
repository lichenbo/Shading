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

Pass::Pass(ShaderProgram* shader, Scene* scene): shader(shader), scene(scene)
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
}

void Pass::Draw()
{
    shader->Use();
    
    if (targetFBO)
        targetFBO->Bind();
    
    RebindUniforms();
        
    scene->Draw(shader->GetUniformModel(), shader->GetUniformNormal());
    
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