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
	void addSpin(float delta_x);
	void addTilt(float delta_y);
	void addZoom(float delta_z);
	void addTrans(float delta_move);
private:
    std::list<Mesh*> objects;
    ShaderProgram* shader;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 EyePos;
	glm::vec3 LightPos;
	glm::vec3 UpPos;
};


#endif /* Scene_hpp */
