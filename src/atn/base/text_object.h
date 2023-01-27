//
// Created by minghaohe on 2023/1/19.
//

#ifndef NIERE_ALLTOBENICE_BASE_TEXT_OBJECT_H
#define NIERE_ALLTOBENICE_BASE_TEXT_OBJECT_H

#include "atn/base/object.h"
#include "atn/render/text_render.h"

namespace atn {
namespace base {

class TextObject : public Object {
 public:
  TextObject(const std::string& tag);
  explicit TextObject(std::shared_ptr<Object> other);

  virtual ~TextObject() noexcept;

  virtual void RenderTick(const render::RenderContext &render_context) override;

  void SetModelMatrix(const glm::mat4& model);
  glm::mat4 GetModelMatrix() const;

  void SetText(const std::string& text, float scale);

 private:
  void GenerateTextRenderObject();
  void DestoryTextRenderObject();

 protected:
  std::string text_;
  glm::vec3 color_;
  float scale_;
  float width_;
  float height_;

 private:
  bool need_generate_text_;
  glm::mat4 model_adjust_matrix_;

  struct TextRenderObject {
    GLuint vbo;
    GLuint texture;
  };
  std::vector<TextRenderObject> text_render_objects_;
  std::shared_ptr<render::TextRender> text_render_;
};

}
}


#endif // NIERE_ALLTOBENICE_BASE_TEXT_OBJECT_H
