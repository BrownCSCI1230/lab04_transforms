#version 330 core

in vec4 worldPos;

out vec4 fragColor;

float interpolate(float A, float B, float mix) {
    return A + mix * (B - A);
}

void main() {
   float mixFactor = distance(vec3(worldPos), vec3(0)) / 2 - 5;
   mixFactor = clamp(mixFactor,0,1);
   fragColor = vec4(vec3(interpolate(0.4,0.2,mixFactor)),
                    1.0);
}
