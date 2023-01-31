//
// Created by minghaohe on 2023/1/23.
//

#include "enemy_attack.h"

#include "atn/base/game_engine.h"
#include "atn/game/enemy_bullet.h"

namespace atn {
namespace game {

EnemyAttack::EnemyAttack()
    : model_(glm::mat4(1.0f)),
      attack_random_(0.0f, 2.0f * static_cast<float>(M_PI)),
      bullet_type_random_(0.0f, 4.0f),
      rotation_angle_(0.0f),
      attack_type_(AttackType::Normal) {}

void EnemyAttack::SetAttackType(AttackType attack_type) {
  attack_type_ = attack_type;
  attack_rand_engine_.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  bullet_type_rand_engine_.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

void EnemyAttack::Attack(glm::mat4 model) {
  model_ = model;
  switch (attack_type_) {
    case AttackType::Normal: {
      NormalAttack();
    } break;
    case AttackType::Medium: {
      MediumAttack();
    } break;
    case AttackType::Hard: {
      HardAttack();
    } break;
    case AttackType::Hell: {
      HellAttack();
    } break;
    case AttackType::Sp3: {
      Sp3Attack();
    } break;
    case AttackType::Sp4: {
      Sp4Attack();
    } break;
    case AttackType::Sp6: {
      Sp6Attack();
    } break;
    default:
      break;
  }
}

void EnemyAttack::NormalAttack() {
  float radians = attack_random_(attack_rand_engine_);
  std::shared_ptr<game::EnemyBullet> bullet =
      base::NewObject<game::EnemyBullet>("enemy_bullet");

  glm::mat4 rotation_matrix = {
      {std::cos(radians), std::sin(radians), 0.0f, 0.0f},
      {std::sin(radians), -std::cos(radians), 0.0f, 0.0f},
      {0.0f, 0.0f, 1.0f, 0.0f},
      {0.0f, 0.0f, 0.0f, 1.0f}};
  model_ = model_ * rotation_matrix;
  bullet->SetStartModel(model_);
  bullet->SetBulletType(bullet_type_random_(bullet_type_rand_engine_) < 3.0f
                            ? EnemyBullet::BulletType::orange
                            : EnemyBullet::BulletType::red);
  base::AddObject(bullet);
}

void EnemyAttack::MediumAttack() {
  for (int i = 0; i < 4; ++i) {
    float radians = attack_random_(attack_rand_engine_);
    std::shared_ptr<game::EnemyBullet> bullet =
        base::NewObject<game::EnemyBullet>("enemy_bullet");

    glm::mat4 rotation_matrix = {
        {std::cos(radians), std::sin(radians), 0.0f, 0.0f},
        {std::sin(radians), -std::cos(radians), 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}};
    model_ = model_ * rotation_matrix;
    bullet->SetStartModel(model_);
    bullet->SetBulletType(bullet_type_random_(bullet_type_rand_engine_) < 3.0f
                              ? EnemyBullet::BulletType::orange
                              : EnemyBullet::BulletType::red);
    base::AddObject(bullet);
  }
}

void EnemyAttack::HardAttack() {
  for (int i = 0; i < 8; ++i) {
    float radians = attack_random_(attack_rand_engine_);
    std::shared_ptr<game::EnemyBullet> bullet =
        base::NewObject<game::EnemyBullet>("enemy_bullet");

    glm::mat4 rotation_matrix = {
        {std::cos(radians), std::sin(radians), 0.0f, 0.0f},
        {std::sin(radians), -std::cos(radians), 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}};
    model_ = model_ * rotation_matrix;
    bullet->SetStartModel(model_);
    bullet->SetBulletType(bullet_type_random_(bullet_type_rand_engine_) < 3.0f
                              ? EnemyBullet::BulletType::orange
                              : EnemyBullet::BulletType::red);
    base::AddObject(bullet);
  }
}

void EnemyAttack::HellAttack() {
  for (int i = 0; i < 16; ++i) {
    float radians = attack_random_(attack_rand_engine_);
    std::shared_ptr<game::EnemyBullet> bullet =
        base::NewObject<game::EnemyBullet>("enemy_bullet");

    glm::mat4 rotation_matrix = {
        {std::cos(radians), std::sin(radians), 0.0f, 0.0f},
        {std::sin(radians), -std::cos(radians), 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}};
    model_ = model_ * rotation_matrix;
    bullet->SetStartModel(model_);
    bullet->SetBulletType(bullet_type_random_(bullet_type_rand_engine_) < 3.0f
                              ? EnemyBullet::BulletType::orange
                              : EnemyBullet::BulletType::red);
    base::AddObject(bullet);
  }
}

void EnemyAttack::Sp3Attack() {
  rotation_angle_ += 0.2f;
  for (int i = 0; i < 3; ++i) {
    std::shared_ptr<game::EnemyBullet> bullet =
        base::NewObject<game::EnemyBullet>("enemy_bullet");

    float radians = 2.0f * static_cast<float>(M_PI) / static_cast<float>(3.0f) *
                        static_cast<float>(i) +
                    rotation_angle_;

    glm::mat4 rotation_matrix = {
        {std::cos(radians), std::sin(radians), 0.0f, 0.0f},
        {std::sin(radians), -std::cos(radians), 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}};
    bullet->SetStartModel(model_ * rotation_matrix);
    base::AddObject(bullet);
  }
}

void EnemyAttack::Sp4Attack() {}

void EnemyAttack::Sp6Attack() {}

}  // namespace game
}  // namespace atn
