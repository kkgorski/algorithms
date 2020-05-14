#pragma once

template<typename TYPE>
class DoublyLinkedList
{
public:
  DoublyLinkedList(){}
  template<typename T>
  DoublyLinkedList(T iterable){
    (void) iterable;
  }
  ~DoublyLinkedList(){
  }
  unsigned size() const{
    return 0;
  }
  void prepend(TYPE item){
    (void) item;
  }
  void emplaceFront(TYPE&& item){
    (void) item;
  }
  void removeFirst(){
  }
  TYPE& front() const{
    TYPE* element = new TYPE();
    return (*element);
  }
  DoublyLinkedList reverse() const{//TODO implement non-const method, which reverses list in place
    return (*this);
  }
  bool operator==(const DoublyLinkedList& other) const{
    return false;
  }
  template<typename functionType>
  void forEach(functionType function){
    (void) function;
  }
  template<typename functionType>
  void removeIf(functionType function){
    (void) function;
  }
  TYPE* begin() const{
    return NULL;
  }
  TYPE* end() const{
    return NULL;
  }
  friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& doublyLinkedList){
    os << "()";
    return os;
  }
  bool contains(const TYPE& item) const{
    return false;
  }
  DoublyLinkedList removeDuplicates() const{ //TODO implement non-const method, which reverses list in place
    return *(this);
  }

};


