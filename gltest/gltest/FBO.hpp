//
//  FBO.hpp
//  gltest
//
//  Created by Chenbo Li on 3/19/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef FBO_hpp
#define FBO_hpp

#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#endif

class FBO
{
public:
    FBO(const int w, const int h, const int numOfTex);
    void Bind();
    void Unbind();
private:
    GLuint fbo;
    int w,h;
    int numOfTex;
};


#endif /* FBO_hpp */
