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
	EyePos = glm::vec3(0.5f, 1.0f, 1.0f);
	LightPos = glm::vec3(10.0f, 10.0f, 10.0f);
	ViewMatrix = glm::lookAt(EyePos, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	ProjectionMatrix = glm::perspective(60.0f, 0.5f, 0.5f, 100.0f);
}


void Scene::addObject(Mesh* mesh)
{
    objects.push_back(mesh);
}

void Scene::Draw()
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->Bind();
	glUniformMatrix4fv(shader->ViewMatrixLoc, 1, GL_TRUE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(shader->ViewInverseMatrixLoc, 1, GL_TRUE, glm::value_ptr(glm::inverse(ViewMatrix)));
	glUniformMatrix4fv(shader->ProjectionMatrixLoc, 1, GL_TRUE, glm::value_ptr(ProjectionMatrix));

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