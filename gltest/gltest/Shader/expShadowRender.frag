#version 330 core

#define M_PI 3.1415926535897932384626433832795
#define EXP 2.7182818284590452353602874713527

#define DEPTH 0.6

in vec2 texture_coord;
uniform mat4 shadowMatrix;
uniform vec3 lightPos;
uniform vec3 eyePos;
uniform vec3 lightValue;

uniform vec3 blurFactor;

uniform sampler2D shadowTexture;
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

out vec4 outputColor;
void main()
{
    vec4 positionVec = texture(positionTexture, texture_coord.st);
    positionVec.w = 1.0;
    vec3 normalVec = texture(normalTexture, texture_coord.st).xyz;
    vec3 lightVec = lightPos - positionVec.xyz;
    vec3 eyeVec = eyePos - positionVec.xyz;
    vec4 shadowCoord = shadowMatrix * positionVec;
    
    vec3 N = normalize(normalVec);
    vec3 L = normalize(lightVec);
    vec3 V = normalize(eyeVec);
    vec3 H = normalize(L+V);
    
    vec3 Kd = texture(diffuseTexture, texture_coord.st).xyz;
    vec3 Ks = texture(specularTexture, texture_coord.st).xyz;
    vec3 I = lightValue;
    vec3 F;
    float D;
    float G;
    
    vec2 shadowIndex = shadowCoord.xy/shadowCoord.w;
    outputColor = vec4(0.0, 0.0, 0.0, 0.7);
    
    float filteredLightDepth = texture(shadowTexture, shadowIndex).w;
    float pixelDepth = shadowCoord.w;
    
    float shadowFactor = filteredLightDepth * exp(-blurFactor.x*pixelDepth);
    if (shadowFactor > 1.0)
        shadowFactor = 1.0;
    
        float g = 0.5;
        float alpha = pow(8192, g);
        F = Ks + (1 - Ks) * pow((1 - dot(L, H)), 5);
        D = ((alpha + 2)/(2*M_PI))*pow(max(0.0,dot(N, H)), alpha);
        G = 1.0 / (dot(L,H) * dot(L,H));
        I = I * M_PI;
        if (dot(L, N) > 0) {
            outputColor.xyz += (Kd / M_PI + 0.25 * F * D *G) * dot(L, N) * I * shadowFactor;
        }

}
