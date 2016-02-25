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

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}