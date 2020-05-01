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
  TYPE operator*() const{
    return this->currentNode_->data();
  }
  TYPE& operator*(){
    return this->currentNode_->data();
  }
private:
  Node<TYPE>* currentNode_;
};

