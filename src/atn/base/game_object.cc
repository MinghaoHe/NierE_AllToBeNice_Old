//
// Created by minghaohe on 2023/1/15.
//

#include "game_object.h"

namespace atn {
namespace base {

GameObject::GameObject(const std::string& tag)
    : base::Object(tag), vbo_(0), ebo_(0), gl_element_cout_(0) {}

GameObject::GameObject(std::shared_ptr<Object> other) : base::Object(other) {
  std::shared_ptr<GameObject> dother =
      std::dynamic_pointer_cast<GameObject>(other);
  gl_element_cout_ = dother->gl_element_cout_;
  vbo_ = dother->vbo_;
  ebo_ = dother->ebo_;
  textures_ = dother->textures_;
}

GameObject::~GameObject() noexcept {}

void GameObject::RenderInit() {
  Object::RenderInit();
  render::ObjectRenderData render_data = GetRenderData();
  std::for_each(
      render_data.textures_data.begin(), render_data.textures_data.end(),
      [this](render::TextureData texture_data) {
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, texture_data.format, texture_data.width,
                     texture_data.height, 0, texture_data.format,
                     GL_UNSIGNED_BYTE, texture_data.pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        textures_.push_back(texture);
      });

  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);
  if (!render_data.vertices.empty()) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 render_data.vertices.size() * sizeof(render_data.vertices[0]),
                 &render_data.vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
  }

  if (!render_data.indices.empty()) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 render_data.indices.size() * sizeof(render_data.indices[0]),
                 &render_data.indices[0], GL_STATIC_DRAW);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  ReleaseRenderData();
}

void GameObject::RenderUninit() {
  Object::RenderUninit();
  glDeleteBuffers(1, &vbo_);
  glDeleteBuffers(1, &ebo_);
  if (!textures_.empty()) glDeleteTextures(textures_.size(), &textures_[0]);
}

void GameObject::RenderTick(
    const render::RenderContext& render_context,
    const std::vector<render::FrameBuffer>& frame_buffers) {
  frame_buffers[static_cast<size_t>(render::FrameIndex::kMain)].Bind();

  glEnable(GL_DEPTH_TEST);

  glBindVertexArray(vao_);
  shader_.Use();
  for (size_t i = 0; i < textures_.size(); ++i) {
    shader_.SetInt(render::TEXTURE_NAME(i), i);
    glActiveTexture(render::GL_TEXTURE_INDEX(i));
    glBindTexture(GL_TEXTURE_2D, textures_[i]);
  }
  shader_.SetMatrix4("projection", render_context.projection);
  shader_.SetMatrix4("view", render_context.view);
  SetShaderUniform();
  glDrawElements(GL_TRIANGLES, gl_element_cout_, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  frame_buffers[static_cast<size_t>(render::FrameIndex::kMain)].Unbind();
}

}  // namespace base
}  // namespace atn