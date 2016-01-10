#include "player.h"

#include <iterator>
#include <sstream>
#include <string>

#include <boost/algorithm/string/replace.hpp>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/tokenizer.hpp>

namespace libarbiter {
namespace {

Player* NewPlayerCSV(std::string player_string) {
  // Because boost::tokenizer can't parse standard CSV quite correctly, we need
  // to mess with it a bit.
  // Replace \ with \\.
  boost::replace_all(player_string, "\\", "\\\\");
  // Replace a pair of quotes ("") with an escaped quote (\")
  boost::replace_all(player_string, "\"\"", "\\\"");

  boost::tokenizer<boost::escaped_list_separator<char>> tokenizer(
      player_string);
  if (std::distance(tokenizer.begin(), tokenizer.end()) != 2) {
    BOOST_LOG_TRIVIAL(warning) << "Player CSV data is of invalid length. Data: "
                               << player_string;
    return nullptr;
  }
  auto iter = tokenizer.begin();
  std::string player_name = *iter;
  iter++;
  int player_elo;
  try {
    player_elo = std::stoi(*iter);
  } catch (std::invalid_argument err) {
    BOOST_LOG_TRIVIAL(warning)
        << "Player CSV data contained invalid ELO. Data: " << player_string;
    return nullptr;
  }
  return new Player(player_name, player_elo);
}

Player* NewPlayerJSON(std::string player_string) {
  boost::property_tree::ptree tree;
  std::stringstream ss(player_string);
  boost::property_tree::read_json(ss, tree);
  std::string player_name = tree.get("name", "");
  int player_elo = tree.get("elo", -1);
  if (player_name == "" || player_elo == -1) {
    BOOST_LOG_TRIVIAL(warning)
        << "Player JSON data contained invalid or missing field. Data: "
        << player_string;
    return nullptr;
  }
  return new Player(player_name, player_elo);
}

}  // namespace

Player* Player::NewPlayer(std::string player_string, PlayerStringType type) {
  switch (type) {
    case PlayerStringType::CSV:
      return NewPlayerCSV(player_string);
    case PlayerStringType::JSON:
      return NewPlayerJSON(player_string);
  }
  return nullptr;
}

}  // namespace libarbiter
