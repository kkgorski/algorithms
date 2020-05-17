#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "Stack.hpp"

TEST_CASE("Items can be added to stack", "[push]") {
  GIVEN("An empty int stack"){

    Stack<int> stack;
    REQUIRE(stack.size() == 0);

    WHEN("int 2 is pushed"){

      stack.push(2);

      THEN("Stack size is 1 and peek returns 2"){

        REQUIRE(stack.peek() == 2);
        REQUIRE(stack.size() == 1);
      }
    }
  }
}

