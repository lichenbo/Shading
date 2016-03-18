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
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp";
#include "gtc/matrix_inverse.hpp"

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

void Scene::Draw()
{
	ViewMatrix = glm::lookAt(EyePos, WatchPos, UpPos);

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Bind();
	glUniformMatrix4fv(shader->ViewMatrixLoc, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(shader->ViewInverseMatrixLoc, 1, GL_FALSE, glm::value_ptr(glm::inverse(ViewMatrix)));
	glUniformMatrix4fv(shader->ProjectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

    for (auto mesh : objects)
    {
        mesh->Draw(shader);
    }
    shader->Unbind();
}

void Scene::addSpin(float delta_x)
{
	delta_x *= 0.01;
	EyePos = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)delta_x, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(EyePos,1.0f));
	//UpPos = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)delta_x, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(UpPos,1.0f));
}

void Scene::addTilt(float delta_y)
{
	delta_y *= 0.01;
	EyePos = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)delta_y, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(EyePos,1.0f));
	//UpPos = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)delta_y, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(UpPos,1.0f));
}

void Scene::addTrans(float delta_move)
{
	EyePos += glm::vec3(delta_move, 0.0f, 0.0f);
	WatchPos += glm::vec3(delta_move, 0.0f, 0.0f);
}

void Scene::addZoom(float dir)
{
	EyePos = glm::vec3(glm::translate(glm::mat4(1.0f), glm::vec3(dir, dir, dir)) * glm::vec4(EyePos, 1.0f));
}


void Scene::setShader(ShaderProgram* shader)
{
    this->shader = shader;
}
