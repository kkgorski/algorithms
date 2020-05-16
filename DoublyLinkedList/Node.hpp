#pragma once

template<typename TYPE>
class Node{
public:
  Node(TYPE&& data, Node* prev, Node* next) : data_(std::move(data)), prev_(prev), next_(next) {}
  TYPE& data(){
    return data_;
  }
  Node<TYPE>* next(){
    return next_;
  }

private:
  TYPE data_;
  Node<TYPE>* prev_;
  Node<TYPE>* next_;
};

