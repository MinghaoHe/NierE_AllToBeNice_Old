#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture_coords_vs;

out vec2 texture_coords_fs;

void main() {
    texture_coords_fs = texture_coords_vs;
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
}