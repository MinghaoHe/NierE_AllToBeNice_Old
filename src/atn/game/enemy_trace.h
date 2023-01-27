//
// Created by minghaohe on 2023/1/21.
//

#ifndef NIERE_ALLTOBENICE_GAME_ENEMY_TRACE_H
#define NIERE_ALLTOBENICE_GAME_ENEMY_TRACE_H

#include <random>
#include <3rdparty/glm/glm.hpp>

namespace atn {
namespace game {

class EnemyTrace {
 public:
  enum class MovementType {
    Fixed, Moving
  };
 public:
  EnemyTrace();

  void SetEnemyTrace(MovementType movement_type, float speed, const glm::mat4 &start_model,
                     const glm::mat4 &end_model = glm::mat4(1.0f));

  glm::mat4 GetTraceModel(int interval_time);

 private:
  glm::mat4 GetFixedTraceModel();

  glm::mat4 GetMovingTraceModel();

 private:
  float speed_;
  int time_;
  glm::mat4 model_;
  glm::mat4 start_model_;
  glm::mat4 end_model_;
  MovementType movement_type_;

  int walk_;
  int walk_length_;
  glm::vec3 translation_;
  std::default_random_engine walk_rand_engine_;
  std::uniform_real_distribution<float> walk_random_;
  std::default_random_engine x_rand_engine_;
  std::uniform_real_distribution<float> x_random_;
  std::default_random_engine y_rand_engine_;
  std::uniform_real_distribution<float> y_random_;
};

}
}


#endif // NIERE_ALLTOBENICE_GAME_ENEMY_TRACE_H
