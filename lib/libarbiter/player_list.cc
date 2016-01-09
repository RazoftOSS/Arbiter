#include "player_list.h"

#include <mutex>

#include "player.h"

namespace libarbiter {

void PlayerList::Add(const Player& player) {
  std::lock_guard<std::mutex> lock(players_lock_);
  players_.emplace(player.id(), player);
}

void PlayerList::Remove(int id) {
  std::lock_guard<std::mutex> lock(players_lock_);
  players_.erase(id);
}

const Player* PlayerList::GetPlayer(int id) const {
  auto player_pair = players_.find(id);
  if (player_pair != players_.end()) {
    return &player_pair->second;
  }
  return nullptr;
}

Player* PlayerList::GetMutablePlayer(int id) {
  auto player_pair = players_.find(id);
  if (player_pair != players_.end()) {
    return &player_pair->second;
  }
  return nullptr;
}

int PlayerList::NumPlayers() const { return players_.size(); }

}  // namespace libarbiter
