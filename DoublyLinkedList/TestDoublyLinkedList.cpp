#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <string>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "DoublyLinkedList.hpp"
#include "TestUtils.hpp"

TEST_CASE("Items can be added to doublyLinkedList", "[prepend]") {
  GIVEN("An empty int list"){

    DoublyLinkedList<int> doublyLinkedList;
    REQUIRE(doublyLinkedList.size() == 0);

    WHEN("int 2 is prepended"){

      doublyLinkedList.prepend(2);

      THEN("List size is 1 and front returns 2"){

        REQUIRE(doublyLinkedList.size() == 1);
        REQUIRE(doublyLinkedList.front() == 2);
      }
    }
  }
}

TEST_CASE("Items can be removed from doublyLinkedList", "[removeFirst]") {
  GIVEN("An int list [3,4]"){

    DoublyLinkedList<int> doublyLinkedList;
    doublyLinkedList.prepend(4);
    doublyLinkedList.prepend(3);
    REQUIRE(doublyLinkedList.size() == 2);
    REQUIRE(doublyLinkedList.front() == 3);

    WHEN("first element is removed"){

      doublyLinkedList.removeFirst();

      THEN("List size is 1 and front returns 4"){

        REQUIRE(doublyLinkedList.size() == 1);
        REQUIRE(doublyLinkedList.front() == 4);
      }
    }
  }
}

TEST_CASE("DoublyLinkedList can be constructed from vector", "[constructor]") {
  GIVEN("An vector (1,2,3)"){

    std::vector<int> vector = {1,2,3};

    WHEN("LinedList is created"){

      DoublyLinkedList<int> doublyLinkedList(vector);

      THEN("List size is 3 and front returns 1"){

        REQUIRE(doublyLinkedList.size() == 3);
        REQUIRE(doublyLinkedList.front() == 1);
      }
    }
  }
}

TEST_CASE("DoublyLinkedList can be constructed from array", "[constructor]") {
  GIVEN("An array (1,2,3)"){

    std::array<int,3> array = {1,2,3};

    WHEN("LinedList is created"){

      DoublyLinkedList<int> doublyLinkedList(array);

      THEN("List size is 3 and front returns 1"){

        REQUIRE(doublyLinkedList.size() == 3);
        REQUIRE(doublyLinkedList.front() == 1);
      }
    }
  }
}

TEST_CASE("DoublyLinkedList can be compared", "[operator==]") {
  GIVEN("Two identical empty int lists"){

    DoublyLinkedList<int> doublyLinkedList;
    DoublyLinkedList<int> doublyLinkedList2;
    REQUIRE(doublyLinkedList.size() == 0);
    REQUIRE(doublyLinkedList2.size() == 0);

    WHEN("They are compared"){

      THEN("Result is true"){
        REQUIRE(doublyLinkedList == doublyLinkedList2);
      }
    }
  }
  GIVEN("Two identical int lists [1,2,3]"){

    std::array<int,3> array = {1,2,3};
    DoublyLinkedList<int> doublyLinkedList(array);
    DoublyLinkedList<int> doublyLinkedList2(array);
    REQUIRE(doublyLinkedList.size() == 3);
    REQUIRE(doublyLinkedList2.size() == 3);

    WHEN("They are compared"){

      THEN("Result is true"){
        REQUIRE(doublyLinkedList == doublyLinkedList2);
      }
    }
  }
  GIVEN("Two different int lists [1,2,{3 or 5}]"){

    std::array<int,3> array = {1,2,3};
    std::array<int,3> array2 = {1,2,5};
    DoublyLinkedList<int> doublyLinkedList(array);
    DoublyLinkedList<int> doublyLinkedList2(array2);
    REQUIRE(doublyLinkedList.size() == 3);
    REQUIRE(doublyLinkedList2.size() == 3);

    WHEN("They are compared"){

      THEN("Result is true"){
        REQUIRE_FALSE(doublyLinkedList == doublyLinkedList2);
      }
    }
  }
}

TEST_CASE("DoublyLinkedList can return reversed copy", "[makeReversed]") {
  GIVEN("An list(1,2,3)"){

    std::array<int,3> array = {1,2,3};
    DoublyLinkedList<int> doublyLinkedList(array);
    REQUIRE(doublyLinkedList.size() == 3);

    WHEN("DoublyLinkedList is reversed"){

      DoublyLinkedList<int> reversedDoublyLinkedList = doublyLinkedList.makeReversed();

      THEN("The result is a list(3,2,1)"){

        std::array<int,3> array = {3,2,1};
        DoublyLinkedList<int> expectedList(array);
        REQUIRE(reversedDoublyLinkedList.size() == 3);
        REQUIRE(reversedDoublyLinkedList == expectedList);
      }
    }
  }
}

