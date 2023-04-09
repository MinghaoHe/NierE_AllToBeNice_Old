//
// Created by minghaohe on 2023/4/9.
//

#include "atn/render/screen_buffer.h"

#include "atn/render/render_context.h"

namespace atn {
namespace render {

ScreenBuffer::ScreenBuffer() : vao_(0), vbo_(0) {}

void ScreenBuffer::Init() {
  screen_shader_.PrebuildFile("../src/atn/game/shader/screen.vs",
                              "../src/atn/game/shader/screen.fs");
  GLfloat screen_vertices[] = {// positions   // texCoords
                               -1.0f, 1.0f, 0.0f, 1.0f,  -1.0f, -1.0f,
                               0.0f,  0.0f, 1.0f, -1.0f, 1.0f,  0.0f,

                               -1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  -1.0f,
                               1.0f,  0.0f, 1.0f, 1.0f,  1.0f,  1.0f};

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(screen_vertices), &screen_vertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                        reinterpret_cast<const void*>(2 * sizeof(GLfloat)));
}

void ScreenBuffer::Uninit() {
  glDeleteVertexArrays(1, &vao_);
  vao_ = 0;
  glDeleteBuffers(1, &vbo_);
  vbo_ = 0;
  screen_shader_.Delete();
}

void ScreenBuffer::Clear() const {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void ScreenBuffer::Draw(std::vector<GLuint> textures) const {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_DEPTH_TEST);

  screen_shader_.Use();
  glBindVertexArray(vao_);
  for (size_t i = 0; i < textures.size(); ++i) {
    screen_shader_.SetInt(TEXTURE_NAME(i), i);
    glActiveTexture(GL_TEXTURE_INDEX(i));
    glBindTexture(GL_TEXTURE_2D, textures[i]);
  }
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

}  // namespace render
}  // namespace atn
