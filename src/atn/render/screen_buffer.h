//
// Created by minghaohe on 2023/4/9.
//

#ifndef NIERE_ALLTOBENICE_RENDER_SCREEN_BUFFER_H
#define NIERE_ALLTOBENICE_RENDER_SCREEN_BUFFER_H

#include "atn/common/utility.h"
#include "atn/render/shader.h"

namespace atn {
namespace render {

class ScreenBuffer {
 public:
  ScreenBuffer();

  void Init();
  void Uninit();

  void Clear() const;

  void Draw(std::vector<GLuint> textures) const;

 private:
  GLuint vao_;
  GLuint vbo_;
  Shader screen_shader_;
  DISALLOW_COPY_AND_ASSIGN(ScreenBuffer);
};

}  // namespace render
}  // namespace atn
#endif  // NIERE_ALLTOBENICE_RENDER_SCREEN_BUFFER_H
