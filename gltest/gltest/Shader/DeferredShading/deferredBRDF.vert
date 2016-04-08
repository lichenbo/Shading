#version 330 core

in vec4 vertex;
in vec2 texture_coordinate;

out vec2 texture_coord;

void main()
{
    texture_coord = texture_coordinate;
    gl_Position = vertex;
}
