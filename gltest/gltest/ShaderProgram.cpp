//
//  ShaderProgram.cpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "ShaderProgram.hpp"
#include <iostream>

ShaderProgram::ShaderProgram()
{
    programId = glCreateProgram();
}

bool ShaderProgram::AddVertexShaderPath(const char* path)
{
    const char* vertexShader = readFile(path);
    const char * src = vertexShader;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &src, NULL);
    
    return compileShader(vertexShaderId);
}

bool ShaderProgram::AddFragmentShaderPath(const char* path)
{
    const char* fragmentShader = readFile(path);
    const char* src = fragmentShader;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &src, NULL);
    
    return compileShader(fragmentShaderId);
}

bool ShaderProgram::compileShader(GLuint shaderId)
{
    glCompileShader(shaderId);
    
    GLint info;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &info);
    
    if (info != 1)
    {
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &info);
        GLchar* logBuffer = new char[info];
        glGetShaderInfoLog(shaderId, info, NULL, logBuffer);
        std::cout << "shader compilation error" << std::endl;
        std::cout << logBuffer <<std::endl;
        delete logBuffer;
        return false;
    }
    
    glAttachShader(programId, shaderId);
    return true;
}

bool ShaderProgram::Link()
{
    glLinkProgram(programId);
    
    GLint info;
    glGetProgramiv(programId, GL_LINK_STATUS, &info);
    if (info != 1)
    {
        glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &info);
        GLchar* logBuffer = new char[info];
        glGetShaderInfoLog(programId, info, NULL, logBuffer);
        std::cout << "shader linking error" << std::endl;
        std::cout << logBuffer <<std::endl;
        delete logBuffer;
        return false;
    }
    
    // Detach shader after linking successfully
    glDetachShader(programId, fragmentShaderId);
    glDetachShader(programId, vertexShaderId);
    
    return true;
}

char* ShaderProgram::readFile(const char * path)
{
    
    std::ifstream ifs(path, std::ifstream::binary);
    
    if (!ifs.is_open())
    {
        std::cout << "Failed to open file " << path << std::endl;
    }
    
    ifs.seekg(0, std::ios_base::end);
    int fileLength = static_cast<int>(ifs.tellg());
    
    char* content = new char[fileLength+1];
    ifs.seekg(0, std::ios_base::beg);
    ifs.read(content, fileLength);
    ifs.close();
    
    content[fileLength] = char(0);
    return content;
}

void ShaderProgram::Bind()
{
    glUseProgram(programId);
}

void ShaderProgram::BindAttribute()
{
    vertexLoc = glGetAttribLocation(programId, "vertex_coord");
    if (vertexLoc == -1) std::cout << "vertex_coord is invalid" << std::endl;

	normalLoc = glGetAttribLocation(programId, "normal_coord");
	if (normalLoc == -1) std::cout << "normal_coord is invalid" << std::endl;
}

void ShaderProgram::BindUniform()
{
	ModelMatrixLoc = glGetUniformLocation(programId, "ModelMatrix");
	if (ModelMatrixLoc== -1) std::cout << "ModelMatrixLoc is invalid" << std::endl;

	NormalMatrixLoc = glGetUniformLocation(programId, "NormalMatrix");
	if (NormalMatrixLoc== -1) std::cout << "NormalMatrixLoc is invalid" << std::endl;

	ViewMatrixLoc = glGetUniformLocation(programId, "ViewMatrix");
	if (ViewMatrixLoc == -1) std::cout << "ViewMatrixLoc is invalid" << std::endl;

	ViewInverseMatrixLoc = glGetUniformLocation(programId, "ViewInverseMatrix");
	if (ViewInverseMatrixLoc == -1) std::cout << "ViewInverseMatrixLoc is invalid" << std::endl;

	ProjectionMatrixLoc = glGetUniformLocation(programId, "ProjectionMatrix");
	if (ProjectionMatrixLoc == -1) std::cout << "ProjectionMatrixLoc is invalid" << std::endl;

	EyePosLoc = glGetUniformLocation(programId, "EyePos");
	if (EyePosLoc == -1) std::cout << "EyePosLoc is invalid" << std::endl;

    return;
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}