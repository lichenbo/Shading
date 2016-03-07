//
//  Scene.hpp
//  gltest
//
//  Created by Chenbo Li on 3/6/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp
#include <list>

class Mesh;
class ShaderProgram;

class Scene {
public:
    void addObject(Mesh* mesh);
    void setShader(ShaderProgram* shader);
    void Draw();
private:
    std::list<Mesh*> objects;
    ShaderProgram* shader;
};


#endif /* Scene_hpp */
