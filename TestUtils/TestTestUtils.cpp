#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "TestUtils.hpp"

TEST_CASE("ConstructorCounter", "[all]") {
  GIVEN("Reset constructor counters"){

    resetConstructorCounters();

    WHEN("new ConstructorCounter object is made"){

      ConstructorCounter ctr;

      THEN("default constructor is called once"){

        REQUIRE(defaultConstructorCalled == 1);
        REQUIRE(copyConstructorCalled == 0);
        REQUIRE(moveConstructorCalled == 0);
        REQUIRE(copyAssignmentOperatorCalled == 0);
        REQUIRE(moveAssignmentOperatorCalled == 0);
        REQUIRE(defaultDestructorCalled == 0);
      }
    }
  }

  GIVEN("ConstructorCounter object"){

    ConstructorCounter ctr;
    resetConstructorCounters();

    WHEN("new ConstructorCounter object is made from previous one"){

      ConstructorCounter ctr2 = ctr;

      THEN("copy constructor is called once"){

        REQUIRE(defaultConstructorCalled == 0);
        REQUIRE(copyConstructorCalled == 1);
        REQUIRE(moveConstructorCalled == 0);
        REQUIRE(copyAssignmentOperatorCalled == 0);
        REQUIRE(moveAssignmentOperatorCalled == 0);
        REQUIRE(defaultDestructorCalled == 0);
      }
    }
  }

  GIVEN("ConstructorCounter object"){

    ConstructorCounter ctr;
    resetConstructorCounters();

    WHEN("new ConstructorCounter object is made from moved previous one"){

      ConstructorCounter ctr2 = std::move(ctr);

      THEN("move constructor is called once"){

        REQUIRE(defaultConstructorCalled == 0);
        REQUIRE(copyConstructorCalled == 0);
        REQUIRE(moveConstructorCalled == 1);
        REQUIRE(copyAssignmentOperatorCalled == 0);
        REQUIRE(moveAssignmentOperatorCalled == 0);
        REQUIRE(defaultDestructorCalled == 0);
      }
    }
  }

  GIVEN("Two ConstructorCounter objects"){

    ConstructorCounter ctr;
    ConstructorCounter ctr2;
    resetConstructorCounters();

    WHEN("new one object is assigned to the other"){

      ctr2 = ctr;

      THEN("move constructor is called once"){

        REQUIRE(defaultConstructorCalled == 0);
        REQUIRE(copyConstructorCalled == 0);
        REQUIRE(moveConstructorCalled == 0);
        REQUIRE(copyAssignmentOperatorCalled == 1);
        REQUIRE(moveAssignmentOperatorCalled == 0);
        REQUIRE(defaultDestructorCalled == 0);
      }
    }
  }

  GIVEN("Two ConstructorCounter objects"){

    ConstructorCounter ctr;
    ConstructorCounter ctr2;
    resetConstructorCounters();

    WHEN("new one object is moved to the other"){

      ctr2 = std::move(ctr);

      THEN("move assignmnet operator is called once"){

        REQUIRE(defaultConstructorCalled == 0);
        REQUIRE(copyConstructorCalled == 0);
        REQUIRE(moveConstructorCalled == 0);
        REQUIRE(copyAssignmentOperatorCalled == 0);
        REQUIRE(moveAssignmentOperatorCalled == 1);
        REQUIRE(defaultDestructorCalled == 0);
      }
    }
  }
}

