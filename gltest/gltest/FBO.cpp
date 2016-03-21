//
//  FBO.cpp
//  gltest
//
//  Created by Chenbo Li on 3/19/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "FBO.hpp"
#include <iostream>


FBO::FBO(const int w, const int h, const int numOfTex):w(w), h(h), numOfTex(numOfTex)
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    
    
    GLenum* DrawBuffers = new GLenum[numOfTex];
    for (int i = 0; i < numOfTex; ++i)
    {
        GLuint renderedTexture;
        glGenTextures(1, &renderedTexture);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGBA, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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

