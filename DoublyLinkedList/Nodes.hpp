#pragma once

#include "Node.hpp"
#include "Iterator.hpp"

template<typename TYPE>
class Nodes{
private:

  static Node<TYPE>* createNodeRegular(TYPE&& data, Node<TYPE>* prev, Node<TYPE>* next){
    return new Node<TYPE>(std::move(data), prev, next);
  }
  static Node<TYPE>* getFollowingNodeRegular(Node<TYPE>* node){
    return node->next();
  }
  static Node<TYPE>* getPreceedingNodeRegular(Node<TYPE>* node){
    return node->prev();
  }
  static void setFollowingNodeRegular(Node<TYPE>* current, Node<TYPE>* next){
    current->setNext(next);
  }
  static void setPreceedingNodeRegular(Node<TYPE>* current, Node<TYPE>* prev){
    current->setPrev(prev);
  }


  static Node<TYPE>* createNodeReversed(TYPE&& data, Node<TYPE>* prev, Node<TYPE>* next){
    return new Node<TYPE>(std::move(data), next, prev);
  }
  static Node<TYPE>* getFollowingNodeReversed(Node<TYPE>* node){
    return node->prev();
  }
  static Node<TYPE>* getPreceedingNodeReversed(Node<TYPE>* node){
    return node->next();
  }
  static void setFollowingNodeReversed(Node<TYPE>* current, Node<TYPE>* next){
    current->setPrev(next);
  }
  static void setPreceedingNodeReversed(Node<TYPE>* current, Node<TYPE>* prev){
    current->setNext(prev);
  }
public:

  Nodes(Node<TYPE>* head, Node<TYPE>* tail):
    createNode(createNodeRegular),
    getFollowingNode(getFollowingNodeRegular),
    getPreceedingNode(getPreceedingNodeRegular),
    setFollowingNode(setFollowingNodeRegular),
    setPreceedingNode(setPreceedingNodeRegular),
    head_(head),
    tail_(tail) {}
  NodeIterator<TYPE> begin() const{
    return NodeIterator<TYPE>(head_, *this);
  }
  NodeIterator<TYPE> end() const{
    return NodeIterator<TYPE>(NULL, *this);
  }
  void reverse(){
    createNode = createNodeReversed;
    getFollowingNode = getFollowingNodeReversed;
    getPreceedingNode = getPreceedingNodeReversed;
    setFollowingNode = setFollowingNodeReversed;
    setPreceedingNode = setPreceedingNodeReversed;
  }

  Node<TYPE>* (* createNode)(TYPE&& data, Node<TYPE>* prev, Node<TYPE>* next);
  Node<TYPE>* (* getFollowingNode)(Node<TYPE>* Node);
  Node<TYPE>* (* getPreceedingNode)(Node<TYPE>* Node);
  void (* setFollowingNode)(Node<TYPE>* current, Node<TYPE>* next);
  void (* setPreceedingNode)(Node<TYPE>* current, Node<TYPE>* prev);

  Node<TYPE>* head_;
  Node<TYPE>* tail_;
};
