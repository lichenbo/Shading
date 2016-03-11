#version 330 core

in vec3 NormalVec;
in vec3 LightVec;
in vec3 EyeVec;

out vec4 outputColor;

void main(void)
{
	vec3 N = normalize(NormalVec);
	vec3 L = normalize(LightVec);

	vec3 diffuse = vec3(0.5f, 0.2f, 0.3f);
	vec3 Kd = diffuse;
	
	vec3 lightValue = vec3(1.0f, 1.0f, 1.0f);
	vec3 I = lightValue;

	outputColor.xyz = max(0.0, dot(L, N))*Kd*I + 0.5f*Kd; // Phong Lighting Diffuse

}