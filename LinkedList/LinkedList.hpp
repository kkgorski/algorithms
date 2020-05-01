template<typename TYPE>
class LinkedList
{
  class Node{
  public:
    Node(TYPE&& data, Node* next) : data_(std::move(data)), next_(next) {}
    TYPE& data(){
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
  class Iterator{
  public:
    explicit Iterator(Node* currentNode) : currentNode_(currentNode) {}
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
    Node* currentNode_;
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
    Node* newItem = new Node(std::move(item), head_);
    head_ = newItem;
    size_++;
  }
  void emplaceFront(TYPE&& item){
    Node* newItem = new Node(std::move(item), head_);
    head_ = newItem;
    size_++;
  }
  void removeFirst(){
    Node* headCopy = head_;
    head_ = head_->next();
    delete headCopy;
    size_--;
  }
  TYPE& front() const{
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
  template<typename functionType>
  void forEach(functionType function)
  {
    Node* currentNode = head_;
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
  Node* head_;
  unsigned size_;
};

