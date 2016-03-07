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
    glBindVertexArray(vao);

    // Generate VBOs
    glGenBuffers(1, &vbo_coord);
    glGenBuffers(1, &vbo_normal);
}

void Mesh::Load(const char* filename)
{
    Model_PLY *model = new Model_PLY();
    model->Load(filename);
    
    // Load Vertex Coord Data
    //const GLfloat* vertex_buffer_data = model->Vertex_Buffer;
    
    const GLfloat* vertex_buffer_data = new GLfloat[3] {0.0f, 1.0f, -1.0f};
    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord);
    // Copy data from main memory to GPU memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Load Normal Data
    const GLfloat* normal_buffer_data = model->Normals;
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal_buffer_data), normal_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    numberOfVertices = model->TotalConnectedPoints;
    
}

void Mesh::Draw(ShaderProgram* shader)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord);
    glEnableVertexAttribArray(shader->vertexLoc);

    // Always refer to GL_ARRAY_BUFFER
    glVertexAttribPointer(
                          shader->vertexLoc, // attribute 0, matching layout in shader
                          3, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0, // stride
                          (void*)0 // array buffer offset
                          );
    
    //glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
    glDrawArrays(GL_TRIANGLES, 0, 1);
    glDisableVertexAttribArray(shader->vertexLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}