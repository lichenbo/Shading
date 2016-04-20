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
#include <unordered_map>
#include "gl.h"

class Model_PLY;
class Texture;

class Mesh
{
public:
    Mesh();
    void Load(const char* filename);
    void LoadSquare();
	float getBSplineT(int i, int n, int degree);
	void LoadBSpline(std::vector<glm::vec3> controlPoints, int degree);
    void Draw();
    void BindVertexAttribute(GLint loc);
    void BindNormalAttribute(GLint loc);
    void BindTextureAttribute(GLint loc);
    void BindTangentAttribute(GLint loc);
    
    template<typename ValueType>
    void BindUniformMatrix4(GLint loc, ValueType v);
    template<typename ValueType>
    void BindUniformVec3(GLint loc, ValueType v);
    template<typename ValueType>
    void BindUniformInt1(GLint loc, ValueType v);
    void BindTexture(const char* uniform_texture_name, Texture* texture);
    
private:
    void RebindUniforms();
    GLuint vao; // contains multiple vbos
    int numberOfVertices;
    
    // Buffers
    GLuint vbo_coord; // buffer stores vertices info
    GLuint vbo_normal; // buffer stores normal info
    GLuint vbo_texture;
	GLuint vbo_tangent;

	// Uniform
    
    GLfloat* vertex_data;
    GLfloat* normal_data;
    GLfloat* texture_data;
    
    std::unordered_map<GLint, GLfloat**> UniformMatrix4Mapper;
    std::unordered_map<GLint, GLfloat**> UniformVec3Mapper;
    std::unordered_map<GLint, GLint> UniformInt1Mapper;
    std::unordered_map<Texture*, int> TextureUnitMapper;
        
};

// Using glm
template<typename ValueType>
void Mesh::BindUniformMatrix4(GLint loc, ValueType v)
{
    glUniformMatrix4fv(loc, 1, GL_FALSE, *v);
    UniformMatrix4Mapper[loc] = (GLfloat**)v;
}

template<typename ValueType>
void Mesh::BindUniformVec3(GLint loc, ValueType v)
{
    glUniform3fv(loc, 1, *v);
    UniformVec3Mapper[loc] = (GLfloat**)v;
}

template<typename ValueType>
void Mesh::BindUniformInt1(GLint loc, ValueType v)
{
    glUniform1i(loc, v);
    UniformInt1Mapper[loc] = (GLint)v;
}


#endif /* Mesh_hpp */
