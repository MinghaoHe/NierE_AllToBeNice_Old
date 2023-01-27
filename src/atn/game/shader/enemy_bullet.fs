#version 330 core
out vec4 fragment_color;

uniform vec3 color;

void main() {
    fragment_color = vec4(color, 1.0f);
}