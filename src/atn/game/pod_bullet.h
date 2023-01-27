//
// Created by minghaohe on 2023/1/18.
//

#ifndef NIERE_ALLTOBENICE_GAME_POD_BULLET_H
#define NIERE_ALLTOBENICE_GAME_POD_BULLET_H

#include <3rdparty/glm/glm.hpp>

#include "atn/base/game_object.h"

namespace atn {
namespace game {

class PodBullet : public base::GameObject {
 public:
  PodBullet();
  explicit PodBullet(std::shared_ptr<Object> other);

  virtual ~PodBullet() override;

 public:
  virtual void LogicInit() override;

  virtual void LogicUninit() override;

  virtual void LogicTick(logic::LogicContext &logic_context) override;

  virtual void PrebuildShader() override;

  virtual render::ObjectRenderData GetRenderData() override;

  virtual void SetShaderUniform() override;

  void SetStartModel(const glm::mat4& start_model);

 private:
  float speed_;
  glm::mat4 start_model_;
  glm::mat4 translation_matrix_;
};

}
}

#endif // NIERE_ALLTOBENICE_GAME_POD_BULLET_H
