#include "Node.hpp"
#include "Iterator.hpp"

template<typename TYPE>
class LinkedList
{
  struct Nodes{
    Nodes(Node<TYPE>* head) : head_(head) {}
    NodeIterator<TYPE> begin() const{
      return NodeIterator<TYPE>(head_);
    }
    NodeIterator<TYPE> end() const{
      return NodeIterator<TYPE>(NULL);
    }
    Node<TYPE>* head_;
  };
public:
  LinkedList() : nodes_(NULL), size_(0) {}
  template<typename T>
  LinkedList(T iterable) : nodes_(NULL), size_(0)
  {
    for (auto value : reverse_wrap(iterable)) {
      prepend(value);
    }
  }
  ~LinkedList()
  {
    for(auto node: nodes_){
      delete node;
    }
  }
  unsigned size() const{
    return size_;
  }
  void prepend(TYPE item){
    Node<TYPE>* newItem = new Node<TYPE>(std::move(item), nodes_.head_);
    nodes_.head_ = newItem;
    size_++;
  }
  void emplaceFront(TYPE&& item){
    Node<TYPE>* newItem = new Node<TYPE>(std::move(item), nodes_.head_);
    nodes_.head_ = newItem;
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
  LinkedList reverse() const{
    LinkedList list;
    for (const auto& data : *this){
      list.prepend(data);
    }
    return list;
  }
  bool operator==(const LinkedList& other) const{
    if(size_ != other.size_){
      return false;
    }
    Node<TYPE>* otherCurrentNode = other.nodes_.head_;
    for (const auto& data : *this){
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
    if(!nodes_.head_){
      return;
    }

    removeConsecutiveNodesIf(nodes_.head_, function);

    Node<TYPE>* node     = nodes_.head_;
    Node<TYPE>* nextNode = nodes_.head_->next();
    while(nextNode){
      removeConsecutiveNodesIf(nextNode, function);
      node->setNext(nextNode);
      if(nextNode){
        node = nextNode;
        nextNode = nextNode->next();
      }
    }
  }
  DataIterator<TYPE> begin() const{
    return DataIterator<TYPE>(nodes_.head_);
  }
  DataIterator<TYPE> end() const{
    return DataIterator<TYPE>(NULL);
  }
  friend std::ostream& operator<<(std::ostream& os, const LinkedList& linkedList){
    os << "(";
    for(auto node: linkedList.nodes_){
      os << node->data();
      if(node->next()){
        os << ",";
      }
    }
    os << ")";
    return os;
  }
  void removeDuplicates(){
  }

private:
  template<typename functionType>
  void removeConsecutiveNodesIf(Node<TYPE>*& node, functionType function){
    while(node && function(node->data())){
      Node<TYPE>* removableNode = node;
      node = node->next();
      delete removableNode;
      size_--;
    }
  }

  Nodes nodes_;
  unsigned size_;
};


