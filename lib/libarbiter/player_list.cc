#include "player_list.h"

#include <mutex>

#include <boost/uuid/uuid.hpp>

#include "player.h"

namespace libarbiter {

void PlayerList::Add(Player* player) {
  std::lock_guard<std::mutex> lock(players_lock_);
  players_.emplace(player->id(), std::unique_ptr<Player>(player));
}

void PlayerList::Remove(boost::uuids::uuid id) {
  std::lock_guard<std::mutex> lock(players_lock_);
  players_.erase(id);
}

const Player* PlayerList::GetPlayer(boost::uuids::uuid id) const {
  auto player_pair = players_.find(id);
  if (player_pair != players_.end()) {
    return player_pair->second.get();
  }
  return nullptr;
}

Player* PlayerList::GetMutablePlayer(boost::uuids::uuid id) {
  auto player_pair = players_.find(id);
  if (player_pair != players_.end()) {
    return player_pair->second.get();
  }
  return nullptr;
}

int PlayerList::NumPlayers() const { return players_.size(); }

}  // namespace libarbiter
