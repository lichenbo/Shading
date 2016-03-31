//
//  Texture.hpp
//  gltest
//
//  Created by Chenbo Li on 3/21/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "gl.h"

class Texture
{
public:
    Texture(const int w, const int h);
    void LoadData(char* data);
    void BindToUnit(const int unit);
	void BindToImageUnit(const int unit);
	void Unbind();
    GLuint textureId() const;
	int Width();
	int Height();
private:
    GLuint renderedTexture;
    int w, h;
    int unit;
};
#endif /* Texture_hpp */
