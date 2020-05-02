template<typename TYPE>
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
protected:
  Node<TYPE>* currentNode_;
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

