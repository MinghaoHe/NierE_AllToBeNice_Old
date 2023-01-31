//
// Created by minghaohe on 2023/1/19.
//

#include "object.h"

namespace atn {
namespace base {

Object::Object(const std::string &tag)
    : vao_(0), tag_(tag), model_(glm::mat4(1.0f)), is_garbage_(false) {}

Object::Object(std::shared_ptr<Object> other)
    : shader_(other->shader_),
      vao_(other->vao_),
      tag_(other->tag_),
      model_(glm::mat4(1.0f)),
      bounding_box_(other->bounding_box_),
      collision_detection_(other->collision_detection_),
      collision_(false),
      is_garbage_(false) {}

Object::~Object() noexcept {}

std::string Object::Tag() const { return tag_; }

glm::mat4 Object::GetModelMatrix() const { return model_; }

void Object::SetModelMatrix(const glm::mat4 &model) { model_ = model; }

void Object::RemoveCurrentObject() { is_garbage_ = true; }

bool Object::GarbageFlag() { return is_garbage_; }

void Object::RenderInit() {
  PrebuildShader();
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
}

void Object::RenderUninit() {
  shader_.Delete();
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &vao_);
}

void Object::SetBoundingBox(
    physics::BBoxType bbox_type, const glm::vec4 &center,
    std::variant<physics::CircleBox, physics::RectangleBox> box_data) {
  bounding_box_.bbox_type = bbox_type;
  bounding_box_.center = center;
  bounding_box_.box_data = box_data;
}

physics::BoundingBox Object::GetBoundingBox() const { return bounding_box_; }

void Object::EnableCollisionDetection(bool enable) {
  collision_detection_ = enable;
}

bool Object::NeedCollisionDetection() const { return collision_detection_; }

bool Object::GetCollision() const { return collision_; }

void Object::SetCollision(bool collision) { collision_ = collision; }

}  // namespace base
}  // namespace atn
