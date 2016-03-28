//
//  Scene.cpp
//  gltest
//
//  Created by Chenbo Li on 3/6/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "Scene.hpp"
#include "Mesh.hpp"
#include "gl.h"

Scene::Scene()
{
}

void Scene::addObject(Mesh* mesh)
{
    objects.push_back(mesh);
}

void Scene::Draw()
{

    for (auto mesh : objects)
    {
        mesh->Draw();
    }
}

void Scene::BindVertex(GLint loc)
{
    for (Mesh* m : objects)
    {
        m->BindVertexAttribute(loc);
    }
}

void Scene::BindNormal(GLint loc)
{
    for (Mesh* m : objects)
    {
        m->BindNormalAttribute(loc);
    }
}

void Scene::BindTexture(GLint loc)
{
    for (Mesh* m : objects)
    {
        m->BindTextureAttribute(loc);
    }
}

void Scene::BindTangent(GLint loc)
{
    for (Mesh* m : objects)
    {
        m->BindTangentAttribute(loc);
    }
}

