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
	EyePos = glm::vec3(0.0f, 0.0f, 10.0f);
	UpPos = glm::vec3(0.0f, 1.0f, 0.0f);
	LightPos = glm::vec3(10.0f, 10.0f, 10.0f);
	WatchPos = glm::vec3(0.0f, 0.0f, 0.0f);
	ProjectionMatrix = glm::perspective(45.0f, 1.0f, 0.5f, 100.0f);
}

void Scene::addObject(Mesh* mesh)
{
    objects.push_back(mesh);
}

void Scene::Draw(GLint modelLoc, GLint normalLoc)
{
	ViewMatrix = glm::lookAt(EyePos, WatchPos, UpPos);

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto mesh : objects)
    {
        if (modelLoc != -1)
            mesh->BindModelUniform(modelLoc);
        if (normalLoc != -1)
            mesh->BindNormalUniform(normalLoc);
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

