//
// Created by minghaohe on 2023/4/9.
//

#ifndef NIERE_ALLTOBENICE_RENDER_FRAME_BUFFER_H
#define NIERE_ALLTOBENICE_RENDER_FRAME_BUFFER_H

#include <vector>
#include <3rdparty/glad/glad.h>

namespace atn {
namespace render {

class FrameBuffer {
 public:
  FrameBuffer();
  ~FrameBuffer();

  void Init(int width, int height, size_t color_attach_count);
  void Uninit();

  void Bind() const;
  void Unbind() const;

  void Clear() const;

  void BindTexture(size_t index) const;
  void UnbindTexture() const;

  GLuint Texture() const;

 private:
  GLuint fbo_;
  GLuint rbo_;
  std::vector<GLuint> textures_;
};

}  // namespace render
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_RENDER_FRAME_BUFFER_H
