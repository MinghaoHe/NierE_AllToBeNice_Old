//
// Created by minghaohe on 2023/1/17.
//

#ifndef NIERE_ALLTOBENICE_BASE_WINDOW_CONTEXT_H
#define NIERE_ALLTOBENICE_BASE_WINDOW_CONTEXT_H

#include <3rdparty/glfw/glfw3.h>

namespace atn {
namespace base {

struct WindowContext {
  GLFWwindow* window;
  int hight;
  int width;
};

}
}

#endif // NIERE_ALLTOBENICE_BASE_WINDOW_CONTEXT_H
