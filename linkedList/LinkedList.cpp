#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

template<typename TYPE>
class LinkedList
{
  class Node{
  public:
    Node(TYPE data, Node* next) : data_(data), next_(next) {}

  private:
    TYPE data_;
    Node* next_;
  };

public:
  LinkedList() : head_(NULL), size_(0) {}
  unsigned size(){
    return size_;
  }
  void prepend(TYPE item){
    Node* newItem = new Node(item, head_);
    head_ = newItem;
    size_++;
  }

private:
  Node* head_;
  unsigned size_;
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

