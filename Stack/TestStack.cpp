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
    WHEN("int 5,8,9,7 are pushed, and pop() is called"){

      stack.push(5);
      stack.push(8);
      stack.push(9);
      stack.push(7);
      const int popped = stack.pop();

      THEN("Popped value is 7, stack size is 3 peek returns 9"){

        REQUIRE(popped == 7);
        REQUIRE(stack.peek() == 9);
        REQUIRE(stack.size() == 3);
      }
    }
  }
}

