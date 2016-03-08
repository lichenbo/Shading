//
//  Engine.hpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <vector>
#include "ShaderProgram.hpp"

class Scene;

class Engine
{
public:
    Engine(int argc, char ** argv);
    
    void render();
    void setScene(Scene* scene);
    
private:
    Scene* scene;
    
};

#endif /* Engine_hpp */
