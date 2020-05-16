#pragma once

#include "Node.hpp"
#include "utils.hpp"
#include "Iterator.hpp"

template<typename TYPE>
class DoublyLinkedList
{
  struct Nodes{
    Nodes(Node<TYPE>* head, Node<TYPE>* tail) : head_(head), tail_(tail) {}
    NodeIterator<TYPE> begin() const{
      return NodeIterator<TYPE>(head_);
    }
    NodeIterator<TYPE> end() const{
      return NodeIterator<TYPE>(tail_);
    }
		Node<TYPE>* head_;
		Node<TYPE>* tail_;
  };
public:
  DoublyLinkedList() : nodes_(NULL, NULL), size_(0){}
  template<typename T>
  DoublyLinkedList(T iterable) : nodes_(NULL, NULL), size_(0){
    for(auto value : reverse_wrap(iterable)) {
      prepend(value);
    }
  }
  ~DoublyLinkedList(){
  }
  unsigned size() const{
    return size_;
  }
  void prepend(TYPE item){
    nodes_.head_ = new Node<TYPE>(std::move(item), NULL, nodes_.head_);
    size_++;
  }
  void emplaceFront(TYPE&& item){
    nodes_.head_ = new Node<TYPE>(std::move(item), NULL, nodes_.head_);
    size_++;
  }
  void removeFirst(){
    Node<TYPE>* headCopy = nodes_.head_;
    nodes_.head_ = nodes_.head_->next();
    delete headCopy;
    size_--;
  }
  TYPE& front() const{
    return nodes_.head_->data();
  }
  DoublyLinkedList reverse() const{//TODO implement non-const method, which reverses list in place
    return (*this);
  }
  bool operator==(const DoublyLinkedList& other) const{
    if(size_ != other.size_){
      return false;
    }
    Node<TYPE>* otherCurrentNode = other.nodes_.head_;
    for(const auto& data : *this){
      if(data != otherCurrentNode->data()){
        return false;
      }
      otherCurrentNode = otherCurrentNode->next();
    }
    return true;
  }
  template<typename functionType>
  void forEach(functionType function){
    (void) function;
  }
  template<typename functionType>
  void removeIf(functionType function){
    (void) function;
  }
  DataIterator<TYPE> begin() const{
    return DataIterator<TYPE>(nodes_.head_);
  }
  DataIterator<TYPE> end() const{
    return DataIterator<TYPE>(NULL);
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
  Nodes nodes_;
  unsigned size_;
};

