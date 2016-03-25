#version 330 core

in vec3 vertex_coord;

void main(void)
{
	gl_Position.xyz = vertex_coord;
}
