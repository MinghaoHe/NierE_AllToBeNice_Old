//
// Created by minghaohe on 2023/1/16.
//

#ifndef NIERE_ALLTOBENICE_RENDER_SHADER_H
#define NIERE_ALLTOBENICE_RENDER_SHADER_H

#include <filesystem>
#include <opengl/gl3.h>

#include <3rdparty/glm/glm.hpp>

namespace atn {
namespace render {

class Shader {
 public:
  void PrebuildFile(const std::filesystem::path &vertex_shader_path, const std::filesystem::path &fragment_shader_path);

  void Prebuild(const std::string_view vertex_shader_source, const std::string_view fragment_shader_source);

  void Delete();

  void CheckCompileError(GLuint shader);

  void CheckLinkError(GLuint program);

  void Use() const;

  void SetInt(const std::string_view name, int i) const;

  void SetVec3(const std::string_view &name, const glm::vec3 &value) const;

  void SetVec3(const std::string_view &name, float x, float y, float z) const;

  void SetMatrix4(const std::string_view name, const glm::mat4 &mat) const;

 private:
  GLuint shader_program_id_;
};

}
}


#endif // NIERE_ALLTOBENICE_RENDER_SHADER_H
