//
// Created by minghaohe on 2023/1/15.
//

#ifndef NIERE_ALLTOBENICE_BASE_GAME_OBJECT_H
#define NIERE_ALLTOBENICE_BASE_GAME_OBJECT_H

#include "atn/base/object.h"

namespace atn {
namespace base {

class GameObject : public Object {
 public:
  GameObject(const std::string& tag);
  explicit GameObject(std::shared_ptr<Object> other);

  virtual ~GameObject() noexcept;

  virtual void RenderInit() override;
  virtual void RenderUninit() override;
  virtual void RenderTick(const render::RenderContext& render_context, const std::vector<render::FrameBuffer>& frame_buffers) override;

  virtual render::ObjectRenderData GetRenderData() = 0;
  virtual void ReleaseRenderData(){};

 protected:
  GLuint vbo_;
  GLuint ebo_;
  std::vector<GLuint> textures_;

  GLsizei gl_element_cout_;
};

}  // namespace base
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_BASE_GAME_OBJECT_H
