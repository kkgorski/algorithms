#pragma once

template<typename TYPE>
class Node{
public:
  Node(TYPE&& data, Node* next) : data_(std::move(data)), next_(next) {}
  TYPE& data(){
    return data_;
  }
  Node* next() const{
    return next_;
  }
  void setNext(Node* node){
    next_ = node;
  }

private:
  TYPE data_;
  Node* next_;
};

