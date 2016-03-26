//
//  Pass.hpp
//  gltest
//
//  Created by Chenbo Li on 3/19/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Pass_hpp
#define Pass_hpp


#include "gl.h"
#include "ShaderProgram.hpp"
#include <unordered_map>
#include "Mesh.hpp"
class Texture;
class Scene;
class FBO;
class ShaderProgram;

class Pass
{
public:
    Pass(ShaderProgram* shader, Scene* scene);
    void Draw();
    void addSpin(float);
    void addTilt(float);
    void addZoom(int);
    void addTrans(float);
    template<typename ValueType>
    void BindUniformMatrix4(const char* uniform_name, ValueType v);
    template<typename ValueType>
    void BindUniformVec3(const char* uniform_name, ValueType v);
    template<typename ValueType>
    void BindUniformInt1(const char* uniform_name, ValueType v);
    
    void SetTarget(FBO* fbo);
	void SetBlend(bool status);
	void SetDepthTest(bool status);
	void SetCullfaceFront(bool status);
	void SetCullfaceBack(bool status);
    
    void BindAttribVertex();
    void BindAttribNormal();
    void BindAttribTangent();
    void BindAttribTexture();

	void BindTexture(const char* uniform_texture_name, Texture* texture);
    
    template<typename ValueType>
    void MeshBindUniformMatrix4(Mesh* mesh, const char* uniform_name, ValueType v);
    template<typename ValueType>
    void MeshBindUniformVec3(Mesh* mesh, const char* uniform_name, ValueType v);
    template<typename ValueType>
    void MeshBindUniformInt1(Mesh* mesh, const char* uniform_name, ValueType v);

    
private:
    void RebindUniforms();

    Scene* scene;
    ShaderProgram* shader;
    FBO* targetFBO;
	int numOfTexture;
	bool isBlend;
	bool isDepthTest;
	bool isCullfaceFront;
	bool isCullfaceBack;
	
    
    std::unordered_map<GLint, GLfloat**> UniformMatrix4Mapper;
    std::unordered_map<GLint, GLfloat**> UniformVec3Mapper;
    std::unordered_map<GLint, GLint> UniformInt1Mapper;
	std::unordered_map<Texture*, int> TextureUnitMapper;
    
};

// Using glm
template<typename ValueType>
void Pass::BindUniformMatrix4(const char* uniform_name, ValueType v)
{
    GLint loc = shader->GetUniform(uniform_name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, *v);
    UniformMatrix4Mapper[loc] = (GLfloat**)v;
}

template<typename ValueType>
void Pass::BindUniformVec3(const char *uniform_name, ValueType v)
{
    GLint loc = shader->GetUniform(uniform_name);
    glUniform3fv(loc, 1, *v);
    UniformVec3Mapper[loc] = (GLfloat**)v;
}

template<typename ValueType>
void Pass::BindUniformInt1(const char* uniform_name, ValueType v)
{
    GLint loc = shader->GetUniform(uniform_name);
    glUniform1i(loc, v);
    UniformInt1Mapper[loc] = (GLint)v;
}

template<typename ValueType>
void Pass::MeshBindUniformMatrix4(Mesh* mesh, const char* uniform_name, ValueType v)
{
    GLint loc = shader->GetUniform(uniform_name);
    mesh->BindUniformMatrix4(loc, v);
}
template<typename ValueType>
void Pass::MeshBindUniformVec3(Mesh* mesh, const char* uniform_name, ValueType v)
{
    GLint loc = shader->GetUniform(uniform_name);
    mesh->BindUniformVec3(loc, v);
}
template<typename ValueType>
void Pass::MeshBindUniformInt1(Mesh* mesh, const char* uniform_name, ValueType v)
{
    GLint loc = shader->GetUniform(uniform_name);
    mesh->BindUniformInt1(loc, v);
}

#endif /* Pass_hpp */
