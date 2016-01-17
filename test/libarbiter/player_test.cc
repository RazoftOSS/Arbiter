#include "player.h"

#include "catch.hpp"

TEST_CASE("CSV Parsing: valid player", "") {
  REQUIRE_NOTHROW(libarbiter::Player::FromCSV("foo,2000"));
  auto player = libarbiter::Player::FromCSV("foo,2000");
  CHECK(player.name() == "foo");
  CHECK(player.elo() == 2000);
}

TEST_CASE("CSV Parsing: not enough fields", "") {
  REQUIRE_THROWS(libarbiter::Player::FromCSV("foo"));
}

TEST_CASE("CSV Parsing: quoted fields", "") {
  REQUIRE_NOTHROW(libarbiter::Player::FromCSV("foo,\"2000\""));
  auto player = libarbiter::Player::FromCSV("foo,\"2000\"");
  CHECK(player.name() == "foo");
  CHECK(player.elo() == 2000);
}

TEST_CASE("CSV Parsing: quoted fields with delimiters inside", "") {
  REQUIRE_NOTHROW(libarbiter::Player::FromCSV("\"Dr. Foo, Ph.D.\",2000"));
  auto player = libarbiter::Player::FromCSV("\"Dr. Foo, Ph.D.\",2000");
  CHECK(player.name() == "Dr. Foo, Ph.D.");
  CHECK(player.elo() == 2000);
}

TEST_CASE("JSON Parsing: valid player", "") {
  REQUIRE_NOTHROW(
      libarbiter::Player::FromJSON("{\"name\":\"foo\", \"elo\":2000}"));
  auto player =
      libarbiter::Player::FromJSON("{\"name\":\"foo\", \"elo\":2000}");
  CHECK(player.name() == "foo");
  CHECK(player.elo() == 2000);
}

TEST_CASE("JSON Parsing: not enough fields", "") {
  REQUIRE_THROWS(libarbiter::Player::FromJSON("{\"name\":\"foo\"}"));
}

TEST_CASE("JSON Parsing: invalid elo", "") {
  REQUIRE_THROWS(
      libarbiter::Player::FromJSON("{\"name\":\"foo\", \"elo\":\"bar\"}"));
}

TEST_CASE("CSV Export: no quotes in name", "") {
  libarbiter::Player player("foo", 2000);
  CHECK(player.ExportCSV() == "\"foo\",2000");
}

TEST_CASE("CSV Export: quotes in name", "") {
  libarbiter::Player player("Foo \"Bar\" Baz", 2000);
  CHECK(player.ExportCSV() == "\"Foo \"\"Bar\"\" Baz\",2000");
}

TEST_CASE("JSON Export", "") {
  libarbiter::Player player("foo", 2000);
  boost::property_tree::ptree expected;
  expected.add("name", "foo");
  expected.add("elo", 2000);
  CHECK(player.ExportJSON() == expected);
}
