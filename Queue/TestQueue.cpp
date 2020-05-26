#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "Queue.hpp"

TEST_CASE("Items can be added to queue", "[push, front]") {
  GIVEN("An empty int queue"){

    Queue<int> queue;
    REQUIRE(queue.isEmpty());

    WHEN("int 2 is pushed"){

      queue.push(2);

      THEN("Queue size is 1 and front returns 2"){

        REQUIRE(queue.size() == 1);
        REQUIRE(queue.front() == 2);
      }
    }
  }
}

