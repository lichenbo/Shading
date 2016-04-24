#version 330 core

in vec4 position;
uniform vec3 blurFactor;
layout(location = 0) out vec4 shadowMap;
//layout(location = 1) out vec4 shadowDebugMap;
float scaleToInterval(float value, float minDepth, float maxDepth)
{
	return (value - minDepth) / (maxDepth - minDepth);
}
void main()
{
    float minDepth = 0.1;	float maxDepth = 20;	float scaledDepth = scaleToInterval(position.w, minDepth, maxDepth);    float depth = exp(blurFactor.x * scaledDepth);

    shadowMap = vec4(depth);
	//shadowDebugMap = vec4(scaledDepth);
}
