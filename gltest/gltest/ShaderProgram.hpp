//
//  ShaderProgram.hpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <fstream>


#ifdef _WIN32
	#include <GL/glew.h>
#else
	#include <OpenGL/gl3.h>
	#include <GLUT/glut.h>
#endif


class ShaderProgram
{
    friend class Mesh;
public:
    ShaderProgram();
    bool AddVertexShaderPath(const char* path);
    bool AddFragmentShaderPath(const char* path);
    bool Link();
    void Bind();
    void Unbind();
    void BindAttribute();
    void BindUniform();
    
private:
    GLuint vertexShaderId;
    GLuint fragmentShaderId;
    
    char* readFile(const char* path);
    bool compileShader(GLuint shaderId);
    
    GLuint programId;
    
    GLint vertexLoc;
    GLint normalLoc;
};

#endif /* ShaderProgram_hpp */
