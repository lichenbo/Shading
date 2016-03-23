//
//  Mesh.hpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp
#include "glm.hpp"

#include "gl.h"

class Model_PLY;

class Mesh
{
public:
    Mesh();
    void Load(const char* filename);
    void LoadSquare();
    void Draw();
    void BindVertexAttribute(GLint loc);
    void BindNormalAttribute(GLint loc);
    void BindTextureAttribute(GLint loc);
    void BindTangentAttribute(GLint loc);
    void BindModelUniform(GLint loc);
    void BindNormalUniform(GLint loc);
    
    void SetModelTrans(const glm::mat4& modelMatrix);
private:
    GLuint vao; // contains multiple vbos
    int numberOfVertices;
    
    // Buffers
    GLuint vbo_coord; // buffer stores vertices info
    GLuint vbo_normal; // buffer stores normal info
    GLuint vbo_texture;

	// Uniform
	glm::mat4 modelMatrix;
	glm::mat4 normalMatrix;
    
    GLfloat* vertex_data;
    GLfloat* normal_data;
    GLfloat* texture_data;
        
};


#endif /* Mesh_hpp */
