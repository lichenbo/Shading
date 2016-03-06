//
//  Mesh.cpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "Mesh.hpp"
#include "Model_PLY.h"

Mesh::Mesh(): vao(0)
{
    glGenVertexArrays(1, &vao);
}

void Mesh::Load()
{

    glBindVertexArray(vao);
    
}