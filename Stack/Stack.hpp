#pragma once
template<typename TYPE>
class Stack{
public:
  void push(TYPE item){
    (void) item;
  }
  TYPE peek(){
    return TYPE();
  }
  unsigned size(){
    return 0;
  }
private:
};

