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
	void UpdateMouseStatus(int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int dir);
	void keyRelease(unsigned char c);
private:
    Scene* scene;
	int lastX, lastY;
    
};

#endif /* Engine_hpp */
