#pragma once

#include "Node.hpp"
#include "Nodes.hpp"
#include "Traverser.hpp"

template<typename TYPE>
class Iterator{
public:
  explicit Iterator(Node<TYPE>* currentNode, ITraverser<TYPE>* const & traverser) : currentNode_(currentNode), traverser_(traverser){
    if(currentNode_){
      nextNode_ = traverser_->getFollowingNode(currentNode_);
    }
  }
  Iterator& operator++(){
    currentNode_ = nextNode_;
    if(nextNode_){
      nextNode_ = traverser_->getFollowingNode(nextNode_);
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
  ITraverser<TYPE>* const & traverser_;
};

template<typename TYPE>
class ReverseIterator{
public:
  explicit ReverseIterator(Node<TYPE>* currentNode, ITraverser<TYPE>* const & traverser) : currentNode_(currentNode), traverser_(traverser){
    if(currentNode_){
      prevNode_ = traverser_->getPreceedingNode(currentNode_);
    }
  }
  ReverseIterator& operator++(){
    currentNode_ = prevNode_;
    if(prevNode_){
      prevNode_ = traverser_->getPreceedingNode(prevNode_);
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
  ITraverser<TYPE>* const & traverser_;
};

template<typename TYPE>
class DataIterator : public Iterator<TYPE>{
public:
  explicit DataIterator(Node<TYPE>* currentNode, ITraverser<TYPE>* const & traverser) : Iterator<TYPE>(currentNode, traverser) {}
  TYPE operator*() const{
    return this->currentNode_->data;
  }
  TYPE& operator*(){
    return this->currentNode_->data;
  }
};

template<typename TYPE>
class NodeIterator : public Iterator<TYPE>{
public:
  explicit NodeIterator(Node<TYPE>* currentNode, ITraverser<TYPE>* const & traverser) : Iterator<TYPE>(currentNode, traverser) {}
  Node<TYPE>* operator*(){
    return this->currentNode_;
  }
};

template<typename TYPE>
class ReverseDataIterator : public ReverseIterator<TYPE>{
public:
  explicit ReverseDataIterator(Node<TYPE>* currentNode, ITraverser<TYPE>* const & traverser) : ReverseIterator<TYPE>(currentNode, traverser) {}
  TYPE operator*() const{
    return this->currentNode_->data;
  }
  TYPE& operator*(){
    return this->currentNode_->data;
  }
};

