//
// Created by minghaohe on 2023/1/16.
//

#include "game_control.h"

#include <3rdparty/glm/gtc/matrix_transform.hpp>

#include "atn/base/game_engine.h"
#include "atn/game/pod.h"
#include "atn/game/pod_bullet.h"
#include "atn/game/enemy.h"
#include "atn/game/enemy_bullet.h"


namespace atn {
namespace game {

GameControl::GameControl(logic::LogicContext &logic_context, render::RenderContext &render_context)
        : logic_context_(logic_context), render_context_(render_context) {}

GameControl::~GameControl() {}

void GameControl::Initialize() {
  std::shared_ptr<Pod> pod = std::make_shared<Pod>();
  base::AddGlobalObjectCache(pod);
  std::shared_ptr<PodBullet> pod_bullet = std::make_shared<PodBullet>();
  base::AddGlobalObjectCache(pod_bullet);

  std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
  base::AddGlobalObjectCache(enemy);

  std::shared_ptr<EnemyBullet> enemy_bullet = std::make_shared<EnemyBullet>();
  base::AddGlobalObjectCache(enemy_bullet);

  // create game control thread
  std::thread(&GameControl::GameMain, this).detach();
}

void GameControl::Uninitialize() {}

void GameControl::Start() {
  std::unique_lock lck(lock_);
  cv_.notify_all();
}

void GameControl::GameMain() {
  std::unique_lock lck(lock_);
  cv_.wait(lck);
  std::shared_ptr<game::Pod> pod = base::NewObject<game::Pod>("pod");
  base::AddObject(pod);
  std::shared_ptr<game::Enemy> enemy = base::NewObject<game::Enemy>("enemy");
  enemy->SetEnemyState(20, 1.0f);
  enemy->SetText("Hello World", 0.0015f);
  enemy->SetEnemyTrace(EnemyTrace::MovementType::Moving, 0.001f, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
  enemy->SetEnemyAttackType(400, EnemyAttack::AttackType::Medium);
  base::AddObject(enemy);
}

}


}
