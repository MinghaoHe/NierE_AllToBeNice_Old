//
// Created by minghaohe on 2023/1/14.
//

#include "game_engine.h"
#include <thread>

namespace atn {
namespace base {

GameEngine::GameEngine() : fps_(30) {}

GameEngine::~GameEngine() noexcept {}

GameEngine &GameEngine::Instance() {
  static GameEngine instance;
  return instance;
}

void GameEngine::Initialize(WindowContext* window_context) {
  window_context_ = window_context;
  render_engine_ = std::make_shared<render::RenderEngine>(*window_context_, objects_, global_objects_cache_map_);
  logic_engine_ = std::make_shared<logic::LogicEngine>(*window_context_, objects_, global_objects_cache_map_);
  physics_engine_ = std::make_shared<physics::PhysicsEngine>(objects_);
  game_control_ = std::make_shared<game::GameControl>(logic_engine_->GetLogicContext(),
                                                      render_engine_->GetRenderContext());
  garbage_collection_ = std::make_shared<base::GarbageCollection>(objects_);

  render_engine_->InitGlobalRenderEnvironment();
  game_control_->Initialize();
  logic_engine_->InitLogic();
  render_engine_->InitRender();

  physics_engine_->InitPhysics();
  physics_engine_->AddCollisionRelation("pod_bullet", {"enemy", "enemy_bullet"});
}

void GameEngine::Uninitalize() {
  physics_engine_->UninitPhysics();
  render_engine_->UninitRender();
  logic_engine_->UninitLogic();
  game_control_->Uninitialize();
}

void GameEngine::Tick() {
  logic_engine_->GetLogicContext().interval_time = std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() - current_frame_start_).count();
  current_frame_start_ = std::chrono::high_resolution_clock::now();

  physics_engine_->Tick();
  logic_engine_->Tick();
  render_engine_->Tick();
  garbage_collection_->Tick();

  current_tick_duration_ = std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() - current_frame_start_);
}

void GameEngine::AddGlobalObjectCache(std::shared_ptr<Object> object_cache) {
  global_objects_cache_map_.insert(std::make_pair(object_cache->Tag(), object_cache));
}

void GameEngine::RemoveGlobalObjectCache(std::shared_ptr<Object> object_cache) {
  auto target = global_objects_cache_map_.find(object_cache->Tag());
  if (target != global_objects_cache_map_.end()) {
    global_objects_cache_map_.erase(target);
  }
}

void GameEngine::AddObject(std::shared_ptr<Object> object) {
  objects_.insert(object);
}

void GameEngine::RemoveObject(std::shared_ptr<Object> object) {
  object->RemoveCurrentObject();
}

void GameEngine::SetFps(int fps) {
  fps_ = fps;
}

void GameEngine::Sleep() {
  static std::chrono::milliseconds per_frame_time = std::chrono::milliseconds(1000 / fps_);
  // std::cout << current_tick_duration_.count() << std::endl;

  std::chrono::milliseconds sleep_time = per_frame_time - current_tick_duration_;
  if (sleep_time.count() > 0) {
    std::this_thread::sleep_for(sleep_time);
  }
}

void GameEngine::Start() {
  current_frame_start_ = std::chrono::high_resolution_clock::now();
  game_control_->Start();
}

}
}