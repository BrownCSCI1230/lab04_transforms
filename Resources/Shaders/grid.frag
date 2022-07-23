#version 330 core

in vec4 worldPos;

out vec4 fragColor;

float interpolate(float A, float B, float mix) {
    return A + mix * (B - A);
}

void main() {
   float mixFactor = distance(vec3(worldPos), vec3(0)) / 2 - 5;
   mixFactor = 1 - clamp(mixFactor,0,1);

   fragColor = vec4(1.0, 1.0, 1.0, 0.2 * mixFactor);

   if (worldPos.y == 0 && worldPos.z == 0) {
       fragColor = vec4(1.0, 0.0, 0.0, 1.0 * mixFactor);
   }
   if (worldPos.x == 0 && worldPos.z == 0) {
       fragColor = vec4(0.0, 1.0, 0.0, 1.0 * mixFactor);
   }
   if (worldPos.x == 0 && worldPos.y == 0) {
       fragColor = vec4(0.0, 0.0, 1.0, 1.0 * mixFactor);
   }
}
