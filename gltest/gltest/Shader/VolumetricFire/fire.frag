#version 330 core

#define M_PI 3.1415926535897932384626433832795

in vec2 texture_coord;
uniform vec3 eyePos;

void main()
{
	gl_FragColor.xyz = vec3(1.0f, 0.0f, 0.0f);
}