#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform vec3 diffuse;
uniform vec3 specular;
uniform sampler2D domeTexture;
uniform sampler2D domeIrrTexture;
uniform int isDome;
uniform vec3 eyePos;

in vec3 worldSpacePosition;
in vec3 worldSpaceNormal;
in vec2 tex_coord;

out vec4 outputColor;

layout(location = 0) out vec4 gposition;
layout(location = 1) out vec4 gnormal;
layout(location = 2) out vec3 gdiffuse;
layout(location = 3) out vec3 gspecular;

vec3 sRGB2Linear(vec3 pixel);
vec3 Linear2sRGB(vec3 pixel);

void main(void)
{
	gposition.xyz = worldSpacePosition;
	gposition.w = 1.0;
	gnormal.xyz = worldSpaceNormal;
	gnormal.w = 0.0;
	gspecular = specular;
    
    vec3 D = worldSpacePosition - eyePos;
    D = worldSpaceNormal;
    if (isDome == 1)
    {
        //gdiffuse = texture(domeTexture, vec2(0.5-atan(D.z, D.x)/(2*M_PI), acos(D.y)/M_PI)).xyz;
        gdiffuse = texture(domeTexture, tex_coord).xyz;
        //gdiffuse = sRGB2Linear(gdiffuse);
        gdiffuse = Linear2sRGB(gdiffuse);
        
    }
    else
    {
        gdiffuse = diffuse/M_PI * texture(domeIrrTexture, gnormal.xz).xyz;
        //gdiffuse = sRGB2Linear(gdiffuse);
        gdiffuse = Linear2sRGB(gdiffuse);

    }

}

vec3 sRGB2Linear(vec3 pixel)
{
    float e = 10;
    vec3 converted = e*pixel/(e*pixel+vec3(1,1,1));
    return vec3(pow(converted.x, 2.2),pow(converted.y, 2.2),pow(converted.z, 2.2));
}

vec3 Linear2sRGB(vec3 pixel)
{
    float e = 10;
    vec3 converted = e*pixel/(e*pixel+vec3(1,1,1));
    return vec3(pow(converted.x, 1/2.2),pow(converted.y, 1/2.2),pow(converted.z, 1/2.2));
}