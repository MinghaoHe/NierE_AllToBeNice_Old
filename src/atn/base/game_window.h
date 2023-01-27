#ifndef NIERE_ALLTOBENICE_BASE_GAME_WINDOW_H
#define NIERE_ALLTOBENICE_BASE_GAME_WINDOW_H

#include <string>
#include <3rdparty/glfw/glfw3.h>

#include "atn/common/utility.h"
#include "atn/base/window_context.h"


namespace atn {
namespace base {

class GameWindow {
 public:
  ~GameWindow() noexcept;

  [[nodiscard]] static GameWindow& Instance();
 public:
  void Initialize(const std::string_view window_name);
  void Uninitialize();

  WindowContext& CreateWindow();

 public:
  static constexpr const int kInitWidth = 800;
  static constexpr const int kInitHeight = 600;

 private:
  std::string window_name_;
  WindowContext window_context_;

  GameWindow();
  DISALLOW_COPY_AND_ASSIGN(GameWindow);
};

}
}

#endif // NIERE_ALLTOBENICE_BASE_GAME_WINDOW_H
