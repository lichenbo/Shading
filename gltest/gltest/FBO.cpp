//
//  FBO.cpp
//  gltest
//
//  Created by Chenbo Li on 3/19/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "FBO.hpp"
#include <iostream>
#include "Texture.hpp"

FBO::FBO(const int w, const int h, const int numOfTex):w(w), h(h), numOfTex(numOfTex)
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    
    
    GLenum* DrawBuffers = new GLenum[numOfTex];
    for (int i = 0; i < numOfTex; ++i)
    {
        Texture tex(w,h);
        GLuint renderedTexture = tex.textureId();
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, renderedTexture, 0);
        DrawBuffers[i] = GL_COLOR_ATTACHMENT0+i;
    }
    glDrawBuffers(numOfTex, DrawBuffers);
    
    
    GLuint depthRenderBuffer;
    glGenRenderbuffers(1, &depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
    
    int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status!=GL_FRAMEBUFFER_COMPLETE)
        std::cout << "FBO Error:" << status << std::endl;
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FBO::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

