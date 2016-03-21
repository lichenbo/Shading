//
//  Texture.hpp
//  gltest
//
//  Created by Chenbo Li on 3/21/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp
#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#endif

class Texture
{
public:
    Texture(const int w, const int h);
    void LoadData(char* data);
    void BindToUnit(const int unit);
    void Unbind();
    GLuint textureId() const;
private:
    GLuint renderedTexture;
    int w, h;
    int unit;
};
#endif /* Texture_hpp */
