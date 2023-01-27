#version 330 core
layout (location = 0) in vec4 vertex;
out vec2 tex_coords;

uniform mat4 model_adjust_matrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * model_adjust_matrix * vec4(vertex.xy, 0.0f, 1.0f);
    tex_coords = vertex.zw;
}