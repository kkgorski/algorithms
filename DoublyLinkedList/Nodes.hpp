#pragma once

#include "Node.hpp"
#include "Iterator.hpp"
#include "Traverser.hpp"

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

