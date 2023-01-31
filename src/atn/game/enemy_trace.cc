//
// Created by minghaohe on 2023/1/21.
//

#include "enemy_trace.h"

#include <chrono>

#include <3rdparty/glm/gtc/matrix_transform.hpp>


namespace atn {
namespace game {

EnemyTrace::EnemyTrace()
    : speed_(0.0f),
      time_(0),
      model_(glm::mat4(1.0f)),
      translation_(glm::vec3(0.0f)),
      walk_(0),
      walk_length_(0),
      walk_random_(10, 45),
      x_random_(-1.0f, 1.0f),
      y_random_(-0.25f, 0.75f) {}

void EnemyTrace::SetEnemyTrace(MovementType movement_type, float speed,
                               const glm::mat4 &start_model,
                               const glm::mat4 &end_model) {
  movement_type_ = movement_type;

  if (movement_type_ == MovementType::Moving) {
    walk_rand_engine_.seed(
        std::chrono::high_resolution_clock::now().time_since_epoch().count() + 0);
    x_rand_engine_.seed(
        std::chrono::high_resolution_clock::now().time_since_epoch().count() + 1024);
    y_rand_engine_.seed(
        std::chrono::high_resolution_clock::now().time_since_epoch().count() + 2048);
  }

  speed_ = speed;
  model_ = start_model;
  start_model_ = start_model;
  end_model_ = end_model;
  time_ = 0;
}

glm::mat4 EnemyTrace::GetTraceModel(int interval_time) {
  time_ = interval_time;

  switch (movement_type_) {
    case MovementType::Fixed:
      return GetFixedTraceModel();
    case MovementType::Moving:
      return GetMovingTraceModel();
    default:
      return glm::mat4(1.0f);
  }
}

glm::mat4 EnemyTrace::GetFixedTraceModel() {
  glm::vec3 expect_translation = glm::vec3(0.0f);
  expect_translation.x = end_model_[3][0] - start_model_[3][0];
  expect_translation.y = end_model_[3][1] - start_model_[3][1];
  translation_ += time_ * speed_ * glm::normalize(expect_translation);
  if (glm::length(translation_) > glm::length(expect_translation)) {
    return end_model_;
  }
  model_ = glm::translate(start_model_, translation_);
  return model_;
}

glm::mat4 EnemyTrace::GetMovingTraceModel() {
  glm::vec4 position = model_ * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  if (walk_length_ < walk_) {
    walk_ = 0;
    walk_length_ = walk_random_(walk_rand_engine_);
    float x_random_pos = x_random_(x_rand_engine_);
    float y_random_pos = y_random_(y_rand_engine_);
    translation_ = time_ * speed_ *
                   glm::normalize(glm::vec3(x_random_pos - position.x,
                                            y_random_pos - position.y, 0.0f));
    model_ = glm::translate(model_, translation_);
  } else {
    ++walk_;
    model_ = glm::translate(model_, translation_);
  }
  return model_;
}

}  // namespace game
}  // namespace atn
