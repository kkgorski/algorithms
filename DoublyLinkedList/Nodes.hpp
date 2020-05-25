#pragma once

#include "Node.hpp"
#include "Iterator.hpp"

template<typename TYPE>
class ITraverser{
public:
  virtual ~ITraverser(){}
  virtual Node<TYPE>* createNode(TYPE&& data, Node<TYPE>* prev, Node<TYPE>* next) const = 0;
  virtual Node<TYPE>* getFollowingNode(Node<TYPE>* Node) const = 0;
  virtual Node<TYPE>* getPreceedingNode(Node<TYPE>* Node) const = 0;
  virtual void setFollowingNode(Node<TYPE>* current, Node<TYPE>* next) const = 0;
  virtual void setPreceedingNode(Node<TYPE>* current, Node<TYPE>* prev) const = 0;
};

template<typename TYPE>
class IForwardTraverser : public ITraverser<TYPE>{
public:
  virtual ~IForwardTraverser(){}
  virtual Node<TYPE>* createNode(TYPE&& data, Node<TYPE>* prev, Node<TYPE>* next) const {
    return new Node<TYPE>(std::move(data), prev, next);
  }
  virtual Node<TYPE>* getFollowingNode(Node<TYPE>* node) const {
    return node->next;
  }
  virtual Node<TYPE>* getPreceedingNode(Node<TYPE>* node) const {
    return node->prev;
  }
  virtual void setFollowingNode(Node<TYPE>* current, Node<TYPE>* next) const {
    current->next = next;
  }
  virtual void setPreceedingNode(Node<TYPE>* current, Node<TYPE>* prev) const {
    current->prev = prev;
  }
};

template<typename TYPE>
class IReverseTraverser : public ITraverser<TYPE>{
public:
  virtual ~IReverseTraverser(){}
  virtual Node<TYPE>* createNode(TYPE&& data, Node<TYPE>* prev, Node<TYPE>* next) const {
    return new Node<TYPE>(std::move(data), next, prev);
  }
  virtual Node<TYPE>* getFollowingNode(Node<TYPE>* node) const {
    return node->prev;
  }
  virtual Node<TYPE>* getPreceedingNode(Node<TYPE>* node) const {
    return node->next;
  }
  virtual void setFollowingNode(Node<TYPE>* current, Node<TYPE>* next) const {
    current->prev = next;
  }
  virtual void setPreceedingNode(Node<TYPE>* current, Node<TYPE>* prev) const {
    current->next = prev;
  }
};

template<typename TYPE>
struct Nodes{
  Nodes(Node<TYPE>* head, Node<TYPE>* tail, ITraverser<TYPE>* const & traverser) : head_(head), tail_(tail), traverser_(traverser) {}
  NodeIterator<TYPE> begin() const{
    return NodeIterator<TYPE>(head_, traverser_);
  }
  NodeIterator<TYPE> end() const{
    return NodeIterator<TYPE>(NULL, traverser_);
  }

  Node<TYPE>* head_;
  Node<TYPE>* tail_;
  private:
  ITraverser<TYPE>* const & traverser_;
};

