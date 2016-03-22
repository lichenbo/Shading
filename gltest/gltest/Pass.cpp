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

void Pass::Draw()
{
    shader->Use();
    
    BindUniformMatrix4(shader->ViewMatrixLoc, scene->ViewMatrix);
    BindUniformMatrix4(shader->ViewInverseMatrixLoc, glm::inverse(scene->ViewMatrix));
    BindUniformMatrix4(shader->ProjectionMatrixLoc, scene->ProjectionMatrix);
    
    if (targetFBO)
        targetFBO->Bind();
        
    scene->Draw();
    
    if (targetFBO)
        targetFBO->Unbind();
    
    shader->Unuse();
}

void Pass::BindAttribVertex(const char* attr_name)
{
    GLint loc = shader->GetAttribute(attr_name);
    scene->BindVertex(loc);
}
void Pass::BindAttribNormal(const char* attr_name)
{
    GLint loc = shader->GetAttribute(attr_name);
    scene->BindNormal(loc);
}
void Pass::BindAttribTangent(const char* attr_name)
{
    GLint loc = shader->GetAttribute(attr_name);
    scene->BindTangent(loc);
}
void Pass::BindAttribTexture(const char* attr_name)
{
    GLint loc = shader->GetAttribute(attr_name);
    scene->BindTexture(loc);
}


void Pass::SetTarget(FBO *fbo)
{
    this->targetFBO = fbo;
}