//
// Created by minghaohe on 2023/1/14.
//

#ifndef NIERE_ALLTOBENICE_COMMON_UTILITY_H
#define NIERE_ALLTOBENICE_COMMON_UTILITY_H

#include <iostream>

#define DISALLOW_COPY_AND_ASSIGN(class_name)    \
  class_name(class_name&&) = delete;            \
  class_name(const class_name&) = delete;       \
  class_name& operator=(class_name&&) = delete; \
  class_name& operator=(const class_name&) = delete

#define UNUSED(x) (void)(x)

#endif  // NIERE_ALLTOBENICE_COMMON_UTILITY_H
