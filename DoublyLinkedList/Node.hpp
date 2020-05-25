#pragma once

template<typename TYPE>
struct Node{
  Node(TYPE&& dataArg, Node* prevArg, Node* nextArg) : data(std::move(dataArg)), prev(prevArg), next(nextArg) {}

  TYPE data;
  Node<TYPE>* prev;
  Node<TYPE>* next;
};

