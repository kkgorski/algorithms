#pragma once

#include "Node.hpp"

template<typename TYPE>
class DoublyLinkedList
{
public:
  DoublyLinkedList() : head_(NULL), tail_(NULL), size_(0){}
  template<typename T>
  DoublyLinkedList(T iterable){
    (void) iterable;
  }
  ~DoublyLinkedList(){
  }
  unsigned size() const{
    return size_;
  }
  void prepend(TYPE item){
    head_ = new Node<TYPE>(std::move(item), NULL, head_);
    size_++;
  }
  void emplaceFront(TYPE&& item){
    (void) item;
  }
  void removeFirst(){
  }
  TYPE& front() const{
    return head_->data();
  }
  DoublyLinkedList reverse() const{//TODO implement non-const method, which reverses list in place
    return (*this);
  }
  bool operator==(const DoublyLinkedList& other) const{
    return false;
  }
  template<typename functionType>
  void forEach(functionType function){
    (void) function;
  }
  template<typename functionType>
  void removeIf(functionType function){
    (void) function;
  }
  TYPE* begin() const{
    return NULL;
  }
  TYPE* end() const{
    return NULL;
  }
  friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& doublyLinkedList){
    os << "()";
    return os;
  }
  bool contains(const TYPE& item) const{
    return false;
  }
  DoublyLinkedList removeDuplicates() const{ //TODO implement non-const method, which reverses list in place
    return *(this);
  }
private:
  Node<TYPE>* head_;
  Node<TYPE>* tail_;
  unsigned size_;
};

