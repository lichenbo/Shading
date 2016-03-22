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
#include "gl.h"

class Mesh;

class Scene {
    friend class Pass;
public:
	Scene();
    void addObject(Mesh* mesh);
    
    // pass -1 is don't have
    void Draw(GLint modelLoc, GLint normalLoc);
    
    void BindVertex(GLint loc);
    void BindNormal(GLint loc);
    void BindTexture(GLint loc);
    void BindTangent(GLint loc);
    
private:
    std::list<Mesh*> objects;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 EyePos;
	glm::vec3 LightPos;
	glm::vec3 UpPos;
	glm::vec3 WatchPos;
};


#endif /* Scene_hpp */
