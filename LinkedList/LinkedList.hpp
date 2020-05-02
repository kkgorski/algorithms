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
  void forEach(functionType function)
  {
    for(auto node: nodes_){
      function(node->data());
    }
  }
  DataIterator<TYPE> begin() const{
    return DataIterator<TYPE>(nodes_.head_);
  }
  DataIterator<TYPE> end() const{
    return DataIterator<TYPE>(NULL);
  }

private:
  Nodes nodes_;
  unsigned size_;
};

