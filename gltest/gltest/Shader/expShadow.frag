#version 330 core

in vec4 position;
uniform vec3 blurFactor;
layout(location = 0) out vec4 shadowMap;

void main()
{
    float c = 10.0;
    float depth = exp(blurFactor.x * position.w);

    shadowMap = vec4(depth,depth,depth,depth);
}
