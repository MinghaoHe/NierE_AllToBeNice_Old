//
// Created by minghaohe on 2023/1/19.
//

#ifndef NIERE_ALLTOBENICE_BASE_OBJECT_H
#define NIERE_ALLTOBENICE_BASE_OBJECT_H

#include <string>
#include <unordered_map>

#include <3rdparty/glad/glad.h>
#include <3rdparty/glm/glm.hpp>

#include "atn/common/utility.h"
#include "atn/logic/logic_context.h"
#include "atn/render/render_context.h"
#include "atn/render/shader.h"
#include "atn/physics/physics_context.h"

namespace atn {
namespace base {

class Object {
 public:
  Object(const std::string& tag);
  explicit Object(std::shared_ptr<Object> other);

  virtual ~Object() noexcept;

  // logic
  virtual void LogicInit() = 0;
  virtual void LogicUninit() = 0;
  virtual void LogicTick(logic::LogicContext& logic_context) = 0;

  glm::mat4 GetModelMatrix() const;
  void SetModelMatrix(const glm::mat4& model);

  // render
  virtual void RenderInit();
  virtual void RenderUninit();
  virtual void RenderTick(const render::RenderContext& render_context) = 0;

  // render shader
  virtual void PrebuildShader() = 0;
  virtual void SetShaderUniform() = 0;

  // physics
  void SetBoundingBox(
      physics::BBoxType bbox_type, const glm::vec4& center,
      std::variant<physics::CircleBox, physics::RectangleBox> box_data);
  physics::BoundingBox GetBoundingBox() const;
  void EnableCollisionDetection(bool enable);
  bool NeedCollisionDetection() const;
  bool GetCollision() const;
  void SetCollision(bool collision);

  // other
  void RemoveCurrentObject();
  bool GarbageFlag();

  std::string Tag() const;

 protected:
  // render
  GLuint vao_;
  render::Shader shader_;

  // other
  std::string tag_;
  bool is_garbage_;

  bool collision_detection_;
  bool collision_;
  physics::BoundingBox bounding_box_;

 private:
  glm::mat4 model_;
};

}  // namespace base
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_BASE_OBJECT_H
