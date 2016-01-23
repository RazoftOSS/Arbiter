#include "game.h"

#include "catch.hpp"

TEST_CASE("Constructor", "") {
  libarbiter::Player white("foo", 2000);
  libarbiter::Player black("bar", 2000);
  libarbiter::Game game(&white, &black);
  CHECK(*(game.white()) == white);
  CHECK(*(game.black()) == black);
}
