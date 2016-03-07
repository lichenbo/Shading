#version 330 core

layout(location = 0) in vec3 vertex_coord;

void main(void)
{

    gl_Position.xyz = vertex_coord;
    gl_Position.w = 1.0;

    
    vec4 vertices[] = vec4[]
    (
     vec4(0.25, -0.25, 0.5, 1.0),
     vec4(-0.25, -0.25, 0.5, 1.0),
     gl_Position
     );
    
    gl_Position = vertices[gl_VertexID];
    
}
