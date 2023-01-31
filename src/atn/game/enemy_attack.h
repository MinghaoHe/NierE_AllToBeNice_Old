//
// Created by minghaohe on 2023/1/23.
//

#ifndef NIERE_ALLTOBENICE_GAME_ENEMY_ATTACK_H
#define NIERE_ALLTOBENICE_GAME_ENEMY_ATTACK_H

#include <random>

#include <3rdparty/glm/glm.hpp>


namespace atn {
namespace game {

class EnemyAttack {
 public:
  enum class AttackType {
    Normal /* 1/s */,
    Medium /*  */,
    Hard /*  */,
    Hell, /*  */
    Sp3,
    Sp4,
    Sp6
  };

  EnemyAttack();
  void SetAttackType(AttackType attack_type);
  void Attack(glm::mat4 model);

 private:
  void NormalAttack();
  void MediumAttack();
  void HardAttack();
  void HellAttack();
  void Sp3Attack();
  void Sp4Attack();
  void Sp6Attack();

 private:
  glm::mat4 model_;
  std::default_random_engine attack_rand_engine_;
  std::uniform_real_distribution<float> attack_random_;

  std::default_random_engine bullet_type_rand_engine_;
  std::uniform_real_distribution<float> bullet_type_random_;

  float rotation_angle_;
  AttackType attack_type_;
};

}  // namespace game
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_GAME_ENEMY_ATTACK_H
