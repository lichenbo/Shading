#version 330 core

#define M_PI 3.1415926535897932384626433832795

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
uniform sampler2D domeTexture;

uniform HammersleyBlock
{
	float Number;
	float hammersley[2*100];
};

out vec4 outputColor;

float g = 0.5;
float alpha = pow(8192, g);

vec3 BRDF(vec3 Ks, vec3 L, vec3 V, vec3 N)
{
    vec3 H = normalize(L+V);
    vec3 F = Ks + (1 - Ks) * pow((1 - dot(L, H)), 5);
    float D = ((alpha + 2)/(2*M_PI))*pow(max(0.0,dot(N, H)), alpha);
    float G = 1.0 / (dot(L,H) * dot(L,H));
    
    return 0.25*F*D*G;
}

vec2 getSphereMapCoord(vec3 N)
{
	float u = 0.5 - atan(N.z/N.x)/(2*M_PI);
	float v = acos(N.y)/M_PI;
	return vec2(u,v);
}

vec3 buildSpheCoord(float xi1, float xi2, float alpha)
{
	float u = xi1;
	float v = acos(pow(xi2, 1/(alpha+1)))/M_PI;
	float x = cos(2*M_PI*(0.5-u))*sin(M_PI*v);
	float y = sin(2*M_PI*(0.5-u))*sin(M_PI*v);
	float z = cos(M_PI*v);
	return vec3(x,z,y); // fix for Herron's code
}


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
    
    vec3 Kd = texture(diffuseTexture, texture_coord.st).xyz;
    vec3 Ks = texture(specularTexture, texture_coord.st).xyz;
    vec3 I = lightValue;

    
    vec2 shadowIndex = shadowCoord.xy/shadowCoord.w;
    outputColor = vec4(0.0, 0.0, 0.0, 0.7);
    
    float filteredLightDepth = texture(shadowTexture, shadowIndex).w;
    float pixelDepth = shadowCoord.w;
    
    float shadowFactor = filteredLightDepth * exp(-blurFactor.x*pixelDepth);
    if (shadowFactor > 1.0)
        shadowFactor = 1.0;
    


	vec3 R = 2*dot(N,V)*N - V;
	vec3 A = normalize(cross(vec3(0,0,1),R));   //z-axis as spec dir
	vec3 B = normalize(cross(R,A));

	for (int i = 0; i < Number; ++i)
	{
		vec3 spheCoord = buildSpheCoord(hammersley[2*i],hammersley[2*i+1], alpha);
		vec3 OmegaK = normalize(spheCoord.x*A+spheCoord.y*B+spheCoord.z*R);
		L = OmegaK;	// L is light direction
		I = I * M_PI;
		// Confused.
		//float level = 0.5*log2(WIDTH*HEIGHT/N)-0.5*log2(D/4);
        float level = 1.0;
		vec3 LightIn = textureLod(domeTexture, getSphereMapCoord(L) ,level).xyz;
		if (dot(L, N) > 0) {
			outputColor.xyz += BRDF(Ks,L,V,N) * LightIn *dot(L,N)* I * shadowFactor / Number;
		}
	}
	

}

