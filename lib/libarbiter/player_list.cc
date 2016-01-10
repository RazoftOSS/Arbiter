#include "player_list.h"

#include <fstream>
#include <mutex>

#include <boost/log/trivial.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
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

bool PlayerList::PopulateFromFile(std::string path, PlayerStringType type) {
  switch (type) {
    case PlayerStringType::CSV:
      return PopulateFromCSVFile(path);
    case PlayerStringType::JSON:
      return PopulateFromJSONFile(path);
  }
  return false;
}

bool PlayerList::PopulateFromCSVFile(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    BOOST_LOG_TRIVIAL(warning) << "File " << path << " failed to open.";
    return false;
  }
  std::string line;
  while (std::getline(file, line)) {
    Add(Player::NewPlayer(line, PlayerStringType::CSV));
  }
  return true;
}

bool PlayerList::PopulateFromJSONFile(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    BOOST_LOG_TRIVIAL(warning) << "File " << path << " failed to open.";
    return false;
  }
  boost::property_tree::ptree tree;
  boost::property_tree::read_json(file, tree);
  for (const auto player : tree.get_child("players")) {
    std::stringstream player_ss;
    boost::property_tree::write_json(player_ss, player.second, false);
    Add(Player::NewPlayer(player_ss.str(), PlayerStringType::JSON));
  }
  return true;
}

}  // namespace libarbiter
