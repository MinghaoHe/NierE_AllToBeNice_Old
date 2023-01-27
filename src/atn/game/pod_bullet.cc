//
// Created by minghaohe on 2023/1/18.
//

#include "pod_bullet.h"


namespace atn {
namespace game {

PodBullet::PodBullet()
        : base::GameObject("pod_bullet"), start_model_(glm::mat4(1.0f)),
          translation_matrix_(glm::mat4(1.0f)), speed_(0.0f) {}

PodBullet::PodBullet(std::shared_ptr<Object> other) : base::GameObject(
        std::dynamic_pointer_cast<base::GameObject>(other)),
                                                      start_model_(glm::mat4(1.0f)),
                                                      translation_matrix_(glm::mat4(1.0f)) {
  std::shared_ptr<PodBullet> dother = std::dynamic_pointer_cast<PodBullet>(other);
  speed_ = dother->speed_;
}

PodBullet::~PodBullet() {
}

void PodBullet::LogicInit() {
  speed_ = 0.002f;
  EnableCollisionDetection(true);
}

void PodBullet::LogicUninit() {}

void PodBullet::LogicTick(logic::LogicContext &logic_context) {
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

render::ObjectRenderData PodBullet::GetRenderData() {
  render::ObjectRenderData render_data;
  render_data.vertices = {0.018f, 0.0f, 0.001f,
                          -0.018f, 0.0f, 0.001f,
                          0.018f, 0.12f, 0.001f,
                          -0.018f, 0.12f, 0.001f,};
  render_data.indices = {0, 1, 2,
                         1, 2, 3};
  gl_element_cout_ = render_data.indices.size();

  physics::RectangleBox rectangle_box;
  for (int i = 0; i < 4; ++i) {
    rectangle_box.vertices[i] = glm::vec4(render_data.vertices[i * 3 + 0], render_data.vertices[i * 3 + 1],
                                          render_data.vertices[i * 3 + 2], 1.0f);
  }
  SetBoundingBox(physics::BBoxType::rectangle, glm::vec4(0.0f, 0.06f, 0.0f, 1.0f), rectangle_box);

  return render_data;
}

void PodBullet::PrebuildShader() {
  shader_.PrebuildFile("../src/atn/game/shader/pod_bullet.vs", "../src/atn/game/shader/pod_bullet.fs");
}

void PodBullet::SetShaderUniform() {
  shader_.SetMatrix4("model", GetModelMatrix());
  shader_.SetVec3("color", static_cast<float>(0xf8) / static_cast<float>(0xff),
                  static_cast<float>(0xf6) / static_cast<float>(0xff),
                  static_cast<float>(0xf0) / static_cast<float>(0xff));
}

void PodBullet::SetStartModel(const glm::mat4 &start_model) {
  start_model_ = start_model;
  SetModelMatrix(start_model_);
}

}
}