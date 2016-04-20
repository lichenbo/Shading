#version 330 core


layout(points) in;
layout(triangle_strip, max_vertices = 4) out;
in vec3 normal[];
out vec2 texture_coord;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    vec3 N = normalize(normal[0]);
    vec3 B = normalize(cross(vec3(0,1,0),N));
    vec3 A = normalize(cross(N, B));
    
    mat4 VP = ProjectionMatrix*ViewMatrix;
    
    float size = 0.1;
    gl_Position.xyz = gl_in[0].gl_Position.xyz + (-size*B+0.0*N-size*A);
    gl_Position.w = 1.0;
    gl_Position = VP*gl_Position;
    vec3 cylinder_coord = vec3(-1.0, gl_in[0].y, -1.0);
    texture_coord = vec2(sqrt(cylinder_coord.x * cylinder_coord.x + cylinder_coord.z * cylinder_coord.z),cylinder_coord.y);
	EmitVertex();
    gl_Position.xyz = gl_in[0].gl_Position.xyz + (-size*B+0.0*N+size*A);
    gl_Position.w = 1.0;
    gl_Position = VP*gl_Position;
    vec3 cylinder_coord = vec3(-1.0, gl_in[0].y, 1.0);
    texture_coord = vec2(sqrt(cylinder_coord.x * cylinder_coord.x + cylinder_coord.z * cylinder_coord.z),cylinder_coord.y);
    EmitVertex();
    gl_Position.xyz = gl_in[0].gl_Position.xyz + (size*B+ 0.0*N -size*A);
    gl_Position.w = 1.0;

    gl_Position = VP*gl_Position;
    vec3 cylinder_coord = vec3(1.0, gl_in[0].y, -1.0);
    texture_coord = vec2(sqrt(cylinder_coord.x * cylinder_coord.x + cylinder_coord.z * cylinder_coord.z),cylinder_coord.y);
    EmitVertex();
    gl_Position.xyz = gl_in[0].gl_Position.xyz + (size*B+ 0.0*N +size*A);
    gl_Position.w = 1.0;
    gl_Position = VP*gl_Position;
    vec3 cylinder_coord = vec3(1.0, gl_in[0].y, 1.0);
    texture_coord = vec2(sqrt(cylinder_coord.x * cylinder_coord.x + cylinder_coord.z * cylinder_coord.z),cylinder_coord.y);
    EmitVertex();
	EndPrimitive();
}