TEST_CASE("DoublyLinkedList can be reversed in place", "[reverse]") {
  GIVEN("An list(1,2,3)"){

    std::array<int,3> array = {1,2,3};
    DoublyLinkedList<int> doublyLinkedList(array);
    REQUIRE(doublyLinkedList.size() == 3);

    WHEN("DoublyLinkedList is reversed"){

      doublyLinkedList.reverse();

      THEN("The result is a list(3,2,1)"){

        std::array<int,3> array = {3,2,1};
        DoublyLinkedList<int> expectedList(array);
        REQUIRE(doublyLinkedList.size() == 3);
        REQUIRE(doublyLinkedList == expectedList);
      }
    }
  }
}

TEST_CASE("DoublyLinkedList can be iterated", "[forEach]") {
  GIVEN("An list(1,2,3)"){

    std::array<int,3> array = {1,2,3};
    DoublyLinkedList<int> doublyLinkedList(array);
    REQUIRE(doublyLinkedList.size() == 3);

    WHEN("For each element incrementByOne function is called"){

      doublyLinkedList.forEach(incrementBy(2));

      THEN("The result is a list(2,3,4)"){

        std::array<int,3> array = {2,3,4};
        DoublyLinkedList<int> expectedList(array);
        REQUIRE(doublyLinkedList.size() == 3);
        REQUIRE(doublyLinkedList == expectedList);
      }
    }
  }
}

