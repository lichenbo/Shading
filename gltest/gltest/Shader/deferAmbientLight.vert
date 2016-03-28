#version 330 core

in vec3 vertex_coord;
in vec2 texture_coordinate;

out vec2 texture_coord;

void main(void)
{
    texture_coord = texture_coordinate;
	gl_Position.xyz = vertex_coord;
}
