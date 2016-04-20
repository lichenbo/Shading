#version 330 core

#define M_PI 3.1415926535897932384626433832795

in vec2 texture_coord;
uniform vec3 eyePos;
uniform sampler2D firetex;

out vec4 outputColor;

void main()
{
	outputColor.xyz = texture(firetex, texture_coord.st);
}