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
    bool Link();
    void Use();
    void Unuse();

    GLint GetAttribute(const char* attr_name);
    GLint GetUniform(const char* uniform_name);
    void SetAttribVertex(const char* attr_vertex_name);
    void SetAttribNormal(const char* attr_normal_name);
    void SetAttribTangent(const char* attr_tangent_name);
    void SetAttribTexture(const char* attr_texture_name);
    GLint GetAttribVertex();
    GLint GetAttribNormal();
    GLint GetAttribTangent();
    GLint GetAttribTexture();

    
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
    
};

#endif /* ShaderProgram_hpp */
