#version 330 core

in vec4 position;
layout(location = 0) out vec4 shadowMap;

void main()
{
   float w = position.w/100;
   shadowMap = vec4(w,w,w,w);
}
