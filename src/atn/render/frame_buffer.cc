//
// Created by minghaohe on 2023/4/9.
//

#include "atn/render/frame_buffer.h"

namespace atn {
namespace render {

FrameBuffer::FrameBuffer() : fbo_(0), rbo_(0) {}

FrameBuffer::~FrameBuffer() {}

void FrameBuffer::Init(int width, int height, size_t color_attach_count) {
  glGenFramebuffers(1, &fbo_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

  textures_.resize(color_attach_count);
  glGenTextures(color_attach_count, textures_.data());

  for (size_t i = 0; i < color_attach_count; ++i) {
    glBindTexture(GL_TEXTURE_2D, textures_[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                           GL_TEXTURE_2D, textures_[i], 0);
  }

  glGenRenderbuffers(1, &rbo_);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rbo_);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Uninit() {
  glDeleteFramebuffers(1, &fbo_);
  fbo_ = 0;

  glDeleteTextures(textures_.size(), textures_.data());
  textures_.clear();

  glDeleteRenderbuffers(1, &rbo_);
  rbo_ = 0;
}

void FrameBuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, fbo_); }

void FrameBuffer::Unbind() const { glBindRenderbuffer(GL_FRAMEBUFFER, 0); }

void FrameBuffer::Clear() const {
  Bind();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Unbind();
}

void FrameBuffer::BindTexture(size_t index) const {
  glBindTexture(GL_TEXTURE_2D, textures_[index]);
}

void FrameBuffer::UnbindTexture() const { glBindTexture(GL_TEXTURE_2D, 0); }

GLuint FrameBuffer::Texture() const { return textures_[0]; }

}  // namespace render
}  // namespace atn
