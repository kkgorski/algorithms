#pragma once

#include "LinkedList.hpp"

template<typename TYPE>
class Stack{
public:
  void push(TYPE item){
    list.prepend(item);
  }
  TYPE pop(){
    const TYPE popped = list.front();
    list.removeFirst();
    return popped;
  }
  TYPE peek(){
    return list.front();
  }
  unsigned size(){
    return list.size();
  }
private:
  LinkedList<TYPE> list;
};

