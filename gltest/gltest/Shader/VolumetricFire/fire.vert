#version 330 core

in vec3 vertex_coord;
in vec3 vertex_normal;

out vec3 normal;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    gl_Position = vec4(vertex_coord, 1.0f);
    normal = normalize(vertex_normal);
}
