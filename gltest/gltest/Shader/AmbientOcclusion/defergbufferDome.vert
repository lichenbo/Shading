#version 330 core

in vec3 vertex_coord;
in vec3 normal_coord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;

out vec3 worldSpacePosition;
out vec3 worldSpaceNormal;
out float depth;

void main(void)
{
	vec4 homo_vertex;
	homo_vertex.xyz = vertex_coord;
	homo_vertex.w = 1.0;

	worldSpacePosition = vec3(ModelMatrix * homo_vertex);

	worldSpaceNormal = normalize(mat3(NormalMatrix)*normal_coord);    

    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * homo_vertex;
	depth = gl_Position.z;
}
