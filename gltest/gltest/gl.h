//
//  gl.h
//  gltest
//
//  Created by Chenbo Li on 3/22/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef gl_h
#define gl_h

#ifdef _WIN32
#include <GL/glew.h>
#include <GL/freeglut.h>
#else
#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#endif

#include <iostream>
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp";
#include "gtc/matrix_inverse.hpp";
#define CHECK_ERROR \
	if (int error = glGetError()) \
	{	\
		std::cout << error << " error in "<< __LINE__ << " of " << __FILE__ << std::endl;	\
	}

#endif /* gl_h */
