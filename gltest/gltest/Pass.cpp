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
    shader->Bind();
    
    BindUniformMatrix4(shader->ViewMatrixLoc, scene->ViewMatrix);
    BindUniformMatrix4(shader->ViewInverseMatrixLoc, glm::inverse(scene->ViewMatrix));
    BindUniformMatrix4(shader->ProjectionMatrixLoc, scene->ProjectionMatrix);
    
    if (targetFBO)
        targetFBO->Bind();
        
    scene->Draw(shader);
    
    if (targetFBO)
        targetFBO->Unbind();
    
    shader->Unbind();
}


void Pass::addSpin(float deltaX)
{
    scene->addSpin(deltaX);
}

void Pass::addTilt(float deltaY)
{
    scene->addTilt(deltaY);
}

void Pass::addZoom(int dir)
{
    scene->addZoom(dir);
}

void Pass::addTrans(float delta_move)
{
    scene->addTrans(delta_move);
}

void Pass::SetTarget(FBO *fbo)
{
    this->targetFBO = fbo;
}