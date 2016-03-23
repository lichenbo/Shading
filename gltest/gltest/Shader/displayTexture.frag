#version 330 core

#define M_PI 3.1415926535897932384626433832795

in vec2 texCoord;
out vec4 outputColor;

uniform sampler2D texture2D;

void main(void)
{
    outputColor.xyz = texture(texture2D, texCoord.st).xyz;
}