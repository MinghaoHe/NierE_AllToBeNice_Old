//
// Created by minghaohe on 2023/1/19.
//

#ifndef NIERE_ALLTOBENICE_GAME_ENEMY_H
#define NIERE_ALLTOBENICE_GAME_ENEMY_H

#include <3rdparty/glm/glm.hpp>

#include "atn/base/text_object.h"
#include "atn/game/enemy_trace.h"
#include "atn/game/enemy_attack.h"

namespace atn {
namespace game {

class Enemy : public base::TextObject {
 public:
  Enemy();

  explicit Enemy(std::shared_ptr<base::Object> other);

  virtual ~Enemy() override;

 public:
  virtual void LogicInit() override;

  virtual void LogicUninit() override;

  virtual void LogicTick(logic::LogicContext &logic_context) override;

  virtual void PrebuildShader() override;

  virtual void SetShaderUniform() override;

  void SetEnemyTrace(EnemyTrace::MovementType movement_type, float speed, const glm::mat4 &start_model,
                     const glm::mat4 &end_model = glm::mat4(1.0f));

  void SetEnemyState(int hp, float scale);

  void SetEnemyAttackType(int fire_cooldown_time, EnemyAttack::AttackType attack_type);

 private:
  int hp_;
  int fire_cooldown_time_;
  int fire_interval_time_;
  EnemyTrace enemy_trace_;
  EnemyAttack enemy_attack_;
};

}
}

#endif // NIERE_ALLTOBENICE_GAME_ENEMY_H
