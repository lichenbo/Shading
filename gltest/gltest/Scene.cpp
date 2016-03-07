//
//  Scene.cpp
//  gltest
//
//  Created by Chenbo Li on 3/6/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "Scene.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"

void Scene::addObject(Mesh* mesh)
{
    objects.push_back(mesh);
}

void Scene::Draw()
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->Bind();
    for (auto mesh : objects)
    {
        mesh->Draw(shader);
    }
    shader->Unbind();
}

void Scene::setShader(ShaderProgram* shader)
{
    this->shader = shader;
}