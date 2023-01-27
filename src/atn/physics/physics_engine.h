//
// Created by minghaohe on 2023/1/19.
//

#ifndef NIERE_ALLTOBENICE_PHYSICS_PHYSICS_ENGINE_H
#define NIERE_ALLTOBENICE_PHYSICS_PHYSICS_ENGINE_H

#include <set>
#include <vector>

#include "atn/base/game_object.h"
#include "atn/physics/physics_context.h"

namespace atn {
namespace physics {

class PhysicsEngine {
 public:
  explicit PhysicsEngine(std::set<std::shared_ptr<base::Object>> &objects);

  ~PhysicsEngine() noexcept;

  void InitPhysics();

  void UninitPhysics();

  void Tick();

  void CollisionDetection();
  void AddCollisionRelation(const std::string& tag, std::vector<std::string> tags);

 private:

  void GroupObjects();

 private:
  std::array<std::vector<std::shared_ptr<base::Object>>, 16> object_groups_;
  std::set<std::shared_ptr<base::Object>> &objects_;
  std::vector<std::pair<std::string, std::vector<std::string>>> collision_relation_;
  std::set<std::string> object_tags_;

  DISALLOW_COPY_AND_ASSIGN(PhysicsEngine);
};

}
}

#endif //NIERE_ALLTOBENICE_PHYSICS_PHYSICS_ENGINE_H
