#include "player_list.h"

#include <boost/uuid/uuid_generators.hpp>
#include "catch.hpp"

#include "player.h"

TEST_CASE("Add and remove player", "") {
  libarbiter::Player player("test", 2000);
  libarbiter::PlayerList list;
  REQUIRE(list.NumPlayers() == 0);

  list.Add(player);
  list.Remove(player.id());

  CHECK(list.NumPlayers() == 0);
}

TEST_CASE("Find existing player", "") {
  libarbiter::Player player("test", 2000);
  libarbiter::PlayerList list;

  list.Add(player);
  auto other = list.GetPlayer(player.id());
  REQUIRE(other != nullptr);
  CHECK(other->id() == player.id());
}

TEST_CASE("Find nonexistent player", "") {
  libarbiter::PlayerList list;

  auto iter = list.GetPlayer(boost::uuids::random_generator()());
  CHECK(iter == nullptr);
}

TEST_CASE("Parse valid CSV file", "") {
  libarbiter::PlayerList list;

  REQUIRE_NOTHROW(
      list.PopulateFromFile("./test/libarbiter/player_list_test.csv",
                            libarbiter::PlayerStringType::CSV));
  CHECK(list.NumPlayers() == 2);
}

TEST_CASE("Parse valid JSON file", "") {
  libarbiter::PlayerList list;

  REQUIRE_NOTHROW(
      list.PopulateFromFile("./test/libarbiter/player_list_test.json",
                            libarbiter::PlayerStringType::JSON));
  CHECK(list.NumPlayers() == 2);
}

TEST_CASE("Export CSV", "") {
  libarbiter::PlayerList list;
  list.Add(libarbiter::Player("foo", 2000));
  std::stringstream ss;
  list.ExportCSV(ss);
  std::string output;
  ss >> output;
  CHECK(output == "\"foo\",2000");
}

TEST_CASE("Export JSON", "") {
  libarbiter::PlayerList list;
  list.Add(libarbiter::Player("foo", 2000));
  std::stringstream ss;
  list.ExportJSON(ss);
  std::string output;
  ss >> output;
  CHECK(output == "{\"players\":[{\"name\":\"foo\",\"elo\":\"2000\"}]}");
}
