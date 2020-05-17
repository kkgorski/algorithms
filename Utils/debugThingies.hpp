// inside doubly linked list class
// TODO introduce debug mode, with printNodes function for each data structure

void printListNodes() const{
  std::cout << std::endl << std::endl;

  std::cout << "current size: " << size_;
  std::cout << " head: " << nodes_.head_->data();
  std::cout << " tail: " << nodes_.tail_->data()<< std::endl;
  for(auto node: nodes_){
    std::cout << "current node: " << node->data();

    if(node->next()){
      std::cout  << " next: " << node->next()->data();
    }
    else{
      std::cout  << " next: " << "NULL";
    }
    if(node->prev()){
      std::cout  << " prev " << node->prev()->data();;
    }
    else{
      std::cout  << " prev: " << "NULL";
    }
    std::cout << std::endl;
  }

  Node<TYPE> * node = nodes_.tail_;
  std::cout << "tail: " << node->data();
  if(node->next()){
    std::cout  << " next: " << node->next()->data();
  }
  else{
    std::cout  << " next: " << "NULL";
  }
  if(node->prev()){
    std::cout  << " prev " << node->prev()->data();;
  }
  else{
    std::cout  << " prev: " << "NULL";
  }
  std::cout << std::endl;
  node = nodes_.head_;
  std::cout << "head: " << node->data();
  if(node->next()){
    std::cout  << " next: " << node->next()->data();
  }
  else{
    std::cout  << " next: " << "NULL";
  }
  if(node->prev()){
    std::cout  << " prev " << node->prev()->data();;
  }
  else{
    std::cout  << " prev: " << "NULL";
  }
  std::cout << std::endl;
}
