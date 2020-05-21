#pragma once

#include "Node.hpp"
#include "Nodes.hpp"

template<typename TYPE>
class Nodes;

template<typename TYPE>
class Iterator{
public:
  explicit Iterator(Node<TYPE>* currentNode, const Nodes<TYPE>& nodes) : currentNode_(currentNode), nodes_(nodes){
    if(currentNode_){
      nextNode_ = nodes_.getFollowingNode(currentNode_);
    }
  }
  Iterator& operator++(){
    currentNode_ = nextNode_;
    if(nextNode_){
      nextNode_ = nodes_.getFollowingNode(nextNode_);
    }
    return *this;
  }
  Iterator operator++() const{
    return nextNode_;
  }
  bool operator==(Iterator other) const{
    return currentNode_ == other.currentNode_;
  }
  bool operator!=(Iterator other) const{
    return currentNode_ != other.currentNode_;
  }
protected:
  Node<TYPE>* currentNode_;
  Node<TYPE>* nextNode_;
  const Nodes<TYPE>& nodes_;
};

template<typename TYPE>
class ReverseIterator{
public:
  explicit ReverseIterator(Node<TYPE>* currentNode, const Nodes<TYPE>& nodes) : currentNode_(currentNode), nodes_(nodes){
    if(currentNode_){
      prevNode_ = nodes_.getPreceedingNode(currentNode_);
    }
  }
  ReverseIterator& operator++(){
    currentNode_ = prevNode_;
    if(prevNode_){
      prevNode_ = nodes_.getPreceedingNode(prevNode_);
    }
    return *this;
  }
  ReverseIterator operator++() const{
    return prevNode_;
  }
  bool operator==(ReverseIterator other) const{
    return currentNode_ == other.currentNode_;
  }
  bool operator!=(ReverseIterator other) const{
    return currentNode_ != other.currentNode_;
  }
protected:
  Node<TYPE>* currentNode_;
  Node<TYPE>* prevNode_;
  const Nodes<TYPE>& nodes_;
};

template<typename TYPE>
class DataIterator : public Iterator<TYPE>{
public:
  explicit DataIterator(Node<TYPE>* currentNode, const Nodes<TYPE>& nodes) : Iterator<TYPE>(currentNode, nodes) {}
  TYPE operator*() const{
    return this->currentNode_->data();
  }
  TYPE& operator*(){
    return this->currentNode_->data();
  }
};

template<typename TYPE>
class NodeIterator : public Iterator<TYPE>{
public:
  explicit NodeIterator(Node<TYPE>* currentNode, const Nodes<TYPE>& nodes) : Iterator<TYPE>(currentNode, nodes) {}
  Node<TYPE>* operator*(){
    return this->currentNode_;
  }
};

template<typename TYPE>
class ReverseDataIterator : public ReverseIterator<TYPE>{
public:
  explicit ReverseDataIterator(Node<TYPE>* currentNode, const Nodes<TYPE>& nodes) : ReverseIterator<TYPE>(currentNode, nodes) {}
  TYPE operator*() const{
    return this->currentNode_->data();
  }
  TYPE& operator*(){
    return this->currentNode_->data();
  }
};

