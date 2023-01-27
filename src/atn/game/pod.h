//
// Created by minghaohe on 2023/1/15.
//

#ifndef NIERE_ALLTOBENICE_GAME_POD_H
#define NIERE_ALLTOBENICE_GAME_POD_H

#include <3rdparty/glm/glm.hpp>

#include "atn/base/game_object.h"

namespace atn {
namespace game {

class Pod : public base::GameObject {
 public:
  Pod();
  explicit Pod(std::shared_ptr<base::Object> other);

  virtual ~Pod() override;

 public:
  virtual void LogicInit() override;

  virtual void LogicUninit() override;

  virtual void LogicTick(logic::LogicContext &logic_context) override;

  virtual render::ObjectRenderData GetRenderData() override;

  virtual void PrebuildShader() override;
  virtual void SetShaderUniform() override;

 private:
  int hp_;
  float speed_;
  int fire_cooldown_time_;
  int fire_interval_time_;
  glm::mat4 translation_matrix_;
};

}
}


#endif // NIERE_ALLTOBENICE_GAME_POD_H
