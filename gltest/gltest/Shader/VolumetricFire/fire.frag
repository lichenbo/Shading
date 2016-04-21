#version 330 core

#define M_PI 3.1415926535897932384626433832795

in vec2 texture_coord;
uniform vec3 eyePos;
uniform sampler2D firetex;

out vec4 outputColor;

void main()
{
	vec2 new_coord = vec2(texture_coord.s, 1-texture_coord.t);
	//vec2 new_coord = texture_coord;
	outputColor = texture(firetex, new_coord.st);

}