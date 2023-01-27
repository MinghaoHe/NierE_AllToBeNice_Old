//
// Created by minghaohe on 2023/1/19.
//

#include "enemy_bullet.h"

namespace atn {
namespace game {

EnemyBullet::EnemyBullet() : base::GameObject("enemy_bullet"), start_model_(glm::mat4(1.0f)),
                             translation_matrix_(glm::mat4(1.0f)), bullet_type_(BulletType::orange), speed_(0.0f), r_(0.0f) {}

EnemyBullet::EnemyBullet(std::shared_ptr<base::Object> other)
        : base::GameObject(std::dynamic_pointer_cast<base::GameObject>(other)), start_model_(glm::mat4(1.0f)),
          translation_matrix_(glm::mat4(1.0f)) {
  std::shared_ptr<EnemyBullet> dother = std::dynamic_pointer_cast<EnemyBullet>(other);
  speed_ = dother->speed_;
  r_ = dother->r_;
  bullet_type_ = dother->bullet_type_;
  EnableCollisionDetection(bullet_type_ == EnemyBullet::BulletType::orange);
}

EnemyBullet::~EnemyBullet() {
}

void EnemyBullet::LogicInit() {
  r_ = 0.05f;
  speed_ = 0.0005f;

  EnableCollisionDetection(true);
}

void EnemyBullet::LogicUninit() {}

void EnemyBullet::LogicTick(logic::LogicContext &logic_context) {
  translation_matrix_[3][1] += (speed_ * static_cast<float>(logic_context.interval_time));

  if (translation_matrix_[3][1] > 3.0f || translation_matrix_[3][1] < -3.0f || translation_matrix_[3][2] > 3.0f ||
      translation_matrix_[3][2] < -3.0f) {
    RemoveCurrentObject();
    return;
  }

  if (collision_) {
    RemoveCurrentObject();
    return;
  }

  SetModelMatrix(start_model_ * translation_matrix_);
}

render::ObjectRenderData EnemyBullet::GetRenderData() {
  render::ObjectRenderData render_data;
  render_data.vertices.push_back(0.0f);
  render_data.vertices.push_back(0.0f);
  render_data.vertices.push_back(0.0f);
  for (int i = 0; i < N_; ++i) {
    render_data.vertices.push_back(r_ * std::cos(2 * M_PI / N_ * i));
    render_data.vertices.push_back(r_ * std::sin(2 * M_PI / N_ * i));
    render_data.vertices.push_back(0.0f);
  }
  for (int i = 1; i < N_; ++i) {
    render_data.indices.push_back(0);
    render_data.indices.push_back(i);
    render_data.indices.push_back(i + 1);
  }
  render_data.indices.push_back(0);
  render_data.indices.push_back(1);
  render_data.indices.push_back(N_);

  gl_element_cout_ = render_data.indices.size();

  physics::CircleBox circle_box;
  circle_box.r = r_;
  SetBoundingBox(physics::BBoxType::circle, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), circle_box);

  return render_data;
}

void EnemyBullet::PrebuildShader() {
  shader_.PrebuildFile("../src/atn/game/shader/enemy_bullet.vs", "../src/atn/game/shader/enemy_bullet.fs");
}

void EnemyBullet::SetShaderUniform() {
  shader_.SetMatrix4("model", GetModelMatrix());
  if (bullet_type_ == BulletType::orange) {
    shader_.SetVec3("color", static_cast<float>(0xef) / static_cast<float>(0xff),
                    static_cast<float>(0x7f) / static_cast<float>(0xff),
                    static_cast<float>(0x37) / static_cast<float>(0xff));
  } else if (bullet_type_ == BulletType::red) {
    shader_.SetVec3("color", static_cast<float>(0xcd) / static_cast<float>(0xff),
                    static_cast<float>(0x33) / static_cast<float>(0xff),
                    static_cast<float>(0x58) / static_cast<float>(0xff));
  }
}

void EnemyBullet::SetStartModel(const glm::mat4 &start_model) {
  start_model_ = start_model;
  SetModelMatrix(start_model_);
}

void EnemyBullet::SetBulletType(BulletType bullet_type) {
  bullet_type_ = bullet_type;
  if (bullet_type_ == BulletType::red) {
    EnableCollisionDetection(false);
  }
}

}
}
