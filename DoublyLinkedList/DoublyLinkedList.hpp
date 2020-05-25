#pragma once

#include "Node.hpp"
#include "Nodes.hpp"
#include "utils.hpp"
#include "Iterator.hpp"

template<typename TYPE>
class DoublyLinkedList
{
public:
  DoublyLinkedList() : traverser_(new IForwardTraverser<TYPE>()), nodes_(NULL, NULL, traverser_), size_(0){}
  template<typename T>
  DoublyLinkedList(T iterable) : traverser_(new IForwardTraverser<TYPE>()), nodes_(NULL, NULL, traverser_), size_(0){
    for(auto value : reverse_wrap(iterable)) {
      prepend(value);
    }
  }
  ~DoublyLinkedList(){
    for(auto node: nodes_){
      delete node;
    }
    delete traverser_;
  }
  unsigned size() const{
    return size_;
  }
  void prepend(TYPE item){
    if(0 == size_){
      nodes_.head_ = traverser_->createNode(std::move(item), NULL, NULL);
      nodes_.tail_ = nodes_.head_;
    }else{
      Node<TYPE>* oldHead = nodes_.head_;
      nodes_.head_ = traverser_->createNode(std::move(item), NULL, nodes_.head_);
      traverser_->setPreceedingNode(oldHead, nodes_.head_);
    }
    size_++;
  }
  void emplaceFront(TYPE&& item){
    if(0 == size_){
      nodes_.head_ = traverser_->createNode(std::move(item), NULL, NULL);
      nodes_.tail_ = nodes_.head_;
    }else{
      Node<TYPE>* oldHead = nodes_.head_;
      nodes_.head_ = traverser_->createNode(std::move(item), NULL, nodes_.head_);
      traverser_->setPreceedingNode(oldHead, nodes_.head_);
    }
    size_++;
  }
  void removeFirst(){
    Node<TYPE>* headCopy = nodes_.head_;
    nodes_.head_ = traverser_->getFollowingNode(nodes_.head_);
    traverser_->setPreceedingNode(nodes_.head_, NULL);
    delete headCopy;
    size_--;
  }
  void removeLast(){
    Node<TYPE>* tailCopy = nodes_.tail_;
    nodes_.tail_ = traverser_->getPreceedingNode(nodes_.tail_);
    traverser_->setFollowingNode(nodes_.tail_, NULL);
    delete tailCopy;
    size_--;
  }
  TYPE& front() const{
    return nodes_.head_->data();
  }
  DoublyLinkedList makeReversed() const{
    DoublyLinkedList list;
    for(const auto& data : *this){
      list.prepend(data);
    }
    return list;
  }
  void reverse(){
    Node<TYPE>* tailCopy = nodes_.tail_;
    nodes_.tail_ = nodes_.head_;
    nodes_.head_ = tailCopy;
    delete traverser_;
    traverser_ = new IReverseTraverser<TYPE>();
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
      otherCurrentNode = other.traverser_->getFollowingNode(otherCurrentNode);
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
    return DataIterator<TYPE>(nodes_.head_, traverser_);
  }
  DataIterator<TYPE> end() const{
    return DataIterator<TYPE>(NULL, traverser_);
  }
  ReverseDataIterator<TYPE> rbegin() const{
    return ReverseDataIterator<TYPE>(nodes_.tail_, traverser_);
  }
  ReverseDataIterator<TYPE> rend() const{
    return ReverseDataIterator<TYPE>(NULL, traverser_);
  }
  friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& doublyLinkedList){
    os << "(";
    for(auto node: doublyLinkedList.nodes_){
      os << node->data();
      if(doublyLinkedList.traverser_->getFollowingNode(node)){
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
    DoublyLinkedList list;
    for(const auto& data : *this){
      if(!list.contains(data)){
        list.prepend(data);
      }
    }
    return list.makeReversed();
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
      Node<TYPE>* next = traverser_->getFollowingNode(node);
      Node<TYPE>* prev = traverser_->getPreceedingNode(node);
      traverser_->setPreceedingNode(next, prev);
      traverser_->setFollowingNode(prev, next);

      size_--;
      delete node;
    }
  }
  ITraverser<TYPE>* traverser_;
  Nodes<TYPE> nodes_;
  unsigned size_;
};

