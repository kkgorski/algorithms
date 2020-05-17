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
  Node<TYPE>* prev(){
    return prev_;
  }
  void setPrev(Node<TYPE>* prev){
    prev_ = prev;
  }

private:
  TYPE data_;
  Node<TYPE>* prev_;
  Node<TYPE>* next_;
};

