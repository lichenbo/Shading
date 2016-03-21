//
//  Pass.hpp
//  gltest
//
//  Created by Chenbo Li on 3/19/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Pass_hpp
#define Pass_hpp
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp";
#include "gtc/matrix_inverse.hpp"
#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#endif

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
    void BindUniformMatrix4(GLint loc, ValueType v);
    void SetTarget(FBO* fbo);
    
private:
    Scene* scene;
    ShaderProgram* shader;
    FBO* targetFBO;
};

// Using glm
template<typename ValueType>
void Pass::BindUniformMatrix4(GLint loc, ValueType v)
{
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(v));
}

#endif /* Pass_hpp */
