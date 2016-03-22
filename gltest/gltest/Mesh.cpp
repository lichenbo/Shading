//
//  Mesh.cpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "Mesh.hpp"
#include "Model_PLY.h"
#include "ShaderProgram.hpp"
#include "gl.h"

Mesh::Mesh(): vao(0)
{
	modelMatrix = glm::mat4(1.0f);

	normalMatrix = glm::transpose(glm::inverse(modelMatrix));

    // Generate VAO
    glGenVertexArrays(1, &vao);

    // Generate VBOs
    glGenBuffers(1, &vbo_normal);
}

void Mesh::SetModelTrans(const glm::mat4& modelMatrix)
{
    this->modelMatrix = modelMatrix;
    this->normalMatrix = glm::transpose(glm::inverse(modelMatrix));
}


// 3 floats, NO TRANSPOSE
void Mesh::BindVertexAttribute(GLint loc)
{
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo_coord);
    const GLfloat* vertex_buffer_data = model->Faces_Triangles;
    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord);
    // Copy data from main memory to GPU memory, be aware of the result of sizeof()
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model->TotalConnectedTriangles * 3, vertex_buffer_data, GL_STATIC_DRAW);
    // Always refer to GL_ARRAY_BUFFER
    glVertexAttribPointer(
                          loc, // attribute 0, matching layout in shader
                          3, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0, // stride
                          (void*)0 // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(loc);
    glBindVertexArray(0);
}

// 3 floats, NO TRANSPOSE
void Mesh::BindNormalAttribute(GLint loc)
{
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo_normal);
    const GLfloat* normal_buffer_data = model->Normals;
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model->TotalConnectedTriangles * 3, normal_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(loc);
    
    glBindVertexArray(0);
}

void Mesh::BindTextureAttribute(GLint loc)
{
    
}

void Mesh::BindTangentAttribute(GLint loc)
{
    
}

void Mesh::BindModelUniform(GLint loc)
{
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Mesh::BindNormalUniform(GLint loc)
{
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void Mesh::Load(const char* filename)
{
    model = new Model_PLY();
    model->Load(filename);
    numberOfVertices = model->TotalConnectedTriangles;
}

void Mesh::LoadSquare()
{
    
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
	glBindVertexArray(0);
}