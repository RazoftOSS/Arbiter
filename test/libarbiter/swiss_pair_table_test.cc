#include "swiss_pair_table.h"

#include "catch.hpp"

TEST_CASE("Basic iterator test", "") {
  libarbiter::pairing::SwissPairTable table;
  // Not using auto to confirm the namespaces work as intended.
  libarbiter::pairing::SwissPairTable::const_iterator begin = table.begin();
  libarbiter::pairing::SwissPairTable::const_iterator end = table.end();
  CHECK(begin == end);
}
