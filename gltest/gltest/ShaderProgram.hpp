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
    void SetUniformModel(const char* uniform_model_name);
    void SetUniformView(const char* uniform_view_name);
    void SetUniformPerspective(const char* uniform_perspective_name);
    void SetUniformNormal(const char* uniform_normal_name);
    GLint GetAttribVertex();
    GLint GetAttribNormal();
    GLint GetAttribTangent();
    GLint GetAttribTexture();
    GLint GetUniformModel();
    GLint GetUniformView();
    GLint GetUniformPerspective();
    GLint GetUniformNormal();
    
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
    GLint uniformModelLoc;
    GLint uniformViewLoc;
    GLint uniformPerspectiveLoc;
    GLint uniformNormalLoc;
};

#endif /* ShaderProgram_hpp */
