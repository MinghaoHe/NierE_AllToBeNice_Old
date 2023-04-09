#include "game_window.h"

namespace atn {
namespace base {

GameWindow::GameWindow() {}

GameWindow::~GameWindow() noexcept {}

GameWindow& GameWindow::Instance() {
  static GameWindow instance;
  return instance;
}

void GameWindow::Initialize(const std::string_view window_name) {
  window_name_ = window_name;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
}

void GameWindow::Uninitialize() { glfwTerminate(); }

WindowContext& GameWindow::Create() {
  window_context_.window = glfwCreateWindow(
      kInitWidth, kInitHeight, window_name_.c_str(), nullptr, nullptr);
  window_context_.width = kInitWidth;
  window_context_.height = kInitHeight;

  glfwSetWindowSizeLimits(window_context_.window, window_context_.width,
                          window_context_.height, window_context_.width,
                          window_context_.height);
  return window_context_;
}

}  // namespace base
}  // namespace atn