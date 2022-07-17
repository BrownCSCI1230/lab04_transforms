#version 330 core

out vec4 fragColor;

uniform vec3 inColor;

void main() {
   fragColor = vec4(inColor, 1.0);
}
