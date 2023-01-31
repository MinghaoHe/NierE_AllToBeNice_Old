//
// Created by minghaohe on 2023/1/18.
//

#include "garbage_collection.h"

namespace atn {
namespace base {

GarbageCollection::GarbageCollection(
    std::unordered_set<std::shared_ptr<base::Object>> &objects)
    : objects_(objects) {}

void GarbageCollection::Tick() {
  std::erase_if(objects_, [](std::shared_ptr<base::Object> garbage) {
    return garbage->GarbageFlag();
  });
}

}  // namespace base
}  // namespace atn