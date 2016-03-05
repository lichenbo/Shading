//
//  Mesh.hpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <OpenGL/gl3.h>

class Mesh
{
public:
    Mesh();
    void Load();
private:
    GLuint vao;
};


#endif /* Mesh_hpp */
