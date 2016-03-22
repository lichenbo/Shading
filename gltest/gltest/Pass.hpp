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
    void BindUniformMatrix4(const char* uniform_name, ValueType& v);
    template<typename ValueType>
    void BindUniformVec3(const char* uniform_name, ValueType& v);
    void SetTarget(FBO* fbo);
    
    void BindAttribVertex(const char* vertex_attrib_name);
    void BindAttribNormal(const char* normal_attrib_name);
    void BindAttribTangent(const char* tangent_attrib_name);
    void BindAttribTexture(const char* texture_attrib_name);
    void BindUniformModel(const char* model_uniform_name);
    void BindUniformNormal(const char* normal_uniform_name);
    
private:
    Scene* scene;
    ShaderProgram* shader;
    FBO* targetFBO;
    GLint model_uniform_loc;
    GLint normal_uniform_loc;
};

// Using glm
template<typename ValueType>
void Pass::BindUniformMatrix4(const char* uniform_name, ValueType& v)
{
    GLint loc = shader->GetUniform(uniform_name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(v));
}

template<typename ValueType>
void Pass::BindUniformVec3(const char *uniform_name, ValueType& v)
{
    GLint loc = shader->GetUniform(uniform_name);
    glUniform3fv(loc, 1, glm::value_ptr(v));
}

#endif /* Pass_hpp */
