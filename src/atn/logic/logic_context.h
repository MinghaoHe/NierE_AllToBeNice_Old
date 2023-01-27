//
// Created by minghaohe on 2023/1/15.
//

#ifndef NIERE_ALLTOBENICE_LOGIC_LOGIC_CONTEXT_H
#define NIERE_ALLTOBENICE_LOGIC_LOGIC_CONTEXT_H

#include <unordered_set>
#include <vector>

namespace atn {

namespace logic {

struct CursorEvent {
  float xpos = 0.0f;
  float ypos = 0.0f;
};

struct LogicEvent {
  CursorEvent cursor_event;
  std::unordered_set<char> key_event;
};

struct LogicContext {
  LogicEvent event;
  int interval_time = 0;
};

}
}

#endif // NIERE_ALLTOBENICE_LOGIC_LOGIC_CONTEXT_H
