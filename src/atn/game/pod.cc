//
// Created by minghaohe on 2023/1/15.
//

#include "pod.h"

#include "atn/base/game_engine.h"
#include "atn/game/pod_bullet.h"

namespace atn {
namespace game {

Pod::Pod() : base::GameObject("pod"), hp_(3), fire_cooldown_time_(0), fire_interval_time_(0), speed_(0.0f),
             translation_matrix_(glm::mat4(1.0f)) {}

Pod::Pod(std::shared_ptr<base::Object> other) : base::GameObject(std::dynamic_pointer_cast<base::GameObject>(other)),
                                                translation_matrix_(glm::mat4(1.0f)), hp_(3), fire_interval_time_(0) {
  std::shared_ptr<Pod> dother = std::dynamic_pointer_cast<Pod>(other);
  speed_ = dother->speed_;
  fire_cooldown_time_ = dother->fire_cooldown_time_;
}

Pod::~Pod() {
}

void Pod::LogicInit() {
  hp_ = 3;
  speed_ = 0.0015f;
  fire_cooldown_time_ = 150;
}

void Pod::LogicUninit() {

}

void Pod::LogicTick(logic::LogicContext &logic_context) {
  fire_interval_time_ += logic_context.interval_time;
  std::for_each(logic_context.event.key_event.cbegin(), logic_context.event.key_event.end(),
                [this, &logic_context](char c) {
                  switch (c) {
                    case 'w':
                    case 'W': {
                      translation_matrix_[3][1] += (speed_ * static_cast<float>(logic_context.interval_time));
                    }
                      break;
                    case 'a':
                    case 'A': {
                      translation_matrix_[3][0] -= speed_ * static_cast<float>(logic_context.interval_time);
                    }
                      break;
                    case 's':
                    case 'S': {
                      translation_matrix_[3][1] -= speed_ * static_cast<float>(logic_context.interval_time);
                    }
                      break;
                    case 'd':
                    case 'D': {
                      translation_matrix_[3][0] += speed_ * static_cast<float>(logic_context.interval_time);
                    }
                      break;
                    case ' ': {
                      // fire !!!
                      if (fire_interval_time_ > fire_cooldown_time_) {
                        std::shared_ptr<game::PodBullet> bullet = base::NewObject<game::PodBullet>("pod_bullet");
                        bullet->SetStartModel(GetModelMatrix());
                        base::AddObject(bullet);
                        fire_interval_time_ = 0;
                      }
                    }
                      break;
                    default:
                      break;
                  }
                });

  glm::mat4 rotation_matrix = glm::mat4(1.0f);
  if (logic_context.event.cursor_event.xpos != 0.0f || logic_context.event.cursor_event.ypos != 0.0f) {
    float x = logic_context.event.cursor_event.xpos;
    float y = logic_context.event.cursor_event.ypos;
    float l = std::sqrt(x * x + y * y);

    rotation_matrix = {{-y / l, -x / l, 0.0f, 0.0f},
                       {x / l,  -y / l, 0.0f, 0.0f},
                       {0.0f,   0.0f,   1.0f, 0.0f},
                       {0.0f,   0.0f,   0.0f, 1.0f}
    };
  }

  SetModelMatrix(translation_matrix_ * rotation_matrix);
}

render::ObjectRenderData Pod::GetRenderData() {
  render::ObjectRenderData render_data;
  render_data.vertices = {0.0f, 0.0f, 0.0f,
                          0.0f, 0.12f, 0.0f,
                          0.04f, 0.025f, 0.0f,
                          -0.04f, 0.025f, 0.0f,};
  render_data.indices = {0, 1, 2,
                         0, 1, 3};

  gl_element_cout_ = render_data.indices.size();
  return render_data;
}

void Pod::PrebuildShader() {
  shader_.PrebuildFile("../src/atn/game/shader/pod.vs", "../src/atn/game/shader/pod.fs");
}

void Pod::SetShaderUniform() { shader_.SetMatrix4("model", GetModelMatrix()); }

}
}
