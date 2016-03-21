//
//  Engine.cpp
//  gltest
//
//  Created by Chenbo Li on 2/24/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#include "Engine.hpp"
#include <iostream>
#include "Scene.hpp"
#include "Pass.hpp"

#ifdef _WIN32
	#include <GL/glew.h>
	#include <GL/freeglut.h>
#else
	#include <OpenGL/gl3.h>
	#include <GLUT/glut.h>
#endif


Engine::Engine(int argc, char ** argv)
{
    glutInit(&argc, argv);

#ifdef _WIN32
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
#elif defined __APPLE__
	// OSX needs core profile support
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE|GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
#endif

    glutInitWindowPosition(100, 300);
    glutInitWindowSize(800, 800);
	//glutInitContextVersion(4, 3);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Windows/OSX GL Demo");


#ifdef _WIN32
	glewExperimental = true; // Needed in core profile
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
	}
#endif

	//glEnable(GL_CULL_FACE|GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE|GL_DEPTH_TEST);
}

void Engine::render()
{
    for (Pass* p : passes)
    {
        p->Draw();
    }
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void Engine::addPass(Pass* pass)
{
    passes.push_back(pass);
}

void Engine::UpdateMouseStatus(int x, int y)
{
	float deltaX = x - lastX;
	float deltaY = y - lastY;

    for (Pass* p : passes)
    {
        p->addSpin(deltaX);
        p->addTilt(deltaY);
    }

	lastX = x;
	lastY = y;
}

void Engine::MouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		lastX = x;
		lastY = y;
	}
    if (button == 3)
    {
        // Scroll up for OSX
        MouseWheel(1);
    }
    if (button == 4)
    {
        // Scroll down for OSX
        MouseWheel(-1);
    }
}

void Engine::MouseWheel(int dir)
{
    for (Pass* p : passes)
    {
        p->addZoom(dir);
    }
}

void Engine::keyRelease(unsigned char c)
{
	float delta_move;
	if (c == 'a')
	{
		delta_move = -1;
	}
	if (c == 'd')
	{
		delta_move = 1;
	}
    else
    {
        return;
    }
    
    for (Pass* p : passes)
    {
        p->addTrans(delta_move);
    }
}

