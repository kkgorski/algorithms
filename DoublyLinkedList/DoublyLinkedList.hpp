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
      return NodeIterator<TYPE>(NULL);
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
    if(0 == size_){
      nodes_.head_ = new Node<TYPE>(std::move(item), NULL, NULL);
      nodes_.tail_ = nodes_.head_;
    }else{
      Node<TYPE>* oldHead = nodes_.head_;
      nodes_.head_ = new Node<TYPE>(std::move(item), NULL, nodes_.head_);
      oldHead->setPrev(nodes_.head_);
    }
    size_++;
  }
  void emplaceFront(TYPE&& item){
    if(0 == size_){
      nodes_.head_ = new Node<TYPE>(std::move(item), NULL, NULL);
      nodes_.tail_ = nodes_.head_;
    }else{
      Node<TYPE>* oldHead = nodes_.head_;
      nodes_.head_ = new Node<TYPE>(std::move(item), NULL, nodes_.head_);
      oldHead->setPrev(nodes_.head_);
    }
    size_++;
  }
  void removeFirst(){
    Node<TYPE>* headCopy = nodes_.head_;
    nodes_.head_ = nodes_.head_->next();
    nodes_.head_->setPrev(NULL);
    delete headCopy;
    size_--;
  }
  void removeLast(){
    Node<TYPE>* tailCopy = nodes_.tail_;
    nodes_.tail_ = nodes_.tail_->prev();
    nodes_.tail_->setNext(NULL);
    delete tailCopy;
    size_--;
  }
  TYPE& front() const{
    return nodes_.head_->data();
  }
  DoublyLinkedList reverse() const{//TODO implement non-const method, which reverses list in place
    DoublyLinkedList list;
    for(const auto& data : *this){
      list.prepend(data);
    }
    return list;
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
    for(auto node: nodes_){
      function(node->data());
    }
  }
  template<typename functionType>
  void removeIf(functionType function){
    for(auto node: nodes_){
      if(function(node->data())){
        removeNode(node);
      }
    }
  }
  DataIterator<TYPE> begin() const{
    return DataIterator<TYPE>(nodes_.head_);
  }
  DataIterator<TYPE> end() const{
    return DataIterator<TYPE>(NULL);
  }
  ReverseDataIterator<TYPE> rbegin() const{
    return ReverseDataIterator<TYPE>(nodes_.tail_);
  }
  ReverseDataIterator<TYPE> rend() const{
    return ReverseDataIterator<TYPE>(NULL);
  }
  friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& doublyLinkedList){
    os << "(";
    for(auto node: doublyLinkedList.nodes_){
      os << node->data();
      if(node->next()){
        os << ",";
      }
    }
    os << ")";
    return os;
  }
  bool contains(const TYPE& item) const{
    for(const auto& data : *this){
      if(item == data){
        return true;
      }
    }
    return false;
  }
  DoublyLinkedList removeDuplicates() const{ //TODO implement non-const method, which reverses list in place
    return *(this);
  }
private:
  void removeNode(Node<TYPE>* node){
    if(0 == size_)
      return;
    if(nodes_.head_ == node){
      removeFirst();
    }else if(nodes_.tail_ == node){
      removeLast();
    }else{
      node->next()->setPrev(node->prev());
      node->prev()->setNext(node->next());
      size_--;
    }
  }
  Nodes nodes_;
  unsigned size_;
};

