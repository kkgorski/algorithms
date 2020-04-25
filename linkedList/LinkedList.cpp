#include <iostream>
#include <vector>
#include <array>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <utils.hpp>

template<typename TYPE>
class LinkedList
{
  class Node{
  public:
    Node(TYPE data, Node* next) : data_(data), next_(next) {}
    TYPE data() const{
      return data_;
    }
    Node* next() const{
      return next_;
    }

  private:
    TYPE data_;
    Node* next_;
  };

public:
  LinkedList() : head_(NULL), size_(0) {}
  template<typename T>
  LinkedList(T iterable) : head_(NULL), size_(0)
  {
    for (auto value : reverse(iterable)) {
      prepend(value);
    }
  }
  unsigned size() const{
    return size_;
  }
  void prepend(TYPE item){
    Node* newItem = new Node(item, head_);
    head_ = newItem;
    size_++;
  }
  void removeFirst(){
    Node* headCopy = head_;
    head_ = head_->next();
    delete headCopy;
    size_--;
  }
  TYPE front() const{
    return head_->data();
  }
  bool operator==(const LinkedList& linkedList) const{
    (void) linkedList;
    return false;
  }

private:
  Node* head_;
  unsigned size_;
};

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
}
