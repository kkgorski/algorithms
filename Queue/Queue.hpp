#pragma once

#include "DoublyLinkedList.hpp"

template<typename TYPE>
class Queue{
public:
  void push(TYPE item){
    list.prepend(item);
  }
  TYPE front() const{
    return list.front();
  }
  unsigned size() const{
    return list.size();
  }
  bool isEmpty() const{
    return (0 == list.size());
  }
private:
  DoublyLinkedList<TYPE> list;
};

