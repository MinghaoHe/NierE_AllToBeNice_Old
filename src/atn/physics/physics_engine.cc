//
// Created by minghaohe on 2023/1/19.
//

#include "physics_engine.h"

#include <limits>

namespace atn {
namespace physics {

bool Intersect(const BoundingBox &box1, const glm::mat4 &model1, const BoundingBox &box2, const glm::mat4 &model2);


PhysicsEngine::PhysicsEngine(std::set<std::shared_ptr<base::Object>> &objects) : objects_(objects) {}

PhysicsEngine::~PhysicsEngine() noexcept {}

void PhysicsEngine::InitPhysics() {}

void PhysicsEngine::UninitPhysics() {}

void PhysicsEngine::Tick() {

  GroupObjects();

  CollisionDetection();
}

void PhysicsEngine::AddCollisionRelation(const std::string &tag, std::vector<std::string> tags) {
  collision_relation_.push_back({tag, tags});
  object_tags_.insert(tag);
  std::for_each(tags.begin(), tags.end(),
                [this](const std::string &tag) {
                  object_tags_.insert(tag);
                });
}

void PhysicsEngine::GroupObjects() {
  std::for_each(object_groups_.begin(), object_groups_.end(), [](std::vector<std::shared_ptr<base::Object>> &group) {
    group.clear();
  });

  std::for_each(objects_.begin(), objects_.end(), [this](const std::shared_ptr<base::Object> object) {
    physics::BoundingBox bounding_box = object->GetBoundingBox();
    glm::vec4 center = object->GetModelMatrix() * bounding_box.center;
    if (center.x > 0.0f && center.y > 0.0f) {
      if (center.x > 0.6f && center.y > 0.6f) {
        object_groups_[0].push_back(object);
      } else if (center.x < 0.6f && center.y > 0.6f) {
        object_groups_[1].push_back(object);
      } else if (center.x < 0.6f && center.y < 0.6f) {
        object_groups_[2].push_back(object);
      } else if (center.x > 0.6f && center.y < 0.6f) {
        object_groups_[3].push_back(object);
      }
    } else if (center.x < 0.0f && center.y > 0.0f) {
      if (center.x > -0.6f && center.y > 0.6f) {
        object_groups_[4].push_back(object);
      } else if (center.x < -0.6f && center.y > 0.6f) {
        object_groups_[5].push_back(object);
      } else if (center.x < -0.6f && center.y < 0.6f) {
        object_groups_[6].push_back(object);
      } else if (center.x > -0.6f && center.y < 0.6f) {
        object_groups_[7].push_back(object);
      }
    } else if (center.x < 0.0f && center.y < 0.0f) {
      if (center.x > -0.6f && center.y > -0.6f) {
        object_groups_[8].push_back(object);
      } else if (center.x < -0.6f && center.y > -0.6f) {
        object_groups_[9].push_back(object);
      } else if (center.x < -0.6f && center.y < -0.6f) {
        object_groups_[10].push_back(object);
      } else if (center.x > -0.6f && center.y < -0.6f) {
        object_groups_[11].push_back(object);
      }
    } else if (center.x > 0.0f && center.y < 0.0f) {
      if (center.x > 0.6f && center.y > -0.6f) {
        object_groups_[12].push_back(object);
      } else if (center.x < 0.6f && center.y > -0.6f) {
        object_groups_[13].push_back(object);
      } else if (center.x < 0.6f && center.y < -0.6f) {
        object_groups_[14].push_back(object);
      } else if (center.x > 0.6f && center.y < -0.6f) {
        object_groups_[15].push_back(object);
      }
    }
  });
}

void PhysicsEngine::CollisionDetection() {
  for (const std::vector<std::shared_ptr<base::Object>> &group: object_groups_) {
    std::unordered_map<std::string, std::vector<std::shared_ptr<base::Object>>> object_map;
    std::for_each(group.begin(), group.end(), [&object_map](std::shared_ptr<base::Object> object) {
      if (object->NeedCollisionDetection())
        object_map[object->Tag()].push_back(object);
    });
    for (const std::pair<std::string, std::vector<std::string>> &relation: collision_relation_) {
      std::vector<std::shared_ptr<base::Object>> main_objects = object_map[relation.first];
      if (main_objects.empty()) break;

      std::vector<std::shared_ptr<base::Object>> sub_objects;
      std::for_each(relation.second.begin(), relation.second.end(),
                    [&sub_objects, &object_map](const std::string &tag) {
                      std::vector<std::shared_ptr<base::Object>> merge;
                      std::merge(sub_objects.begin(), sub_objects.end(),
                                 object_map[tag].begin(),
                                 object_map[tag].end(), std::back_inserter(merge));
                      sub_objects = merge;
                    });
      if (sub_objects.empty()) break;

      for (std::shared_ptr<base::Object> main_object: main_objects) {
        for (std::shared_ptr<base::Object> sub_object: sub_objects) {
          if (!main_object->GetCollision() && !sub_object->GetCollision() &&
              Intersect(main_object->GetBoundingBox(),
                        main_object->GetModelMatrix(),
                        sub_object->GetBoundingBox(),
                        sub_object->GetModelMatrix())) {
            main_object->SetCollision(true);
            sub_object->SetCollision(true);
          }
        }
      }
    }
  }
}

bool Intersect(const BoundingBox &box1, const glm::mat4 &model1, const BoundingBox &box2, const glm::mat4 &model2) {
  if (box1.bbox_type == BBoxType::rectangle && box2.bbox_type == BBoxType::circle) {
    glm::vec4 center = model2 * box2.center;
    for (const glm::vec4 &pos: std::get<RectangleBox>(box1.box_data).vertices) {
      if (glm::length(center - model1 * pos) < std::get<CircleBox>(box2.box_data).r) {
        return true;
      }
    }
  } else if (box1.bbox_type == BBoxType::rectangle && box2.bbox_type == BBoxType::rectangle) {
    float x_min = std::numeric_limits<float>::max();
    float x_max = std::numeric_limits<float>::min();
    float y_min = std::numeric_limits<float>::max();
    float y_max = std::numeric_limits<float>::min();

    for (glm::vec4 vertex : std::get<RectangleBox>(box2.box_data).vertices) {
      vertex = model2 * vertex;
      x_min = std::min(vertex.x, x_min);
      x_max = std::max(vertex.x, x_max);
      y_min = std::min(vertex.y, y_min);
      y_max = std::max(vertex.y, y_max);
    }
    for (glm::vec4 pos : std::get<RectangleBox>(box1.box_data).vertices) {
      pos = model1 * pos;
      if (pos.x > x_min && pos.x < x_max && pos.y > y_min && pos.y < y_max) {
        return true;
      }
    }
  }
  return false;
}

}
}
