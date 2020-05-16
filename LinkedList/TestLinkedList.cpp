#include <iostream>
#include <vector>
#include <array>
#include <utility>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
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

      THEN("List size is 1 and front returns 4"){

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

TEST_CASE("LinkedList can be iterated", "[forEach]") {
  GIVEN("An list(1,2,3)"){

    std::array<int,3> array = {1,2,3};
    LinkedList<int> linkedList(array);
    REQUIRE(linkedList.size() == 3);

    WHEN("For each element incrementByOne function is called"){

      linkedList.forEach(incrementBy(2));

      THEN("The result is a list(2,3,4)"){

        std::array<int,3> array = {2,3,4};
        LinkedList<int> expectedList(array);
        REQUIRE(linkedList.size() == 3);
        REQUIRE(linkedList == expectedList);
      }
    }
  }
}

TEST_CASE("Items are moved to linkedList", "[emplaceFront]") {
  GIVEN("An empty ConstructorCounter list"){

    resetConstructorCounters();
    LinkedList<ConstructorCounter> linkedList;
    REQUIRE(linkedList.size() == 0);

    WHEN("An rvalue object is prepended"){

      linkedList.emplaceFront(std::move(ConstructorCounter()));

      THEN("List size is 1 and move constructor is called once"){

        REQUIRE(linkedList.size() == 1);
        REQUIRE(defaultConstructorCalled == 1);
        REQUIRE(copyConstructorCalled == 0);
        REQUIRE(moveConstructorCalled == 1);
        REQUIRE(copyAssignmentOperatorCalled == 0);
        REQUIRE(moveAssignmentOperatorCalled == 0);
        REQUIRE(defaultDestructorCalled == 1);
      }
    }
  }
}

TEST_CASE("It is possible to iterate through linkedList", "[begin, end, Iterator]") {
  GIVEN("An int list (1,2,3)"){

    std::array<int,3> array = {1,2,3};
    LinkedList<int> linkedList(array);
    REQUIRE(linkedList.size() == 3);

    WHEN("Vector is constructed from linkedList values during for loop"){

      std::vector<int> result = {};

      for(int it : linkedList){
        it++;
      }
      for(int it : linkedList){
        result.emplace_back(it);
      }

      THEN("Resulting vector is 1,2,3"){

        std::vector<int> expectedVector = {1,2,3};
        REQUIRE(result == expectedVector);

      }
    }
  }
}

TEST_CASE("It is possible to iterate through linkedList and modify elements", "[begin, end, Iterator]") {
  GIVEN("An list(1,2,3)"){

    std::array<int,3> array = {1,2,3};
    LinkedList<int> linkedList(array);
    REQUIRE(linkedList.size() == 3);

    WHEN("For each element incrementByOne function is called"){

      for(auto& it : linkedList){
        it++;
      }

      THEN("The result is a list(2,3,4)"){

        std::array<int,3> array = {2,3,4};
        LinkedList<int> expectedList(array);
        REQUIRE(linkedList.size() == 3);
        REQUIRE(linkedList == expectedList);
      }
    }
  }
}

TEST_CASE("It is possible to remove linkedList's elements during iteration", "[removeIf]") {
  GIVEN("An list(2,2,2,1,2,2,2,3,2,4,5,6,2,2,2)"){

    std::array<int,15> array = {2,2,2,1,2,2,2,3,2,4,5,6,2,2,2};
    LinkedList<int> linkedList(array);
    REQUIRE(linkedList.size() == 15);

    WHEN("All elements eual to Two should be removed"){

      linkedList.removeIf(equalsTwo);

      THEN("The result is a list(1,3,4,5,6)"){

        std::array<int,5> array = {1,3,4,5,6};
        LinkedList<int> expectedList(array);
        REQUIRE(linkedList.size() == 5);
        REQUIRE(linkedList == expectedList);
      }
    }
  }
}

TEST_CASE("It is possible to print linkedList", "[operator<<]") {
  GIVEN("An list(1,3,4,5,6)"){

    std::array<int,5> array = {1,3,4,5,6};
    LinkedList<int> linkedList(array);

    WHEN("List is <<ed to std::ostream"){

      std::stringstream os;
      os << linkedList;

      THEN("The result is a list(1,3,4,5,6)"){
        std::stringstream expectedOs;
        expectedOs << "(1,3,4,5,6)";

        REQUIRE(os.str() == expectedOs.str());
      }
    }
  }
}

TEST_CASE("It is possible to check if list contains an element", "[contains]") {
  GIVEN("An list(1,1,3,4,4,5,7,6,6)"){

    std::array<int,9> array = {1,1,3,4,4,5,7,6,6};
    LinkedList<int> linkedList(array);

    WHEN("Function contains is called for each number [0-9]"){

      THEN("The results are true for 1 3 4 5 6 and 7, and false for the rest"){

        REQUIRE(true  == linkedList.contains(1));
        REQUIRE(false == linkedList.contains(2));
        REQUIRE(true  == linkedList.contains(3));
        REQUIRE(true  == linkedList.contains(4));
        REQUIRE(true  == linkedList.contains(5));
        REQUIRE(true  == linkedList.contains(6));
        REQUIRE(true  == linkedList.contains(7));
        REQUIRE(false == linkedList.contains(8));
        REQUIRE(false == linkedList.contains(9));
      }
    }
  }
}

TEST_CASE("It is possible to remove duplicates", "[removeDuplicates]") {
  GIVEN("An list(1,1,3,4,4,5,7,6,6)"){

    std::array<int,9> array = {1,1,3,4,4,5,7,6,6};
    LinkedList<int> linkedList(array);

    WHEN("removeDuplicates function is called"){

      LinkedList<int> listWithoutDuplicates = linkedList.removeDuplicates();

      THEN("The result is a list(1,3,4,5,7,6)"){
        std::array<int,6> array = {1,3,4,5,7,6};
        LinkedList<int> expectedLinkedList(array);

        REQUIRE(expectedLinkedList == listWithoutDuplicates);
      }
    }
  }
}

