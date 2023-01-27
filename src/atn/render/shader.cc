//
// Created by minghaohe on 2023/1/16.
//

#include "shader.h"

#include <fstream>
#include <sstream>
#include <opengl/gl3.h>

namespace atn {
namespace render {

void
Shader::PrebuildFile(const std::filesystem::path &vertex_shader_path,
                     const std::filesystem::path &fragment_shader_path) {
  std::ifstream vertex_shader_file(vertex_shader_path);
  std::stringstream vertex_shader_stream;
  vertex_shader_stream << vertex_shader_file.rdbuf();
  std::string vertex_shader_source = vertex_shader_stream.str();

  std::ifstream fragment_shader_file(fragment_shader_path);
  std::stringstream fragment_shader_stream;
  fragment_shader_stream << fragment_shader_file.rdbuf();
  std::string fragment_shader_source = fragment_shader_stream.str();

  Prebuild(vertex_shader_source, fragment_shader_source);
}

void Shader::Prebuild(const std::string_view vertex_shader_source, const std::string_view fragment_shader_source) {
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar *vertex_shader_source_list[]{vertex_shader_source.data()};
  glShaderSource(vertex_shader, 1, vertex_shader_source_list, nullptr);
  glCompileShader(vertex_shader);
  CheckCompileError(vertex_shader);

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar *fragment_shader_source_list[]{fragment_shader_source.data()};
  glShaderSource(fragment_shader, 1, fragment_shader_source_list, nullptr);
  glCompileShader(fragment_shader);
  CheckCompileError(fragment_shader);

  shader_program_id_ = glCreateProgram();
  glAttachShader(shader_program_id_, vertex_shader);
  glAttachShader(shader_program_id_, fragment_shader);
  glLinkProgram(shader_program_id_);
  CheckLinkError(shader_program_id_);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void Shader::Delete() { glDeleteProgram(shader_program_id_); }

void Shader::Use() const {
  glUseProgram(shader_program_id_);
}

void Shader::SetInt(const std::string_view name, int i) const {
  glUniform1i(glGetUniformLocation(shader_program_id_, name.data()), i);
}

void Shader::SetVec3(const std::string_view &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(shader_program_id_, name.data()), 1, &value[0]);
}

void Shader::SetVec3(const std::string_view &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(shader_program_id_, name.data()), x, y, z);
}

void Shader::SetMatrix4(const std::string_view name, const glm::mat4 &matrix) const {
  glUniformMatrix4fv(glGetUniformLocation(shader_program_id_, name.data()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::CheckCompileError(GLuint shader) {
  GLint compile_result = 0;
  GLchar error_message[1024]{};
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
  if (!compile_result) {
    glGetShaderInfoLog(shader, sizeof(error_message), nullptr, error_message);
  }
}

void Shader::CheckLinkError(GLuint program) {
  GLint link_result = 0;
  GLchar error_message[1024]{};
  glGetProgramiv(program, GL_LINK_STATUS, &link_result);
  if (!link_result) {
    glGetProgramInfoLog(program, sizeof(error_message), nullptr, error_message);
  }
}

}
}