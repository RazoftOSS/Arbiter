#include "player.h"

#include "catch.hpp"

TEST_CASE("CSV Parsing: valid player", "") {
  auto player = libarbiter::Player::NewPlayer(
      "foo,2000", libarbiter::PlayerStringType::CSV);
  REQUIRE(player);
  CHECK(player->name() == "foo");
  CHECK(player->elo() == 2000);
  delete player;
}

TEST_CASE("CSV Parsing: not enough fields", "") {
  auto player =
      libarbiter::Player::NewPlayer("foo", libarbiter::PlayerStringType::CSV);
  REQUIRE(!player);
  delete player;
}

TEST_CASE("CSV Parsing: quoted fields", "") {
  auto player = libarbiter::Player::NewPlayer(
      "foo,\"2000\"", libarbiter::PlayerStringType::CSV);
  REQUIRE(player);
  CHECK(player->name() == "foo");
  CHECK(player->elo() == 2000);
  delete player;
}

TEST_CASE("CSV Parsing: quoted fields with delimiters inside", "") {
  auto player = libarbiter::Player::NewPlayer(
      "\"Dr. Foo, Ph.D.\",2000", libarbiter::PlayerStringType::CSV);
  REQUIRE(player);
  CHECK(player->name() == "Dr. Foo, Ph.D.");
  CHECK(player->elo() == 2000);
  delete player;
}

TEST_CASE("JSON Parsing: valid player", "") {
  auto player = libarbiter::Player::NewPlayer(
      "{\"name\":\"foo\", \"elo\":2000}", libarbiter::PlayerStringType::JSON);
  REQUIRE(player);
  CHECK(player->name() == "foo");
  CHECK(player->elo() == 2000);
  delete player;
}

TEST_CASE("JSON Parsing: not enough fields", "") {
  auto player = libarbiter::Player::NewPlayer(
      "{\"name\":\"foo\"}", libarbiter::PlayerStringType::JSON);
  REQUIRE(!player);
  delete player;
}

TEST_CASE("JSON Parsing: invalid elo", "") {
  auto player =
      libarbiter::Player::NewPlayer("{\"name\":\"foo\", \"elo\":\"bar\"}",
                                    libarbiter::PlayerStringType::JSON);
  REQUIRE(!player);
  delete player;
}
