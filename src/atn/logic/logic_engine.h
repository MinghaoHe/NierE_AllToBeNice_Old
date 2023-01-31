//
// Created by minghaohe on 2023/1/14.
//

#ifndef NIERE_ALLTOBENICE_LOGIC_LOGIC_ENGINE_H
#define NIERE_ALLTOBENICE_LOGIC_LOGIC_ENGINE_H

#include <unordered_set>

#include <3rdparty/glfw/glfw3.h>

#include "atn/common/utility.h"
#include "atn/base/game_object.h"
#include "atn/base/window_context.h"
#include "atn/logic/logic_context.h"

namespace atn {
namespace logic {

class LogicEngine {
 public:
  LogicEngine(base::WindowContext &window_context,
              std::unordered_set<std::shared_ptr<base::Object>> &objects,
              std::unordered_map<std::string, std::shared_ptr<base::Object>>
                  &global_objects_cache_map);

  ~LogicEngine() noexcept;

  void InitLogic();

  void UninitLogic();

  void Tick();

  void CursorPosCallback(float xpos, float ypos);

  void CharInputCallback(char key, int action);

  LogicContext &GetLogicContext();

 private:
  base::WindowContext &window_context_;
  std::unordered_set<std::shared_ptr<base::Object>> &objects_;
  std::unordered_map<std::string, std::shared_ptr<base::Object>>
      &global_objects_cache_map_;
  LogicContext logic_context_;

  DISALLOW_COPY_AND_ASSIGN(LogicEngine);
};

}  // namespace logic
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_LOGIC_LOGIC_ENGINE_H
