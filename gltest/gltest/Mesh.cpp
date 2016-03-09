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
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

Mesh::Mesh(): vao(0)
{
	//
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(20.0f));
	//modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	normalMatrix = glm::transpose(glm::inverse(modelMatrix));
	//normalMatrix = glm::inverse(modelMatrix);

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
    numberOfVertices = model->TotalConnectedTriangles;
	const GLfloat* vertex_buffer_data = model->Faces_Triangles;

	// -------------  VERTEX INPUT ATTRIBUTE -----------------
    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord);
    // Copy data from main memory to GPU memory, be aware of the result of sizeof()
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model->TotalConnectedTriangles * 3, vertex_buffer_data, GL_STATIC_DRAW);
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
	// --------------  VERTEX INPUT ATTRIBUTE ----------------


    // Load Normal Data
    const GLfloat* normal_buffer_data = model->Normals;

	// -------------  NORMAL INPUT ATTRIBUTE -----------------
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model->TotalConnectedTriangles * 3, normal_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(shader->normalLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(shader->normalLoc);
	// --------------  NORMAL INPUT ATTRIBUTE ----------------

	glBindVertexArray(0);
    
}

void Mesh::Draw(ShaderProgram* shader)
{
	glUniformMatrix4fv(shader->ModelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(shader->NormalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
	glBindVertexArray(0);
}