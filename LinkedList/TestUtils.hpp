unsigned defaultConstructorCalled = 0;
unsigned copyConstructorCalled = 0;
unsigned moveConstructorCalled = 0;
unsigned copyAssignmentOperatorCalled = 0;
unsigned moveAssignmentOperatorCalled = 0;
unsigned defaultDestructorCalled = 0;

void resetConstructorCounters(){
  defaultConstructorCalled = 0;
  copyConstructorCalled = 0;
  moveConstructorCalled = 0;
  copyAssignmentOperatorCalled = 0;
  moveAssignmentOperatorCalled = 0;
  defaultDestructorCalled = 0;
}

class ConstructorCounter{
public:
  //default constructor
  ConstructorCounter(){
    defaultConstructorCalled++;
  }
  //copy constructor
  ConstructorCounter(const ConstructorCounter&){
    copyConstructorCalled++;
  }
  //move constructor
  ConstructorCounter(ConstructorCounter&&){
    moveConstructorCalled++;
  }
  //copy assignmenty operator
  ConstructorCounter& operator=(const ConstructorCounter&){
    copyAssignmentOperatorCalled++;
    return *this;
  }
  //move assignment operator
  ConstructorCounter& operator=(ConstructorCounter&&){
    moveAssignmentOperatorCalled++;
    return *this;
  }
  //destructor
  ~ConstructorCounter(){
    defaultConstructorCalled++;
  }
};

