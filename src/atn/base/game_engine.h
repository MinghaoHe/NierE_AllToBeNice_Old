//
// Created by minghaohe on 2023/1/14.
//

#ifndef NIERE_ALLTOBENICE_BASE_GAME_ENGINE_H
#define NIERE_ALLTOBENICE_BASE_GAME_ENGINE_H

#include <set>
#include <unordered_map>

#include "atn/common/utility.h"
#include "atn/base/game_object.h"
#include "atn/base/window_context.h"
#include "atn/base/garbage_collection.h"
#include "atn/game/game_control.h"
#include "atn/logic/logic_engine.h"
#include "atn/render/render_engine.h"
#include "atn/physics/physics_engine.h"

namespace atn {
namespace base {

class GameEngine {
 public:
  ~GameEngine() noexcept;

  [[nodiscard]] static GameEngine &Instance();

 public:
  void Initialize(WindowContext *window_context);

  void Uninitalize();

  void Tick();

  void Sleep();

  void Start();

  void AddGlobalObjectCache(std::shared_ptr<Object> object_cache);

  void RemoveGlobalObjectCache(std::shared_ptr<Object> object_cache);

  void AddObject(std::shared_ptr<Object> object);

  void RemoveObject(std::shared_ptr<Object> object);

  template<class T>
  std::shared_ptr<T> NewObject(const std::string &object_tag) {
    return std::make_shared<T>((global_objects_cache_map_[object_tag]));
  }

  std::shared_ptr<logic::LogicEngine> GetLogic() { return logic_engine_; }

  std::shared_ptr<render::RenderEngine> GetRender() { return render_engine_; }

  void SetFps(int fps);

 private:
  WindowContext *window_context_;
  std::shared_ptr<logic::LogicEngine> logic_engine_;
  std::shared_ptr<render::RenderEngine> render_engine_;
  std::shared_ptr<physics::PhysicsEngine> physics_engine_;
  std::shared_ptr<game::GameControl> game_control_;
  std::shared_ptr<base::GarbageCollection> garbage_collection_;

  std::set<std::shared_ptr<base::Object>> objects_;
  std::unordered_map<std::string, std::shared_ptr<base::Object>> global_objects_cache_map_;

  int fps_;
  std::chrono::high_resolution_clock::time_point current_frame_start_;
  std::chrono::milliseconds current_tick_duration_;

  GameEngine();
  DISALLOW_COPY_AND_ASSIGN(GameEngine);
};

inline void AddGlobalObjectCache(std::shared_ptr<Object> object_cache) {
  GameEngine::Instance().AddGlobalObjectCache(object_cache);
}

inline void RemoveGlobalObjectCache(std::shared_ptr<Object> object_cache) {
  GameEngine::Instance().RemoveGlobalObjectCache(object_cache);
}

template<class T>
inline std::shared_ptr<T> NewObject(const std::string &object_tag) {
  return GameEngine::Instance().NewObject<T>(object_tag);
}

inline void AddObject(std::shared_ptr<Object> object) {
  GameEngine::Instance().AddObject(object);
}

inline void RemoveObject(std::shared_ptr<Object> object) {
  GameEngine::Instance().RemoveObject(object);
}

}
}


#endif // NIERE_ALLTOBENICE_BASE_GAME_ENGINE_H
