#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

template<typename TYPE>
class LinkedList
{
};

TEST_CASE("Items can be added to linkedList", "[prepend]") {
  GIVEN("An empty int list"){

    LinkedList<int> linkedList;
    REQUIRE(linkedList.size() == 0);

    WHEN("An element is prepended"){

      linkedList.prepend(2);

      THEN("List size is increased"){

        REQUIRE(linkedList.size() == 1);
      }
    }
  }
}

