#include "Node.hpp"

template<typename TYPE>
class LinkedList
{
public:
  class Iterator{
  public:
    explicit Iterator(Node<TYPE>* currentNode) : currentNode_(currentNode) {}
    Iterator& operator++(){
      currentNode_ = currentNode_->next();
      return *this;
    }
    Iterator operator++() const{
      return currentNode_->next();
    }
    bool operator==(Iterator other) const{
      return currentNode_ == other.currentNode_;
    }
    bool operator!=(Iterator other) const{
      return currentNode_ != other.currentNode_;
    }
    TYPE operator*() const{
      return currentNode_->data();
    }
    TYPE& operator*(){
      return currentNode_->data();
    }
  private:
    Node<TYPE>* currentNode_;
  };

  LinkedList() : head_(NULL), size_(0) {}
  template<typename T>
  LinkedList(T iterable) : head_(NULL), size_(0)
  {
    for (auto value : reverse_wrap(iterable)) {
      prepend(value);
    }
  }
  ~LinkedList()
  {
    Node<TYPE>* nextNode;
    while(head_){
      nextNode = head_->next();
      delete head_;
      head_ = nextNode;
    }
  }
  unsigned size() const{
    return size_;
  }
  void prepend(TYPE item){
    Node<TYPE>* newItem = new Node<TYPE>(std::move(item), head_);
    head_ = newItem;
    size_++;
  }
  void emplaceFront(TYPE&& item){
    Node<TYPE>* newItem = new Node<TYPE>(std::move(item), head_);
    head_ = newItem;
    size_++;
  }
  void removeFirst(){
    Node<TYPE>* headCopy = head_;
    head_ = head_->next();
    delete headCopy;
    size_--;
  }
  TYPE& front() const{
    return head_->data();
  }
  LinkedList reverse() const{
    LinkedList list;
    Node<TYPE>* currentNode = head_;
    while(currentNode){
      list.prepend(currentNode->data());
      currentNode = currentNode->next();
    }
    return list;
  }
  bool operator==(const LinkedList& other) const{
    if(size_ != other.size_){
      return false;
    }
    Node<TYPE>* currentNode = head_;
    Node<TYPE>* otherCurrentNode = other.head_;

    while(currentNode){
      if(currentNode->data() != otherCurrentNode->data()){
        return false;
      }
      currentNode = currentNode->next();
      otherCurrentNode = otherCurrentNode->next();
    }

    return true;
  }
  template<typename functionType>
  void forEach(functionType function)
  {
    Node<TYPE>* currentNode = head_;
    while(currentNode){
      function(currentNode->data());
      currentNode = currentNode->next();
    }
  }
  Iterator begin() const{
    return Iterator(head_);
  }
  Iterator end() const{
    return Iterator(NULL);
  }

private:
  Node<TYPE>* head_;
  unsigned size_;
};

