#version 330 core

in vec3 vertex_coord;
in vec3 normal_coord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ViewInverseMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;

uniform vec3 EyePos;

out vec3 NormalVec;
out vec3 LightVec;
out vec3 EyeVec;

void main(void)
{
	vec4 homo_vertex;
	homo_vertex.xyz = vertex_coord;
	homo_vertex.w = 1.0;

	vec3 LightPos = vec3(10.0f, 10.0f, -10.0f);
	//vec3 worldVertex = vec3(ModelMatrix * homo_vertex);

	vec3 worldVertex = vec3(0.0f, 0.0f, 0.0f);

	LightVec = LightPos - worldVertex; 

	LightVec = vec3(0.0f, 0.0f, 0.0f);
	EyeVec = (ViewInverseMatrix*vec4(0,0,0,1)).xyz - worldVertex;
	NormalVec = normalize(mat3(NormalMatrix)*normal_coord);    


	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * homo_vertex;

}
