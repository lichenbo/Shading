//
//  ShaderProgram.hpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <list>
#include <fstream>
#include "gl.h"

class ShaderProgram
{
    friend class Mesh;
    friend class Pass;
public:
    ShaderProgram();
    bool AddVertexShaderPath(const char* path);
    bool AddFragmentShaderPath(const char* path);
	bool SetComputeShaderPath(const char* path);
	bool AddComputeShaderPath(const char* path);
	bool SetupComputeShader(int num_groups_x, int num_groups_y, int num_groups_z);
    bool Link();
    void Use();
    void Unuse();
	void Compute();

    GLint GetAttribute(const char* attr_name);
    GLint GetUniform(const char* uniform_name);
	GLint GetUniformBlock(const char* block_name);
	void SetAttribVertex(const char* attr_vertex_name);
    void SetAttribNormal(const char* attr_normal_name);
    void SetAttribTangent(const char* attr_tangent_name);
    void SetAttribTexture(const char* attr_texture_name);
    GLint GetAttribVertex();
    GLint GetAttribNormal();
    GLint GetAttribTangent();
    GLint GetAttribTexture();
	void BindUniformBlockToPoint(const char* block_name, int uniform_binding_point);

private:
    GLuint vertexShaderId;
    GLuint fragmentShaderId;
    
    char* readFile(const char* path);
    bool compileShader(GLuint shaderId);
    
    GLuint programId;
    
    GLint attribVertexLoc;
    GLint attribNormalLoc;
    GLint attribTangentLoc;
    GLint attribTextureLoc;

	int num_groups_x, num_groups_y, num_groups_z;
    
};

#endif /* ShaderProgram_hpp */
