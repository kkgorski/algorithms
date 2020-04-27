
template<typename TYPE>
class LinkedList
{
  class Node{
  public:
    Node(TYPE data, Node* next) : data_(data), next_(next) {}
    TYPE data() const{
      return data_;
    }
    Node* next() const{
      return next_;
    }

  private:
    TYPE data_;
    Node* next_;
  };

public:
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
    Node* nextNode;
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
    Node* newItem = new Node(item, head_);
    head_ = newItem;
    size_++;
  }
  void removeFirst(){
    Node* headCopy = head_;
    head_ = head_->next();
    delete headCopy;
    size_--;
  }
  TYPE front() const{
    return head_->data();
  }
  LinkedList reverse() const{
    LinkedList list;
    Node* currentNode = head_;
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
    Node* currentNode = head_;
    Node* otherCurrentNode = other.head_;

    while(currentNode){
      if(currentNode->data() != otherCurrentNode->data()){
        return false;
      }
      currentNode = currentNode->next();
      otherCurrentNode = otherCurrentNode->next();
    }

    return true;
  }

private:
  Node* head_;
  unsigned size_;
};

