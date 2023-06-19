#include <iostream>
#include <algorithm>
#include <list>

template<class U> 
class List;

template<class T> 
class Link {
  public:
    Link() = default;
    ~Link() = default;
    T getValue() {
      return value;
    }

    Link<T>* getNext() {
      return nextPtr;
    }
    Link<T>* getPrev() {
      return prevPtr;
    }

  private:
    Link<T>* nextPtr = nullptr;
    Link<T>* prevPtr = nullptr;
    T value;
  
  friend class List<T>;
};

template<class T>
class List {
  public:
    List() = default;
    ~List() = default;
    Link<T>* firstPtr = nullptr;
    Link<T>* lastPtr = nullptr;

    void addElem(T val);
    void remElem(T val);
    void showValue(Link<T>* elem) {
       while (elem) {
        std::cout << elem->getValue() << " ";
        elem = elem->getPrev();
      }
      // std::cout << elem->getValue();
      return;
    }
    
    friend std::ostream& operator<<(std::ostream& os, List<T>& list) {
      Link<T>* elem = list.lastPtr;
      while (elem) {
        os << elem->getValue() << " ";
        elem = elem->getPrev();
      }
      return os;
    }

  friend class Link<T>;
};

template<class T>
void List<T> :: addElem(T val) {
  Link<T>* tmp = new Link<T>;
  Link<T>* cur = firstPtr;

  tmp->value = val;
  if (!cur) {
    firstPtr = tmp;
    lastPtr = tmp;
    return;
  }
  while (cur) {
    std::cout << cur->value << " ";
    if (cur->value < tmp->value &&
    cur->nextPtr == nullptr) {
      cur->nextPtr = tmp;
      tmp->prevPtr = cur;
      lastPtr = tmp;
      return;
    }
    else if (cur->value < tmp->value &&
    cur->nextPtr->value > tmp->value) {
      tmp->nextPtr = cur->nextPtr;
      tmp->prevPtr = cur;
      cur->nextPtr->prevPtr = tmp;
      cur->nextPtr = tmp;
      return;
    }
    cur = cur->nextPtr;
  }
}

template<class T>
void List<T> :: remElem(T val) {
  Link<T>* cur = firstPtr;

  while (cur) {
    if (cur->value == val) {
      if (cur->nextPtr) {
        cur->nextPtr->prevPtr = cur->prevPtr;
        cur->prevPtr->nextPtr = cur->nextPtr;
      } else {
        lastPtr = cur->prevPtr;
      }

      if (cur->prevPtr) {
        cur->prevPtr->nextPtr = cur->nextPtr;
      } else {
        firstPtr = cur->prevPtr;
      }
      delete cur;
      return;
    }
    cur = cur->nextPtr;
  }

}


int main() {
  List<double> list;
  double elem;
  int M, N;

  std::cout<<"wprwoadz liczbe elementow, a nastepnie wprowadz liczby:";
  std::cin >> M;
  for (int i = 0; i < M; i++) {
    std::cin >> elem;
    list.addElem(elem);
  }

  std::cout << list << std::endl;

  for (int i = 0; i < M; i++) {
    std::cin >> elem;
    list.remElem(elem);
  }
  
  std::cout << list << std::endl;



  return 0;
}