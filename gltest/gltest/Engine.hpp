//
//  Engine.hpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <list>
#include "Mesh.hpp"
#include "ShaderProgram.hpp"


class Engine
{
public:
    Engine(int argc, char ** argv);
    
    void render(ShaderProgram* shader);
    void addMesh(Mesh* mesh);
    
private:
    std::list<Mesh*> meshes;
    
};

#endif /* Engine_hpp */
