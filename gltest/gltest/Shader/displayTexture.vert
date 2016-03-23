#version 330 core

in vec3 vertex_coord;
in vec2 texture_coord;

out vec2 texCoord;

void main(void)
{
    vec4 homo_vertex;
    homo_vertex.xyz = vertex_coord;
    homo_vertex.w = 1.0;
    
    gl_Position = homo_vertex;
    
    texCoord = texture_coord;
}
