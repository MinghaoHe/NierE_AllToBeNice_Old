#version 330 core
out vec4 fragment_color;

in vec2 texture_coords_fs;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    vec3 color0 = texture(texture0, texture_coords_fs).rgb;
    fragment_color = vec4(color0, 1.0);
}