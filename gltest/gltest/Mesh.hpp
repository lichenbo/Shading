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

#ifdef _WIN32
	#include <GL/glew.h>
#else
	#include <OpenGL/gl3.h>
	#include <OpenGL/glu.h>
#endif


class Mesh
{
public:
    Mesh();
    void Load();
private:
    GLuint vao;
};


#endif /* Mesh_hpp */
