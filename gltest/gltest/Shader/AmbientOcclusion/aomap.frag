#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform sampler2D normalTexture;
uniform sampler2D positionTexture;
uniform sampler2D depthTexture;

uniform int windowHeight;
uniform int windowWidth;

in vec2 texture_coord;
out vec4 outputColor;


float ambientFactor(float range, float numSamplePoints)
{
	vec2 frag_window_coord = gl_FragCoord.xy; //Relative to window coordinate
	//vec2 frag_coord = vec2(float(frag_window_coord.x)/windowWidth, float(frag_window_coord.y)/windowHeight); // Clamp to 0..1
	vec2 frag_coord = texture_coord;
	vec3 position = texture(positionTexture, frag_coord.st).xyz;
	vec3 normal = texture(normalTexture, frag_coord.st).xyz;
	float depth = texture(depthTexture, frag_coord.st).x;

	float phi = (30*(int(frag_window_coord.x)^int(frag_window_coord.y)))+10*frag_window_coord.x*frag_window_coord.y;
	float S = 0.0;
	float c = 0.1*range;
	float delta = 0.001;
	float s = 0.1; // adjustable scale;
	float k = 10; // adjustable contrast;
	for (int i = 0; i < numSamplePoints; ++i)
	{
		float alpha = (i+0.5)/numSamplePoints;
		float h = alpha*range/depth;
		float theta = 2*M_PI*alpha*(7*numSamplePoints/9)+phi;
		vec3 Pi = texture(positionTexture, frag_coord+h*vec2(cos(theta),sin(theta))).xyz;
		
		vec3 OmegaI = (Pi - position).xyz;
		if (range > length(OmegaI))
		{
			S += max(0.0, dot(normal,OmegaI)-delta*depth)/max(c*c, dot(OmegaI,OmegaI));
		}
	}
	S *= 2*M_PI*c/numSamplePoints;
	return (1-s*S > 0) ? pow(1-s*S,k):0;

}

void main(void)
{
    outputColor.xyz = vec3(ambientFactor(0.5,20));
}