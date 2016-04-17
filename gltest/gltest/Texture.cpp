//
//  Texture.cpp
//  gltest
//
//  Created by Chenbo Li on 3/21/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "Texture.hpp"
#include <iostream>

Texture::Texture(const int w, const int h): w(w), h(h), unit(0)
{
    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
	CHECK_ERROR;
}

void Texture::LoadData(float* data)
{
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGBA, GL_FLOAT, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindToUnit(const int unit)
{
    this->unit = unit;
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
}

void Texture::BindToImageUnit(const int unit)
{
#ifdef _WIN32
	glBindImageTexture(unit, renderedTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
#endif
}

void Texture::Unbind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::textureId() const
{
    return renderedTexture;
}

int Texture::Width()
{
	return w;
}

int Texture::Height()
{
	return h;
}
