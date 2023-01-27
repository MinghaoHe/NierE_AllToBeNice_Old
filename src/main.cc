#include <chrono>

#include "atn/base/game_engine.h"
#include "atn/base/game_window.h"

int fps = 60;

int main(int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);

  atn::base::GameWindow& window = atn::base::GameWindow::Instance();
  window.Initialize("NierE_AllToBeNice");
  atn::base::WindowContext& window_context = window.CreateWindow();

  atn::base::GameEngine& engine =  atn::base::GameEngine::Instance();
  engine.Initialize(&window_context);
  engine.SetFps(fps);

  engine.Start();
  while (!glfwWindowShouldClose(window_context.window)) {
    if (glfwGetKey(window_context.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window_context.window, true);
    }
    engine.Tick();
    engine.Sleep();
  }

  engine.Uninitalize();
  window.Uninitialize();

  return 0;
}


