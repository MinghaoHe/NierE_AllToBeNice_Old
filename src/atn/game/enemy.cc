//
// Created by minghaohe on 2023/1/19.
//

#include "enemy.h"

#include "atn/game/enemy_bullet.h"

namespace atn {
namespace game {

Enemy::Enemy() : base::TextObject("enemy"), hp_(0), fire_cooldown_time_(0), fire_interval_time_(0) {}

Enemy::Enemy(std::shared_ptr<base::Object> other)
        : base::TextObject(std::dynamic_pointer_cast<base::TextObject>(other)), fire_cooldown_time_(0),
          fire_interval_time_(0) {
  std::shared_ptr<Enemy> dother = std::dynamic_pointer_cast<Enemy>(other);
  hp_ = dother->hp_;
  fire_cooldown_time_ = dother->fire_cooldown_time_;
}

Enemy::~Enemy() {
}

void Enemy::LogicInit() {
  fire_cooldown_time_ = 250;
  EnableCollisionDetection(true);
}

void Enemy::LogicUninit() {}

void Enemy::LogicTick(logic::LogicContext &logic_context) {
  fire_interval_time_ += logic_context.interval_time;
  if (fire_interval_time_ > fire_cooldown_time_) {
    enemy_attack_.Attack(GetModelMatrix());
    fire_interval_time_ = 0;
  }

  if (collision_) {
    collision_ = false;
    if (0 == hp_--) {
      RemoveCurrentObject();
      return;
    }
  }
  SetModelMatrix(enemy_trace_.GetTraceModel(logic_context.interval_time));
}

void Enemy::PrebuildShader() {
  shader_.PrebuildFile("../src/atn/game/shader/enemy.vs", "../src/atn/game/shader/enemy.fs");
}

void Enemy::SetShaderUniform() {
  shader_.SetMatrix4("model", GetModelMatrix());
  shader_.SetVec3("text_color", 1.0f, 1.0f, 1.0f);
}

void Enemy::SetEnemyTrace(EnemyTrace::MovementType movement_type, float speed, const glm::mat4 &start_model,
                          const glm::mat4 &end_model) {
  enemy_trace_.SetEnemyTrace(movement_type, speed, start_model, end_model);
}

void Enemy::SetEnemyState(int hp, float scale) {
  hp_ = hp;
  scale_ = scale;
}

void Enemy::SetEnemyAttackType(int fire_cooldown_time, EnemyAttack::AttackType attack_type) {
  fire_cooldown_time_ = fire_cooldown_time;
  enemy_attack_.SetAttackType(attack_type);
}

}
}