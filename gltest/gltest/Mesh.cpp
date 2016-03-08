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

Mesh::Mesh(): vao(0)
{
    // Generate VAO
    glGenVertexArrays(1, &vao);

    // Generate VBOs
    glGenBuffers(1, &vbo_coord);
    glGenBuffers(1, &vbo_normal);

}

void Mesh::Load(const char* filename, ShaderProgram* shader)
{
    glBindVertexArray(vao);

    Model_PLY *model = new Model_PLY();
    model->Load(filename);
    
    // Load Vertex Coord Data
    numberOfVertices = model->TotalConnectedPoints;
    const GLfloat* vertex_buffer_data = model->Vertex_Buffer;

    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord);
    // Copy data from main memory to GPU memory, be aware of the result of sizeof()
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model->TotalConnectedPoints, vertex_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Load Normal Data
    const GLfloat* normal_buffer_data = model->Normals;
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model->TotalConnectedPoints, normal_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_coord);

	// Always refer to GL_ARRAY_BUFFER
	glVertexAttribPointer(
		shader->vertexLoc, // attribute 0, matching layout in shader
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized
		0, // stride
		(void*)0 // array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(shader->vertexLoc);

	glBindVertexArray(0);
    
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
	glBindVertexArray(0);
}