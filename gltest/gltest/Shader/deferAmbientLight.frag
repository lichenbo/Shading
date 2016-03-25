#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform vec3 ambientColor;

out vec4 outputColor;


void main(void)
{
	outputColor.xyz = ambientColor;
}