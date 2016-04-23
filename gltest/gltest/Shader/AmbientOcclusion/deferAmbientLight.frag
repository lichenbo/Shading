#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform sampler2D diffuseTexture;
uniform sampler2D domeIrrTexture;
uniform sampler2D normalTexture;
uniform sampler2D aoTexture;

in vec2 texture_coord;
out vec4 outputColor;

vec3 Linear2sRGB(vec4 pixel)
{
	float exposure = pixel.w;
    vec3 converted = exposure*pixel.xyz/(exposure*pixel.xyz+vec3(1,1,1));
    return vec3(pow(converted.x, 1/2.2),pow(converted.y, 1/2.2),pow(converted.z, 1/2.2));
}

void main(void)
{
	vec3 gnormal = texture(normalTexture, texture_coord).xyz;
	vec4 pixel= texture(domeIrrTexture, vec2(0.5+atan(gnormal.z, gnormal.x)/(2*M_PI), 0.5-asin(gnormal.y)/M_PI));
    vec3 ambientColor = Linear2sRGB(pixel) * 4;
    //vec3 ambientColor = Linear2sRGB(pixel) / M_PI;
	float ambientFactor = texture(aoTexture, texture_coord.st).x;
    outputColor.xyz = ambientFactor * ambientColor * texture(diffuseTexture, texture_coord.st).xyz;

}