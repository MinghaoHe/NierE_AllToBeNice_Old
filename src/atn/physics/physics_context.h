//
// Created by minghaohe on 2023/1/24.
//

#ifndef NIERE_ALLTOBENICE_PHYSICS_PHYSICS_CONTEXT_H
#define NIERE_ALLTOBENICE_PHYSICS_PHYSICS_CONTEXT_H

#include <array>
#include <variant>

#include <3rdparty/glm/glm.hpp>

namespace atn {
namespace physics {

enum BBoxType {
  circle,
  rectangle,
};

struct CircleBox {
  float r;
};

struct RectangleBox {
  std::array<glm::vec4, 4> vertices;
};

struct BoundingBox {
  BBoxType bbox_type;
  glm::vec4 center;
  std::variant<CircleBox, RectangleBox> box_data;
};

}  // namespace physics
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_PHYSICS_PHYSICS_CONTEXT_H
