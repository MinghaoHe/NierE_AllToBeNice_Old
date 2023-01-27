//
// Created by minghaohe on 2023/1/18.
//

#ifndef NIERE_ALLTOBENICE_BASE_GARBAGE_COLLECTION_H
#define NIERE_ALLTOBENICE_BASE_GARBAGE_COLLECTION_H

#include <set>

#include "atn/common/utility.h"
#include "atn/base/game_object.h"


namespace atn {
namespace base {

class GarbageCollection {
 public:
  explicit GarbageCollection(std::set<std::shared_ptr<base::Object>>& game_objects);
  void Tick();

 private:
  std::set<std::shared_ptr<base::Object>>& objects_;
};

}
}

#endif // NIERE_ALLTOBENICE_BASE_GARBAGE_COLLECTION_H
