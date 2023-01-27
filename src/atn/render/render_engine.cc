//
// Created by minghaohe on 2023/1/14.
//

#include "render_engine.h"

#include <algorithm>
#include <3rdparty/glm/gtc/matrix_transform.hpp>

#ifndef __APPLE__
#include <3rdparty/glad/glad.h>
#endif

namespace atn {
namespace render {

RenderEngine::RenderEngine(base::WindowContext &window_context,
                           std::set<std::shared_ptr<base::Object>> &objects,
                           std::unordered_map<std::string, std::shared_ptr<base::Object>> &global_objects_cache_map)
        : window_context_(window_context), objects_(objects),
          global_objects_cache_map_(global_objects_cache_map) {
}

RenderEngine::~RenderEngine() noexcept {

}

void RenderEngine::InitGlobalRenderEnvironment() {
  glfwMakeContextCurrent(window_context_.window);
  glfwSetFramebufferSizeCallback(window_context_.window, FrameBufferSizeCallback);
#ifndef __APPLE__
  gladLoadGLLoader(reinterpret_cast<GLADloadproc>(&glfwGetProcAddress));
#endif
}

void RenderEngine::InitRender() {
  text_render_ = std::make_shared<TextRender>();
  text_render_->InitText();
  render_context_.view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  render_context_.projection = glm::perspective(glm::radians(45.0f),
                                                static_cast<float>(window_context_.width) /
                                                static_cast<float>(window_context_.hight), 0.1f,
                                                100.0f);
  glEnable(GL_DEPTH_TEST);
  std::for_each(global_objects_cache_map_.begin(), global_objects_cache_map_.end(),
                [this](auto object) { object.second->RenderInit(); });
}

void RenderEngine::UninitRender() {
  text_render_->UninitText();

  std::for_each(global_objects_cache_map_.begin(), global_objects_cache_map_.end(),
                [this](auto object) { object.second->RenderUninit(); });
  glfwMakeContextCurrent(nullptr);
}

void RenderEngine::Tick() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  std::for_each(objects_.begin(), objects_.end(),
                [this](std::shared_ptr<base::Object> object) {
                  object->RenderTick(render_context_);
                });

  glfwSwapBuffers(window_context_.window);
}

RenderContext &RenderEngine::GetRenderContext() {
  return render_context_;
}

void RenderEngine::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

std::shared_ptr<TextRender> RenderEngine::GetTextRender() {
  return text_render_;
}

}
}