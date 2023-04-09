//
// Created by minghaohe on 2023/1/14.
//

#include "render_engine.h"

#include <algorithm>

#include <3rdparty/glad/glad.h>
#include <3rdparty/glm/gtc/matrix_transform.hpp>


#include "atn/base/game_engine.h"

namespace {

void FrameBufferSizeCallbackWrap(GLFWwindow *window, int width, int height) {
  std::invoke(&atn::render::RenderEngine::FrameBufferSizeCallback,
              atn::base::GameEngine::Instance().GetRender().get(), window,
              width, height);
}

}  // namespace

namespace atn {
namespace render {

RenderEngine::RenderEngine(
    base::WindowContext &window_context,
    std::unordered_set<std::shared_ptr<base::Object>> &objects,
    std::unordered_map<std::string, std::shared_ptr<base::Object>>
        &global_objects_cache_map)
    : window_context_(window_context),
      objects_(objects),
      global_objects_cache_map_(global_objects_cache_map) {}

RenderEngine::~RenderEngine() noexcept {}

void RenderEngine::InitGlobalRenderEnvironment() {
  glfwMakeContextCurrent(window_context_.window);
  glfwSetFramebufferSizeCallback(window_context_.window,
                                 FrameBufferSizeCallbackWrap);
  gladLoadGLLoader(reinterpret_cast<GLADloadproc>(&glfwGetProcAddress));
}

void RenderEngine::InitRender() {
  text_render_ = std::make_shared<TextRender>();
  text_render_->InitText();
  screen_buffer_.Init();
  InitFrameBuffers();
  render_context_.view =
      glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  render_context_.projection =
      glm::perspective(glm::radians(45.0f),
                       static_cast<float>(window_context_.width) /
                           static_cast<float>(window_context_.height),
                       0.1f, 100.0f);
  glEnable(GL_MULTISAMPLE);
  std::for_each(global_objects_cache_map_.begin(),
                global_objects_cache_map_.end(),
                [this](auto object) { object.second->RenderInit(); });
}

void RenderEngine::UninitRender() {
  text_render_->UninitText();
  screen_buffer_.Uninit();
  std::for_each(global_objects_cache_map_.begin(),
                global_objects_cache_map_.end(),
                [this](auto object) { object.second->RenderUninit(); });
  UninitFrameBuffers();
  glfwMakeContextCurrent(nullptr);
}

void RenderEngine::Tick() {
  ClearFrameBuffers();
  std::for_each(objects_.begin(), objects_.end(),
                [this](std::shared_ptr<base::Object> object) {
                  object->RenderTick(render_context_, frame_buffers_);
                });

  screen_buffer_.Clear();
  screen_buffer_.Draw(
      {frame_buffers_[static_cast<size_t>(FrameIndex::kMain)].Texture(),
       frame_buffers_[static_cast<size_t>(FrameIndex::kBloom)].Texture()});

  glfwSwapBuffers(window_context_.window);
}

RenderContext &RenderEngine::GetRenderContext() { return render_context_; }

void RenderEngine::FrameBufferSizeCallback(GLFWwindow *window, int width,
                                           int height) {
  window_context_.width = width;
  window_context_.height = height;
  render_context_.projection =
      glm::perspective(glm::radians(45.0f),
                       static_cast<float>(window_context_.width) /
                           static_cast<float>(window_context_.height),
                       0.1f, 100.0f);
  glViewport(0, 0, width, height);
}

std::shared_ptr<TextRender> RenderEngine::GetTextRender() {
  return text_render_;
}

void RenderEngine::InitFrameBuffers() {
  frame_buffers_.resize(static_cast<size_t>(FrameIndex::kMax));
  frame_buffers_[static_cast<size_t>(FrameIndex::kMain)].Init(
      window_context_.width, window_context_.height, 1);
  frame_buffers_[static_cast<size_t>(FrameIndex::kBloom)].Init(
      window_context_.width, window_context_.height, 2);
}

void RenderEngine::UninitFrameBuffers() {
  std::for_each(frame_buffers_.begin(), frame_buffers_.end(),
                [](auto &&frame_buffer) { frame_buffer.Uninit(); });
  frame_buffers_.clear();
}

void RenderEngine::ClearFrameBuffers() {
  std::for_each(frame_buffers_.begin(), frame_buffers_.end(),
                [](auto &&frame_buffer) { frame_buffer.Clear(); });
}

}  // namespace render
}  // namespace atn