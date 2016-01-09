#include "player_list.h"

#include <boost/uuid/uuid_generators.hpp>
#include "catch.hpp"

#include "player.h"

TEST_CASE("Add and remove player", "") {
  auto player = new libarbiter::Player("test", 2000);
  libarbiter::PlayerList list;
  REQUIRE(list.NumPlayers() == 0);

  list.Add(player);
  list.Remove(player->id());

  CHECK(list.NumPlayers() == 0);
}

TEST_CASE("Find existing player", "") {
  auto player = new libarbiter::Player("test", 2000);
  libarbiter::PlayerList list;

  list.Add(player);
  auto other = list.GetPlayer(player->id());
  REQUIRE(other != nullptr);
  CHECK(other->id() == player->id());
}

TEST_CASE("Find nonexistent player", "") {
  libarbiter::PlayerList list;

  auto iter = list.GetPlayer(boost::uuids::random_generator()());
  CHECK(iter == nullptr);
}
