//
// Created by minghaohe on 2023/1/19.
//

#ifndef NIERE_ALLTOBENICE_GAME_ENEMY_BULLET_H
#define NIERE_ALLTOBENICE_GAME_ENEMY_BULLET_H

#include <3rdparty/glm/glm.hpp>

#include "atn/base/game_object.h"

namespace atn {
namespace game {

class EnemyBullet : public base::GameObject {
 public:
  enum class BulletType { orange, red };

 public:
  EnemyBullet();
  explicit EnemyBullet(std::shared_ptr<base::Object> other);

  virtual ~EnemyBullet() override;

 public:
  virtual void LogicInit() override;

  virtual void LogicUninit() override;

  virtual void LogicTick(logic::LogicContext& logic_context) override;

  virtual render::ObjectRenderData GetRenderData() override;

  virtual void PrebuildShader() override;
  virtual void SetShaderUniform() override;

  void SetStartModel(const glm::mat4& start_model);

  void SetBulletType(BulletType bullet_type);

 private:
  float speed_;
  glm::mat4 start_model_;
  glm::mat4 translation_matrix_;

  BulletType bullet_type_;

  float r_;
  const int N_ = 48;
};

}  // namespace game
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_GAME_ENEMY_BULLET_H
