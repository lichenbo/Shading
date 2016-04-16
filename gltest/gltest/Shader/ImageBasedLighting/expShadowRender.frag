#version 330 core

#define M_PI 3.1415926535897932384626433832795

in vec2 texture_coord;
uniform vec3 eyePos;

uniform vec3 blurFactor;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;
uniform sampler2D domeTexture;

uniform HammersleyBlock
{
	float Number;
	float hammersley[2*100];
};

out vec4 outputColor;

float g = 10;
float alpha = pow(8192, g);
vec3 lightValue = vec3(1.0);

vec3 MonteBRDF(vec3 Ks, vec3 L, vec3 V, vec3 N)
{
    L = normalize(L);
    V = normalize(V);
    vec3 H = normalize(L+V);
    // Schlick's approximation of the Fresnel equation
    vec3 F = Ks + (1 - Ks) * pow((1 - dot(L, H)), 5);
    float G = 1.0 / (dot(L,H) * dot(L,H));
    return 0.25*F*G;
}

vec2 getSphereMapCoord(vec3 N)
{
	float u = 0.5 + atan(N.z,N.x)/(2*M_PI);
	float v = 0.5 - asin(N.y)/M_PI;
	return vec2(u,v);
}

vec3 buildSpheCoord(float xi1, float xi2, float alpha)
{
	float u = xi1;
	float v = acos(pow(xi2, 1/(alpha+1)))/M_PI;
	float x = cos(2*M_PI*(0.5-u))*sin(M_PI*v);
	float y = sin((0.5-v)*M_PI);
	float z = sin(2*M_PI*(0.5-u))*sin(M_PI*v);

	return vec3(x,y,z); // fix for Herron's code
}
vec3 Linear2sRGB(vec4 pixel)
{
	float exposure = pixel.w;
    vec3 converted = exposure*pixel.xyz/(exposure*pixel.xyz+vec3(1,1,1));
    return vec3(pow(converted.x, 1/2.2),pow(converted.y, 1/2.2),pow(converted.z, 1/2.2));
}

float scaleToInterval(float value, float minDepth, float maxDepth)
{
	return (value - minDepth) / (maxDepth - minDepth);
}

void main()
{
    vec4 positionVec = texture(positionTexture, texture_coord.st);
    positionVec.w = 1.0;
    vec3 normalVec = texture(normalTexture, texture_coord.st).xyz;
    vec3 eyeVec = eyePos - positionVec.xyz;
    
    vec3 N = normalize(normalVec);
    vec3 V = normalize(eyeVec);

    vec3 Ks = texture(specularTexture, texture_coord.st).xyz;
    vec3 I = lightValue;

    
    outputColor = vec4(0.0, 0.0, 0.0, 0.7);
    
	vec3 R = 2*dot(N,V)*N - V; // reflection vector
	vec3 A = normalize(cross(vec3(0,1,0),R));   //R as up dir, A is bi-up
	vec3 B = normalize(cross(R,A)); // third axis
	// [A R B] is the new transformation matrix, world coord -> refl coord

	for (int i = 0; i < Number; ++i)
	{
		vec3 spheCoord = buildSpheCoord(hammersley[2*i],hammersley[2*i+1], alpha);
		// spheCoord is local coord light direction
		vec3 OmegaK = normalize(spheCoord.x*A+spheCoord.y*R+spheCoord.z*B);
		vec3 L = OmegaK;	// L is world coord light direction
		int WIDTH = 2400;
		int HEIGHT = 1200;
		vec3 H = normalize(L+V);
		float D = (alpha+2)/(2*M_PI)*pow(max(0.0,dot(N,H)),alpha);
		float level = 0.5*log2(WIDTH*HEIGHT/Number)-0.5*log2(D/4);
		vec4 LightColor = textureLod(domeTexture, getSphereMapCoord(L) ,level);
		LightColor.xyz = Linear2sRGB(LightColor);
        if (dot(L, N) > 0) {
            outputColor.xyz += MonteBRDF(Ks,L,V,N) * LightColor.xyz *dot(L,N)*I / Number;
		}
		
	}
}

