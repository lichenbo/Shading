//
//  ShaderProgram.cpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "ShaderProgram.hpp"
#include <iostream>
#include "Texture.hpp"

ShaderProgram::ShaderProgram():attribNormalLoc(-1), attribVertexLoc(-1), attribTangentLoc(-1), attribTextureLoc(-1), num_groups_x(0), num_groups_y(0), num_groups_z(0)
{
    CHECK_ERROR;
    programId = glCreateProgram();
    CHECK_ERROR;

}

bool ShaderProgram::AddVertexShaderPath(const char* path)
{
    CHECK_ERROR;
    const char* vertexShader = readFile(path);
    const char * src = vertexShader;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &src, NULL);
    CHECK_ERROR;
    return compileShader(vertexShaderId);
}

bool ShaderProgram::AddFragmentShaderPath(const char* path)
{
    CHECK_ERROR;
    const char* fragmentShader = readFile(path);
    const char* src = fragmentShader;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &src, NULL);
    CHECK_ERROR;
    return compileShader(fragmentShaderId);
}

bool ShaderProgram::SetComputeShaderPath(const char* path)
{
#ifdef _WIN32
    CHECK_ERROR;
	const char* computeShader = readFile(path);
	GLuint computeShaderId = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(computeShaderId, 1, &computeShader, NULL);
	compileShader(computeShaderId);
	glLinkProgram(programId);
	glDetachShader(programId, computeShaderId);
    CHECK_ERROR;
#endif
	return true;
}

bool ShaderProgram::SetupComputeShader(int num_groups_x, int num_groups_y, int num_groups_z)
{
#ifdef _WIN32
	this->num_groups_x = num_groups_x;
	this->num_groups_y = num_groups_y;
	this->num_groups_z = num_groups_z;
#endif
	return true;
}

bool ShaderProgram::compileShader(GLuint shaderId)
{
    CHECK_ERROR;

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
        CHECK_ERROR;
        return false;
    }
    
    glAttachShader(programId, shaderId);
    CHECK_ERROR;

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
        CHECK_ERROR;
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

void ShaderProgram::Use()
{
    glUseProgram(programId);
}

GLint ShaderProgram::GetAttribute(const char* attr_name)
{
    CHECK_ERROR;

    GLint attributeLoc;
    attributeLoc = glGetAttribLocation(programId, attr_name);
    if (attributeLoc == -1) std::cout << attr_name << " is invalid in shader" << std::endl;
    CHECK_ERROR;

    return attributeLoc;
}

GLint ShaderProgram::GetUniform(const char* uniform_name)
{
    CHECK_ERROR;

    GLint uniformLoc;
    uniformLoc = glGetUniformLocation(programId, uniform_name);
    if (uniformLoc == -1) std::cout << uniform_name << " is invalid in shader" << std::endl;
    CHECK_ERROR;

    return uniformLoc;
}

GLint ShaderProgram::GetUniformBlock(const char* block_name)
{
	GLint blockLoc;
	blockLoc = glGetUniformBlockIndex(programId, block_name);
	if (blockLoc == -1) std::cout << block_name << " is invalid in shader" << std::endl;
	return blockLoc;
}

void ShaderProgram::Unuse()
{
    glUseProgram(0);
}

void ShaderProgram::Compute()
{
#ifdef _WIN32
	glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
#endif
}

void ShaderProgram::SetAttribNormal(const char *attr_normal_name)
{
    attribNormalLoc = GetAttribute(attr_normal_name);
}

void ShaderProgram::SetAttribVertex(const char *attr_vertex_name)
{
    attribVertexLoc = GetAttribute(attr_vertex_name);
}

void ShaderProgram::SetAttribTangent(const char *attr_tangent_name)
{
    attribTangentLoc = GetAttribute(attr_tangent_name);
}

void ShaderProgram::SetAttribTexture(const char *attr_texture_name)
{
    attribTextureLoc = GetAttribute(attr_texture_name);
}

GLint ShaderProgram::GetAttribNormal()
{
    return attribNormalLoc;
}
GLint ShaderProgram::GetAttribVertex()
{
    return attribVertexLoc;
}
GLint ShaderProgram::GetAttribTangent()
{
    return attribTangentLoc;
}
GLint ShaderProgram::GetAttribTexture()
{
    return attribTextureLoc;
}

void ShaderProgram::BindUniformBlockToPoint(const char* block_name, int uniform_binding_point)
{
    CHECK_ERROR;
	int loc = GetUniformBlock(block_name);
	glUniformBlockBinding(programId, loc, uniform_binding_point);
    CHECK_ERROR;

}
