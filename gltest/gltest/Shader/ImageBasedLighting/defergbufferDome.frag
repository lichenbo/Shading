#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 gloss;
uniform sampler2D domeTexture;
uniform int isDome;
uniform vec3 eyePos;

in vec3 worldSpacePosition;
in vec3 worldSpaceNormal;

out vec4 outputColor;

layout(location = 0) out vec4 gposition;
layout(location = 1) out vec4 gnormal;
layout(location = 2) out vec3 gdiffuse;
layout(location = 3) out vec3 gspecular;
layout(location = 4) out vec3 ggloss;

vec3 sRGB2Linear(vec4 pixel);
vec3 Linear2sRGB(vec4 pixel);

void main(void)
{
	gposition.xyz = worldSpacePosition;
	gposition.w = 1.0;
	gnormal.xyz = worldSpaceNormal;
	gnormal.w = 0.0;
	gspecular = specular;
	ggloss = gloss;
    
    vec3 D = worldSpacePosition - eyePos;
    D = normalize(D);
    if (isDome == 1)
    {
		vec4 pixel = texture(domeTexture, vec2(0.5+atan(D.z,D.x)/(2*M_PI),0.5- asin(D.y)/M_PI));
        gdiffuse = Linear2sRGB(pixel);
        
    }
    else
    {
		gdiffuse = diffuse;
    }

}

vec3 sRGB2Linear(vec4 pixel)
{
	float exposure = pixel.w;
    vec3 converted = exposure*pixel.xyz/(exposure*pixel.xyz+vec3(1,1,1));
    return vec3(pow(converted.x, 2.2),pow(converted.y, 2.2),pow(converted.z, 2.2));
}

vec3 Linear2sRGB(vec4 pixel)
{
	float exposure = pixel.w;
    vec3 converted = exposure*pixel.xyz/(exposure*pixel.xyz+vec3(1,1,1));
    return vec3(pow(converted.x, 1/2.2),pow(converted.y, 1/2.2),pow(converted.z, 1/2.2));
}