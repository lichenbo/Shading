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


#ifdef _WIN32
	#include <GL/glew.h>
#else
	#include <OpenGL/gl3.h>
	#include <GLUT/glut.h>
#endif


class ShaderProgram
{
    friend class Mesh;
    friend class Pass;
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
    
    std::list<GLint> attributesLoc;
    std::list<GLint> uniformsLoc;
    
	// Attribute
    GLint vertexLoc;
    GLint normalLoc;


	// Uniform
	GLint ModelMatrixLoc;
	GLint NormalMatrixLoc;
	GLint ViewMatrixLoc;
	GLint ViewInverseMatrixLoc;
	GLint ProjectionMatrixLoc;
	GLint EyePosLoc;
};

#endif /* ShaderProgram_hpp */
