#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform vec3 diffuse;
uniform vec3 specular;

in vec3 worldSpacePosition;
in vec3 worldSpaceNormal;

out vec4 outputColor;

layout(location = 0) out vec4 gposition;
layout(location = 1) out vec4 gnormal;
layout(location = 2) out vec3 gdiffuse;
layout(location = 3) out vec3 gspecular;


void main(void)
{
	gposition.xyz = worldSpacePosition;
	gposition.w = 1.0;
	gnormal.xyz = worldSpaceNormal;
	gnormal.w = 0.0;
	gdiffuse = diffuse;
	gspecular = specular;

}