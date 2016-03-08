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
#include "glm.hpp"

class Mesh;
class ShaderProgram;

class Scene {
public:
	Scene();
    void addObject(Mesh* mesh);
    void setShader(ShaderProgram* shader);
    void Draw();
private:
    std::list<Mesh*> objects;
    ShaderProgram* shader;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 EyePos;
	glm::vec3 LightPos;
};


#endif /* Scene_hpp */
