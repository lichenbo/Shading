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
#include "ShaderProgram.hpp"

class Pass;

class Engine
{
public:
    Engine(int argc, char ** argv);
    
    void render();
    void addPass(Pass* pass);
	void UpdateMouseStatus(int x, int y, void(*spin)(float), void(*tilt)(float));
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int dir, void(*zoom)(float));
	void keyRelease(unsigned char c, void(*trans)(float));
private:
    std::list<Pass*> passes;
	int lastX, lastY;
    
};

#endif /* Engine_hpp */
