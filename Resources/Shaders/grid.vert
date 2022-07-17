#version 330 core

layout (location = 0) in vec3 position;

out vec4 worldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main() {
   worldPos = model * vec4(position,1);
   gl_Position = proj * view * model * vec4(position, 1.0);
}
