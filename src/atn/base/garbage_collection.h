//
// Created by minghaohe on 2023/1/18.
//

#ifndef NIERE_ALLTOBENICE_BASE_GARBAGE_COLLECTION_H
#define NIERE_ALLTOBENICE_BASE_GARBAGE_COLLECTION_H

#include <unordered_set>

#include "atn/common/utility.h"
#include "atn/base/game_object.h"

namespace atn {
namespace base {

class GarbageCollection {
 public:
  explicit GarbageCollection(std::unordered_set<std::shared_ptr<base::Object>>& game_objects);
  void Tick();

 private:
  std::unordered_set<std::shared_ptr<base::Object>>& objects_;
};

}  // namespace base
}  // namespace atn

#endif  // NIERE_ALLTOBENICE_BASE_GARBAGE_COLLECTION_H
