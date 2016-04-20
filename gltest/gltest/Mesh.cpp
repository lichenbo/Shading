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
#include "BSpline.h"

Mesh::Mesh(): vao(0)
{
    // Generate VAO
    glGenVertexArrays(1, &vao);

}


// 3 floats, NO TRANSPOSE
void Mesh::BindVertexAttribute(GLint loc)
{
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo_coord);
    const GLfloat* vertex_buffer_data = vertex_data;
    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord);
    // Copy data from main memory to GPU memory, be aware of the result of sizeof()
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numberOfVertices * 3, vertex_buffer_data, GL_STATIC_DRAW);
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
    CHECK_ERROR;

}

// 3 floats, NO TRANSPOSE
void Mesh::BindNormalAttribute(GLint loc)
{
    CHECK_ERROR;

    glBindVertexArray(vao);
    glGenBuffers(1, &vbo_normal);
    const GLfloat* normal_buffer_data = normal_data;
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numberOfVertices * 3, normal_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(loc);
    
    glBindVertexArray(0);
    CHECK_ERROR;

}

void Mesh::BindTextureAttribute(GLint loc)
{
    CHECK_ERROR;

    glBindVertexArray(vao);
    glGenBuffers(1, &vbo_texture);
    const GLfloat* texture_buffer_data = texture_data;
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_texture);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numberOfVertices*2, texture_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(loc);
    glBindVertexArray(0);
    CHECK_ERROR;

}

void Mesh::BindTangentAttribute(GLint loc)
{
    
}

void Mesh::Load(const char* filename)
{
    Model_PLY* model = new Model_PLY();
    model->Load(filename);
    numberOfVertices = model->TotalConnectedTriangles;
    vertex_data = model->Faces_Triangles;
    normal_data = model->Normals;
	texture_data = model->Textures;
}

//void Mesh::LoadPoint()
//{
//	vertex_data = new GLfloat[3];
//	vertex_data[0] = 0.0f;
//	vertex_data[1] = 0.0f;
//	vertex_data[2] = 0.0f;
//
//	normal_data[0] = 0.0f;
//
//
//}

void Mesh::LoadSquare()
{
    numberOfVertices = 6;
    vertex_data = new GLfloat[3 * numberOfVertices];
    
    vertex_data[0] = -1.0f;
    vertex_data[1] = -1.0f;
    vertex_data[2] = 0.0f;
    
    vertex_data[3] = 1.0f;
    vertex_data[4] = 1.0f;
    vertex_data[5] = 0.0f;
    
    vertex_data[6] = -1.0f;
    vertex_data[7] = 1.0f;
    vertex_data[8] = 0.0f;
    
    vertex_data[9] = 1.0f;
    vertex_data[10] = 1.0f;
    vertex_data[11] = 0.0f;
    
    vertex_data[12] = -1.0f;
    vertex_data[13] = -1.0f;
    vertex_data[14] = 0.0f;
    
    vertex_data[15] = 1.0f;
    vertex_data[16] = -1.0f;
    vertex_data[17] = 0.0f;
    
    normal_data = new GLfloat[3 * numberOfVertices];
    
    for (int i = 0; i < 3*numberOfVertices; i = i+3)
    {
        normal_data[i] = 0.0f;
        normal_data[i+1] = 0.0f;
        normal_data[i+2] = 1.0f;
    }
    
    texture_data = new GLfloat[2*numberOfVertices];
    
    texture_data[0] = 0.0f;
    texture_data[1] = 0.0f;
    
    texture_data[2] = 1.0f;
    texture_data[3] = 1.0f;
    
    texture_data[4] = 0.0f;
    texture_data[5] = 1.0f;
    
    texture_data[6] = 1.0f;
    texture_data[7] = 1.0f;
    
    texture_data[8] = 0.0f;
    texture_data[9] = 0.0f;
    
    texture_data[10] = 1.0f;
    texture_data[11] = 0.0f;
    
}

void Mesh::LoadBSpline(std::vector<glm::vec3> uniformControlPoints, int degree)
{
	numberOfVertices = uniformControlPoints.size() * 50;
	BSpline b(uniformControlPoints, degree);
	float interval = 1.0 / numberOfVertices;
	vertex_data = new GLfloat[3 * numberOfVertices];
	int data_index = 0;
	for (float i = 0.0f; i < 1.0f; i+=interval)
	{
		glm::vec3 point = b.Value(i);
		vertex_data[data_index] = point.x;
		vertex_data[data_index + 1] = point.y;
		vertex_data[data_index + 2] = point.z;
		data_index += 3;
	}

	normal_data = new GLfloat[3 * numberOfVertices];
	for (int i = 1; i < numberOfVertices-1; ++i)
	{
		glm::vec3 prevPoint(vertex_data[3 * i - 3], vertex_data[3 * i - 2], vertex_data[3 * i - 1]);
		glm::vec3 nextPoint(vertex_data[3 * i + 3], vertex_data[3 * i + 4], vertex_data[3 * i + 5]);
		glm::vec3 dirVec = nextPoint - prevPoint;
		normal_data[3 * i] = dirVec.x;
		normal_data[3 * i + 1] = dirVec.y;
		normal_data[3 * i + 2] = dirVec.z;
	}
	normal_data[0] = 0.0f;
	normal_data[1] = 1.0f;
	normal_data[2] = 0.0f;
	normal_data[3 * numberOfVertices - 3] = 0.0f;
	normal_data[3 * numberOfVertices - 2] = 1.0f;
	normal_data[3 * numberOfVertices - 1] = 0.0f;
	
	
}

void Mesh::Draw()
{
    CHECK_ERROR;
    RebindUniforms();
	glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
	glBindVertexArray(0);
    CHECK_ERROR;

}

void Mesh::RebindUniforms()
{
    CHECK_ERROR;
    for (auto item : UniformMatrix4Mapper)
    {
        glUniformMatrix4fv(item.first, 1, GL_FALSE, *(item.second));
    }
    for (auto item : UniformVec3Mapper)
    {
        glUniform3fv(item.first, 1, *(item.second));
    }
    for (auto item : UniformInt1Mapper)
    {
        glUniform1i(item.first, item.second);
    }
    CHECK_ERROR;

}