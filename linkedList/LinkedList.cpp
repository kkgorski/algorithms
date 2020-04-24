#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

template<typename TYPE>
class LinkedList
{
  class Node{
  public:
    Node(TYPE data, Node* next) : data_(data), next_(next) {}
    TYPE data(){
      return data_;
    }

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
  TYPE front(){
    return head_->data();
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