TEST_CASE("Items are moved to doublyLinkedList", "[emplaceFront]") {
  GIVEN("An empty ConstructorCounter list"){

    resetConstructorCounters();
    DoublyLinkedList<ConstructorCounter> doublyLinkedList;
    REQUIRE(doublyLinkedList.size() == 0);

    WHEN("An rvalue object is prepended"){

      doublyLinkedList.emplaceFront(std::move(ConstructorCounter()));

      THEN("List size is 1 and move constructor is called once"){

        REQUIRE(doublyLinkedList.size() == 1);
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

TEST_CASE("It is possible to iterate through doublyLinkedList", "[begin, end, Iterator]") {
  GIVEN("An int list (1,2,3)"){

    std::array<int,3> array = {1,2,3};
    DoublyLinkedList<int> doublyLinkedList(array);
    REQUIRE(doublyLinkedList.size() == 3);

    WHEN("Vector is constructed from doublyLinkedList values during for loop"){

      std::vector<int> result = {};

      for(int it : doublyLinkedList){
        it++;
      }
      for(int it : doublyLinkedList){
        result.emplace_back(it);
      }

      THEN("Resulting vector is 1,2,3"){

        std::vector<int> expectedVector = {1,2,3};
        REQUIRE(result == expectedVector);

      }
    }
  }
}

TEST_CASE("It is possible to iterate through doublyLinkedList and modify elements", "[begin, end, Iterator]") {
  GIVEN("An list(1,2,3)"){

    std::array<int,3> array = {1,2,3};
    DoublyLinkedList<int> doublyLinkedList(array);
    REQUIRE(doublyLinkedList.size() == 3);

    WHEN("For each element incrementByOne function is called"){

      for(auto& it : doublyLinkedList){
        it++;
      }

      THEN("The result is a list(2,3,4)"){

        std::array<int,3> array = {2,3,4};
        DoublyLinkedList<int> expectedList(array);
        REQUIRE(doublyLinkedList.size() == 3);
        REQUIRE(doublyLinkedList == expectedList);
      }
    }
  }
}

TEST_CASE("It is possible to remove doublyLinkedList's elements during iteration", "[removeIf]") {
  GIVEN("An list(2,2,2,1,2,2,2,3,2,4,5,6,2,2,2)"){

    std::array<int,15> array = {2,2,2,1,2,2,2,3,2,4,5,6,2,2,2};
    DoublyLinkedList<int> doublyLinkedList(array);
    REQUIRE(doublyLinkedList.size() == 15);

    WHEN("All elements eual to Two should be removed"){

      doublyLinkedList.removeIf(equalsTwo);

      THEN("The result is a list(1,3,4,5,6)"){

        std::array<int,5> array = {1,3,4,5,6};
        DoublyLinkedList<int> expectedList(array);
        REQUIRE(doublyLinkedList.size() == 5);
        REQUIRE(doublyLinkedList == expectedList);
      }
    }
  }
}

TEST_CASE("It is possible to print doublyLinkedList", "[operator<<]") {
  GIVEN("An list(1,3,4,5,6)"){

    std::array<int,5> array = {1,3,4,5,6};
    DoublyLinkedList<int> doublyLinkedList(array);

    WHEN("List is <<ed to std::ostream"){

      std::stringstream os;
      os << doublyLinkedList;

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
    DoublyLinkedList<int> doublyLinkedList(array);

    WHEN("Function contains is called for each number [0-9]"){

      THEN("The results are true for 1 3 4 5 6 and 7, and false for the rest"){

        REQUIRE(true  == doublyLinkedList.contains(1));
        REQUIRE(false == doublyLinkedList.contains(2));
        REQUIRE(true  == doublyLinkedList.contains(3));
        REQUIRE(true  == doublyLinkedList.contains(4));
        REQUIRE(true  == doublyLinkedList.contains(5));
        REQUIRE(true  == doublyLinkedList.contains(6));
        REQUIRE(true  == doublyLinkedList.contains(7));
        REQUIRE(false == doublyLinkedList.contains(8));
        REQUIRE(false == doublyLinkedList.contains(9));
      }
    }
  }
}

TEST_CASE("It is possible to remove duplicates", "[removeDuplicates]") {
  GIVEN("An list(1,1,3,4,4,5,7,6,6)"){

    std::array<int,9> array = {1,1,3,4,4,5,7,6,6};
    DoublyLinkedList<int> doublyLinkedList(array);

    WHEN("removeDuplicates function is called"){

      DoublyLinkedList<int> listWithoutDuplicates = doublyLinkedList.removeDuplicates();

      THEN("The result is a list(1,3,4,5,7,6)"){
        std::array<int,6> array = {1,3,4,5,7,6};
        DoublyLinkedList<int> expectedDoublyLinkedList(array);

        REQUIRE(expectedDoublyLinkedList == listWithoutDuplicates);
      }
    }
  }
}

TEST_CASE("It is possible to iterate in reverse order", "[rbegin, rend]") {
  GIVEN("An list(1,3,4,5,6)"){

    std::array<int,5> array = {1,3,4,5,6};
    DoublyLinkedList<int> doublyLinkedList(array);

    WHEN("List is iterated in reverse order"){

      std::string result = "";

      for(auto it = doublyLinkedList.rbegin(); it != doublyLinkedList.rend(); ++it){
        result += std::to_string(*it);
      }
      THEN("The result is a 65431"){

        REQUIRE(result == "65431");
      }
    }

    WHEN("List first element is removed"){

      doublyLinkedList.removeFirst();
      std::string result = "";

      for(auto it = doublyLinkedList.rbegin(); it != doublyLinkedList.rend(); ++it){
        result += std::to_string(*it);
      }
      THEN("The result is 65431"){

        REQUIRE(result == "6543");
      }

    }
  }
}

TEST_CASE("Items can be removed from the end of doublyLinkedList", "[removeLast]") {
  GIVEN("An int list [3,4]"){

    DoublyLinkedList<int> doublyLinkedList;
    doublyLinkedList.prepend(4);
    doublyLinkedList.prepend(3);
    REQUIRE(doublyLinkedList.size() == 2);
    REQUIRE(doublyLinkedList.front() == 3);

    WHEN("last element is removed"){

      doublyLinkedList.removeLast();

      THEN("List size is 1 and front returns 3"){

        REQUIRE(doublyLinkedList.size() == 1);
        REQUIRE(doublyLinkedList.front() == 3);
      }
    }
  }
}

TEST_CASE("Items can be added to the end of doublyLinkedList", "[append]") {
  GIVEN("An empty int list"){

    DoublyLinkedList<int> doublyLinkedList;
    REQUIRE(doublyLinkedList.size() == 0);

    WHEN("int 2 is prepended"){

      doublyLinkedList.append(2);
      doublyLinkedList.append(3);
      doublyLinkedList.append(4);

      THEN("List size is 3 front returns 2, and back returns 4"){

        REQUIRE(doublyLinkedList.size() == 3);
        REQUIRE(doublyLinkedList.front() == 2);
        REQUIRE(doublyLinkedList.back() == 4);
      }
    }
  }
}

TEST_CASE("It is possible to concatenate lists", "[operator +]") {
  GIVEN("Two lists (1,2,3) and (4,5,6)"){

    std::array<int,3> array = {1,2,3};
    DoublyLinkedList<int> doublyLinkedList(array);
    std::array<int,3> array2 = {4,5,6};
    DoublyLinkedList<int> doublyLinkedList2(array2);

    WHEN("the second is added to the first one"){

      DoublyLinkedList<int> result = doublyLinkedList + doublyLinkedList2;

      THEN("The result is a list(1,2,3,4,5,6)"){
        std::array<int,6> array = {1,2,3,4,5,6};
        DoublyLinkedList<int> expectedDoublyLinkedList(array);

        REQUIRE(expectedDoublyLinkedList == result);
      }
    }
  }
}

TEST_CASE("It is possible to concatenate regular and reversed lists", "[operator +]") {
  GIVEN("Two lists (1,2,3) and (4,5,6)"){

    std::array<int,3> array = {1,2,3};
    DoublyLinkedList<int> doublyLinkedList(array);
    std::array<int,3> array2 = {6,5,4};
    DoublyLinkedList<int> doublyLinkedList2(array2);

    WHEN("the second is reversed and added to the first one"){

      doublyLinkedList2.reverse();
      DoublyLinkedList<int> result = doublyLinkedList + doublyLinkedList2;

      THEN("The result is a list(1,2,3,4,5,6)"){
        std::array<int,6> array = {1,2,3,4,5,6};
        DoublyLinkedList<int> expectedDoublyLinkedList(array);

        REQUIRE(expectedDoublyLinkedList == result);
      }
    }
  }
}
