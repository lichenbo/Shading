#version 330 core
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

in vec3 vertex;

out vec4 position;

void main()
{      
	gl_Position = ProjectionMatrix *ViewMatrix*ModelMatrix*vec4(vertex,1);
	position = gl_Position;
}
