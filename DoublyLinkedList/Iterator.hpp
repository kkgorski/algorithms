#pragma once

template<typename TYPE>
class Iterator{
public:
  explicit Iterator(Node<TYPE>* currentNode) : currentNode_(currentNode){
    if(currentNode_){
      nextNode_ = currentNode_->next();
    }
  }
  Iterator& operator++(){
    currentNode_ = nextNode_;
    if(nextNode_){
      nextNode_ = nextNode_->next();
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
};

template<typename TYPE>
class ReverseIterator{
public:
  explicit ReverseIterator(Node<TYPE>* currentNode) : currentNode_(currentNode){
    if(currentNode_){
      prevNode_ = currentNode_->prev();
    }
  }
  ReverseIterator& operator++(){
    currentNode_ = prevNode_;
    if(prevNode_){
			prevNode_ = prevNode_->prev();
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
};

template<typename TYPE>
class DataIterator : public Iterator<TYPE>{
public:
  explicit DataIterator(Node<TYPE>* currentNode) : Iterator<TYPE>(currentNode) {}
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
  explicit NodeIterator(Node<TYPE>* currentNode) : Iterator<TYPE>(currentNode) {}
  Node<TYPE>* operator*(){
    return this->currentNode_;
  }
};

template<typename TYPE>
class ReverseDataIterator : public ReverseIterator<TYPE>{
public:
  explicit ReverseDataIterator(Node<TYPE>* currentNode) : ReverseIterator<TYPE>(currentNode) {}
  TYPE operator*() const{
    return this->currentNode_->data();
  }
  TYPE& operator*(){
    return this->currentNode_->data();
  }
};

