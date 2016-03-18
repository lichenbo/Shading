#version 330 core

#define M_PI 3.1415926535897932384626433832795

in vec3 NormalVec;
in vec3 LightVec;
in vec3 EyeVec;
in vec3 TanVec;

out vec4 outputColor;


void main(void)
{
	vec3 N = normalize(NormalVec);
	vec3 L = normalize(LightVec);
    vec3 V = normalize(EyeVec);
    vec3 H = normalize(L+V);
    //vec3 T = normalize(TanVec);

	vec3 diffuse = vec3(0.5, 0.2, 0.3);
	vec3 Kd = diffuse;
	
	vec3 lightValue = vec3(1.0, 1.0, 1.0);
	vec3 I = lightValue;
    
    vec3 lightAmbient = vec3(0.2, 0.2, 0.2);
    
    vec3 specular = vec3(1.0, 1.0, 1.0);
    vec3 Ks = specular;
    
    float g = 0.5;
    float alpha = pow(8192, g);
    vec3 F = Ks + (1 - Ks) * pow((1-dot(L, H)), 5);
    float D = ((alpha + 2)/(2 * M_PI))*pow(max(0.0, dot(N,H)), alpha);
    float G = 1.0 / (dot(L, H) * dot(L,H));
    I = I * M_PI;
    
    outputColor.xyz = 0.2*lightAmbient*Kd;
    if (dot(L,N) > 0)
    {
        outputColor.xyz += (Kd/M_PI+0.25*F*D*G)*dot(L,N)*I;
    }

	outputColor.xyz = max(0.0, dot(L, N))*Kd*I + 0.5*Kd; // Phong Lighting Diffuse

}