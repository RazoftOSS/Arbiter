#include "player_list.h"

#include <fstream>
#include <mutex>
#include <stdexcept>

#include <boost/log/trivial.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/uuid/uuid.hpp>

#include "player.h"
#include "util.h"

namespace libarbiter {

void PlayerList::Add(const Player& player) {
  std::lock_guard<std::mutex> lock(players_lock_);
  players_.emplace(player.id(), player);
}

void PlayerList::Remove(const boost::uuids::uuid& id) {
  std::lock_guard<std::mutex> lock(players_lock_);
  players_.erase(id);
}

const Player* PlayerList::GetPlayer(const boost::uuids::uuid& id) const {
  auto player_pair = players_.find(id);
  if (player_pair != players_.end()) {
    return &(player_pair->second);
  }
  return nullptr;
}

Player* PlayerList::GetMutablePlayer(const boost::uuids::uuid& id) {
  auto player_pair = players_.find(id);
  if (player_pair != players_.end()) {
    return &(player_pair->second);
  }
  return nullptr;
}

int PlayerList::NumPlayers() const { return players_.size(); }

void PlayerList::PopulateFromFile(std::string path, PlayerStringType type) {
  switch (type) {
    case PlayerStringType::CSV:
      PopulateFromCSVFile(path);
      break;
    case PlayerStringType::JSON:
      PopulateFromJSONFile(path);
      break;
  }
}

void PlayerList::PopulateFromCSVFile(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    BOOST_LOG_TRIVIAL(warning) << "File " << path << " failed to open.";
    throw FileNotFoundException("File " + path + " failed to open.");
  }
  std::string line;
  while (std::getline(file, line)) {
    Add(Player::FromCSV(line));
  }
}

void PlayerList::PopulateFromJSONFile(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    BOOST_LOG_TRIVIAL(warning) << "File " << path << " failed to open.";
    throw FileNotFoundException("File " + path + " failed to open.");
  }
  boost::property_tree::ptree tree;
  try {
    boost::property_tree::read_json(file, tree);
  } catch (std::exception&) {
    throw InvalidJSONException();
  }
  for (const auto player : tree.get_child("players")) {
    std::stringstream player_ss;
    boost::property_tree::write_json(player_ss, player.second, false);
    Add(Player::FromJSON(player_ss.str()));
  }
}

}  // namespace libarbiter
