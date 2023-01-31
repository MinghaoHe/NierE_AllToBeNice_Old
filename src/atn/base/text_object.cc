//
// Created by minghaohe on 2023/1/19.
//

#include "text_object.h"

#include <3rdparty/glm/gtc/matrix_transform.hpp>

#include "atn/base/game_engine.h"
#include "atn/render/text_render.h"

namespace {
atn::physics::RectangleBox GetTextBoundingVertices(
    const glm::mat4 &model_adjust_matrix, float width, float height) {
  atn::physics::RectangleBox rectangle_box;
  rectangle_box.vertices[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  rectangle_box.vertices[1] = model_adjust_matrix * glm::vec4(width, 0.0f, 0.0f, 1.0f);
  rectangle_box.vertices[2] = model_adjust_matrix * glm::vec4(0.0f, height, 0.0f, 1.0f);
  rectangle_box.vertices[3] = model_adjust_matrix * glm::vec4(width, height, 0.0f, 1.0f);

  return rectangle_box;
}
}  // namespace

namespace atn {
namespace base {

TextObject::TextObject(const std::string &tag)
    : base::Object(tag),
      text_render_(base::GameEngine::Instance().GetRender()->GetTextRender()),
      need_generate_text_(false),
      scale_(1.0f),
      width_(0.0f),
      height_(0.0f) {}

TextObject::TextObject(std::shared_ptr<Object> other)
    : base::Object(other),
      text_render_(base::GameEngine::Instance().GetRender()->GetTextRender()),
      need_generate_text_(false),
      scale_(1.0f),
      width_(0.0f),
      height_(0.0f) {
  std::shared_ptr<TextObject> dother =
      std::dynamic_pointer_cast<TextObject>(other);
  text_ = dother->text_;
}

TextObject::~TextObject() noexcept { DestoryTextRenderObject(); }

void TextObject::RenderTick(const render::RenderContext &render_context) {
  if (need_generate_text_) {
    GenerateTextRenderObject();
    need_generate_text_ = false;
  }
  shader_.Use();
  shader_.SetMatrix4("model_adjust_matrix", model_adjust_matrix_);
  shader_.SetMatrix4("projection", render_context.projection);
  shader_.SetMatrix4("view", render_context.view);
  SetShaderUniform();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vao_);
  std::for_each(text_render_objects_.begin(), text_render_objects_.end(),
                [](const TextRenderObject &text_render_object) {
                  glBindTexture(GL_TEXTURE_2D, text_render_object.texture);
                  glBindBuffer(GL_ARRAY_BUFFER, text_render_object.vbo);
                  glEnableVertexAttribArray(0);
                  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
                                        4 * sizeof(float), 0);
                  glDrawArrays(GL_TRIANGLES, 0, 6);
                });
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_BLEND);
}

void TextObject::SetModelMatrix(const glm::mat4 &model) {
  Object::SetModelMatrix(model);
}

glm::mat4 TextObject::GetModelMatrix() const {
  return Object::GetModelMatrix();
}

void TextObject::SetText(const std::string &text, float scale) {
  if (text_.compare(text) != 0) {
    text_ = text;
    scale_ = scale;
    need_generate_text_ = true;
  }
}

void TextObject::GenerateTextRenderObject() {
  size_t i = 0 /* vbo index */, j = 0 /* text index */;

  width_ = 0.0f;
  height_ = 0.0f;

  float x = 0.0f;
  for (; i < text_render_objects_.size() && j < text_.length(); ++i, ++j) {
    render::Character char_texture =
        text_render_->CharacterTextureObject(text_[j]);
    float xpos = x + char_texture.bearing.x * scale_;

    float w = char_texture.size.x * scale_;
    width_ += w;
    float h = char_texture.size.y * scale_;
    height_ = std::max(height_, h);

    float vertices[6][4] = {
        {xpos, 0.0f + h, 0.0f, 0.0f}, {xpos, 0.0f, 0.0f, 1.0f},
        {xpos + w, 0.0f, 1.0f, 1.0f}, {xpos, 0.0f + h, 0.0f, 0.0f},
        {xpos + w, 0.0f, 1.0f, 1.0f}, {xpos + w, 0.0f + h, 1.0f, 0.0f}};
    text_render_objects_[i].texture = char_texture.texture;
    glBindBuffer(GL_ARRAY_BUFFER, text_render_objects_[i].vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    x += (char_texture.advance >> 6) * scale_;
  }
  if (text_render_objects_.size() > text_.length()) {
    int new_size = i;
    for (; i < text_render_objects_.size(); ++i) {
      glDeleteBuffers(1, &text_render_objects_[i].vbo);
    }
    text_render_objects_.resize(new_size);
  } else if (text_render_objects_.size() < text_.length()) {
    for (; j < text_.length(); ++j) {
      render::Character char_texture =
          text_render_->CharacterTextureObject(text_[j]);
      float xpos = x + char_texture.bearing.x * scale_;
      float w = char_texture.size.x * scale_;
      width_ += w;
      float h = char_texture.size.y * scale_;
      height_ = std::max(height_, h);
      float vertices[6][4] = {
          {xpos, 0.0f + h, 0.0f, 0.0f}, {xpos, 0.0f, 0.0f, 1.0f},
          {xpos + w, 0.0f, 1.0f, 1.0f}, {xpos, 0.0f + h, 0.0f, 0.0f},
          {xpos + w, 0.0f, 1.0f, 1.0f}, {xpos + w, 0.0f + h, 1.0f, 0.0f}};
      TextRenderObject text_render_object;
      text_render_object.texture = char_texture.texture;
      glGenBuffers(1, &text_render_object.vbo);
      glBindBuffer(GL_ARRAY_BUFFER, text_render_object.vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                   GL_DYNAMIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      text_render_objects_.push_back(text_render_object);
      x += (char_texture.advance >> 6) * scale_;
    }
  }
  model_adjust_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(-width_ / 2.0f, -height_ / 2.0f, 0.0f));
  SetBoundingBox(
      physics::BBoxType::rectangle, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
      GetTextBoundingVertices(model_adjust_matrix_, width_, height_));
}

void TextObject::DestoryTextRenderObject() {
  std::for_each(text_render_objects_.begin(), text_render_objects_.end(),
                [](const TextRenderObject &text_render_object) {
                  glDeleteBuffers(1, &text_render_object.vbo);
                });
}

}  // namespace base
}  // namespace atn