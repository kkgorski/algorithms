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

TEST_CASE("Items can be popped from queue", "[pop, back]") {
  GIVEN("An [2,3,4] int queue"){

    Queue<int> queue;
    REQUIRE(queue.isEmpty());
    queue.push(4);
    queue.push(3);
    queue.push(2);
    REQUIRE(queue.size() == 3);

    WHEN("pop is called"){

      queue.pop();

      THEN("Queue size is 2, front returns 2, and back returns 3"){

        REQUIRE(queue.size() == 2);
        REQUIRE(queue.front() == 2);
        REQUIRE(queue.back() == 3);
      }
    }
  }
}
