#include <iostream>
#include <vector>
#include <array>
#include <utility>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <utils.hpp>
#include "LinkedList.hpp"
#include "TestUtils.hpp"

TEST_CASE("Items can be added to linkedList", "[prepend]") {
  GIVEN("An empty int list"){

    LinkedList<int> linkedList;
    REQUIRE(linkedList.size() == 0);

    WHEN("int 2 is prepended"){

      linkedList.prepend(2);

      THEN("List size is 1 and front returns 2"){

        REQUIRE(linkedList.size() == 1);
        REQUIRE(linkedList.front() == 2);
      }
    }
  }
}

TEST_CASE("Items can be removed from linkedList", "[removeFirst]") {
  GIVEN("An int list [3,4]"){

    LinkedList<int> linkedList;
    linkedList.prepend(4);
    linkedList.prepend(3);
    REQUIRE(linkedList.size() == 2);
    REQUIRE(linkedList.front() == 3);

    WHEN("first element is removed"){

      linkedList.removeFirst();

      THEN("List size is 1 and front returns 2"){

        REQUIRE(linkedList.size() == 1);
        REQUIRE(linkedList.front() == 4);
      }
    }
  }
}

TEST_CASE("LinkedList can be constructed from vector", "[constructor]") {
  GIVEN("An vector (1,2,3)"){

    std::vector<int> vector = {1,2,3};

    WHEN("LinedList is created"){

      LinkedList<int> linkedList(vector);

      THEN("List size is 3 and front returns 1"){

        REQUIRE(linkedList.size() == 3);
        REQUIRE(linkedList.front() == 1);
      }
    }
  }
}

TEST_CASE("LinkedList can be constructed from array", "[constructor]") {
  GIVEN("An array (1,2,3)"){

    std::array<int,3> array = {1,2,3};

    WHEN("LinedList is created"){

      LinkedList<int> linkedList(array);

      THEN("List size is 3 and front returns 1"){

        REQUIRE(linkedList.size() == 3);
        REQUIRE(linkedList.front() == 1);
      }
    }
  }
}

TEST_CASE("LinkedList can be compared", "[operator==]") {
  GIVEN("Two identical empty int lists"){

    LinkedList<int> linkedList;
    LinkedList<int> linkedList2;
    REQUIRE(linkedList.size() == 0);
    REQUIRE(linkedList2.size() == 0);

    WHEN("They are compared"){

      THEN("Result is true"){
        REQUIRE(linkedList == linkedList2);
      }
    }
  }
  GIVEN("Two identical int lists [1,2,3]"){

    std::array<int,3> array = {1,2,3};
    LinkedList<int> linkedList(array);
    LinkedList<int> linkedList2(array);
    REQUIRE(linkedList.size() == 3);
    REQUIRE(linkedList2.size() == 3);

    WHEN("They are compared"){

      THEN("Result is true"){
        REQUIRE(linkedList == linkedList2);
      }
    }
  }
  GIVEN("Two different int lists [1,2,{3 or 5}]"){

    std::array<int,3> array = {1,2,3};
    std::array<int,3> array2 = {1,2,5};
    LinkedList<int> linkedList(array);
    LinkedList<int> linkedList2(array2);
    REQUIRE(linkedList.size() == 3);
    REQUIRE(linkedList2.size() == 3);

    WHEN("They are compared"){

      THEN("Result is true"){
        REQUIRE_FALSE(linkedList == linkedList2);
      }
    }
  }
}

TEST_CASE("LinkedList can be reversed", "[reverse]") {
  GIVEN("An list(1,2,3)"){

    std::array<int,3> array = {1,2,3};
    LinkedList<int> linkedList(array);
    REQUIRE(linkedList.size() == 3);

    WHEN("LinkedList is reversed"){

      LinkedList<int> reversedLinkedList = linkedList.reverse();

      THEN("The result is a list(3,2,1)"){

        std::array<int,3> array = {3,2,1};
        LinkedList<int> expectedList(array);
        REQUIRE(reversedLinkedList.size() == 3);
        REQUIRE(reversedLinkedList == expectedList);
      }
    }
  }
}

// This may seem irrelevant to linkedList but I wanted to have one test binary, at least for now
// It will be needed for next UTs
// TODO move to some general test utils
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

