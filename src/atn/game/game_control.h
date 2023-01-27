//
// Created by minghaohe on 2023/1/16.
//

#ifndef NIERE_ALLTOBENICE_GAME_GAME_CONTROL_H
#define NIERE_ALLTOBENICE_GAME_GAME_CONTROL_H

#include <string>
#include <unordered_map>
#include <thread>

#include "atn/common/utility.h"
#include "atn/base/game_object.h"
#include "atn/logic/logic_context.h"
#include "atn/render/render_context.h"

namespace atn {
namespace game {

class GameControl {
 public:
  GameControl(logic::LogicContext& logic_context, render::RenderContext& render_context);

  ~GameControl();

 public:
  void Initialize();

  void Uninitialize();

  void Start();

  void GameMain();

 private:

 private:
  logic::LogicContext& logic_context_;
  render::RenderContext& render_context_;

  std::mutex lock_;
  std::condition_variable cv_;

  DISALLOW_COPY_AND_ASSIGN(GameControl);
};

}
}

#endif // NIERE_ALLTOBENICE_GAME_GAME_CONTROL_H
