#version 330 core

#define M_PI 3.1415926535897932384626433832795

in vec2 texture_coord;
uniform vec3 eyePos;
uniform sampler2D firetex;

out vec4 outputColor;

void main()
{
	outputColor = texture(firetex, texture_coord.st);
	//outputColor.xy = texture_coord.st;
	//outputColor.z = 0.0;
	//outputColor.w = 1.0;
}