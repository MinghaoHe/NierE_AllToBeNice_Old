//
// Created by minghaohe on 2023/1/14.
//

#include "logic_engine.h"

#include <functional>

#include "atn/base/game_engine.h"

namespace {

inline void CursorPosCallbackWrap(GLFWwindow *window, double xpos,
                                  double ypos) {
  UNUSED(window);
  std::invoke(&atn::logic::LogicEngine::CursorPosCallback,
              atn::base::GameEngine::Instance().GetLogic().get(),
              static_cast<float>(xpos), static_cast<float>(ypos));
}

inline void KeyCallbackWrap(GLFWwindow *window, int code_point, int scancode,
                            int action, int mods) {
  UNUSED(window);
  UNUSED(scancode);
  UNUSED(mods);
  std::invoke(&atn::logic::LogicEngine::CharInputCallback,
              atn::base::GameEngine::Instance().GetLogic().get(),
              static_cast<char>(code_point), action);
}

}  // namespace

namespace atn {
namespace logic {

LogicEngine::LogicEngine(
    base::WindowContext &window_context,
    std::unordered_set<std::shared_ptr<base::Object>> &objects,
    std::unordered_map<std::string, std::shared_ptr<base::Object>>
        &global_objects_cache_map)
    : window_context_(window_context),
      objects_(objects),
      global_objects_cache_map_(global_objects_cache_map) {}

LogicEngine::~LogicEngine() noexcept {}

void LogicEngine::InitLogic() {
  glfwSetCursorPosCallback(window_context_.window, CursorPosCallbackWrap);
  glfwSetKeyCallback(window_context_.window, KeyCallbackWrap);
  // glfwSetInputMode(window_context_.window, GLFW_CURSOR,
  // GLFW_CURSOR_DISABLED);

  std::for_each(global_objects_cache_map_.begin(),
                global_objects_cache_map_.end(),
                [this](auto object) { object.second->LogicInit(); });
}

void LogicEngine::UninitLogic() {
  std::for_each(global_objects_cache_map_.begin(),
                global_objects_cache_map_.end(),
                [this](auto object) { object.second->LogicUninit(); });

  glfwSetCursorPosCallback(window_context_.window, nullptr);
  glfwSetCharCallback(window_context_.window, nullptr);
}

void LogicEngine::Tick() {
  std::for_each(objects_.begin(), objects_.end(),
                [this](std::shared_ptr<base::Object> object) {
                  object->LogicTick(logic_context_);
                });
  glfwPollEvents();
}

void LogicEngine::CursorPosCallback(float xpos, float ypos) {
  logic_context_.event.cursor_event.xpos =
      (xpos - static_cast<float>(window_context_.width) / 2.0f) /
      static_cast<float>(window_context_.width);
  logic_context_.event.cursor_event.ypos =
      (static_cast<float>(window_context_.hight) / 2.0f - ypos) /
      -static_cast<float>(window_context_.hight);
}

void LogicEngine::CharInputCallback(char key, int action) {
  if (action == GLFW_PRESS) {
    logic_context_.event.key_event.insert(key);
  } else if (action == GLFW_RELEASE) {
    std::erase_if(logic_context_.event.key_event,
                  [key](char c) { return key == c; });
  }
}

LogicContext &LogicEngine::GetLogicContext() { return logic_context_; }

}  // namespace logic
}  // namespace atn