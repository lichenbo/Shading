#version 330 core

#define EXP 2.7182818284590452353602874713527

in vec4 position;
uniform vec3 blurFactor;
layout(location = 0) out vec4 shadowMap;

void main()
{
    float c = 10.0;
    float depth = pow(EXP, blurFactor.x * position.w);

    shadowMap = vec4(depth,depth,depth,depth);
}
