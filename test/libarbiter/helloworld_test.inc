#include "helloworld.h"

#include <string>

TEST_CASE("Hello World Test", "") {
  std::string helloworld = HelloWorld();
  CHECK(helloworld == "Hello World!");
}
