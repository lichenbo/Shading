#version 330 core

#define M_PI 3.1415926535897932384626433832795

in float depth;
out vec4 outputColor;

void main(void)
{
	outputColor.x = depth;
	outputColor.y = gl_PrimitiveID;
	outputColor.zw = vec2(0.0, 0.0);
}