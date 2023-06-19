#include <iostream>
#include <cassert>

using namespace std;

template <class T> class Link;
template <class T> class DoubleEnded;

// ======================================================================
//                    Class Template List
// ======================================================================
template <class T>
class List {
protected:
    Link <T> *first;                // data field

public:
    List() : first(nullptr) {}      // default constructor
    List(const List &source);       // copy constructor
    virtual ~List() {};                // destructor

    virtual void add(T value);      // insert a new item
    virtual void deleteAll();
    T firstElement() const;        // access the first item
    virtual bool includes(T value) const;  // inclusion test
    bool isEmpty() const;
    virtual void removeFirst();

  // friend class DoubleEnded<T>;
};
// ======================================================================
//                    Class Template Link
// ======================================================================
template <class T>
class Link {
private:
    T value;
    Link <T> *next;

    Link(T val, Link *ptr) : value(val), next(ptr) { }
public:
    Link <T> *insert(T value);      // after current Link

    friend class List <T>;
    friend class DoubleEnded<T>;
};

// ======================================================================
//                    Class Template DoubleEnded
// ======================================================================

template <class T>
class DoubleEnded : public List<T> {
  private:
    T value;
    Link<T>* last;

  public:
    DoubleEnded() : last(nullptr) {}

    void add(T value) override {
      if (List<T>::isEmpty()) {
        List<T>::add(value);
        last = this->first;
        return;
      }
      List<T>::add(value);
    }
    void addAfter(T value) {
      if (List<T>::isEmpty()) {
        List<T>::add(value);
        last = this->first;
      } else {
        last = last->Link<T>::insert(value);
      }
    }
    virtual void deleteAll() {
      List<T>::deleteAll();
      last = nullptr;
    }
    T firstElement() const {
      assert(this->first != nullptr);
      return this->first->value;
    }
    bool includes(T value) const {
      for (Link <T> *p = this->first; p; p = p->next)
        if (value == p->value) return true;
    return false;
    }
    bool isEmpty() const {
      return this->first == nullptr;
    }
    void removeFirst() {
      List<T>::removeFirst();
      if (List<T>::isEmpty()) {
        last = nullptr;
      }
    }
};

// ======================================================================
//                    Class Template Link - attributes
// ======================================================================
template <class T> Link <T> * Link <T> ::insert(T value)
{
    next = new Link <T>(value, next);
    return next;
}

// ======================================================================
//                    Class Template List - attributes
// ======================================================================
template <class T> void List <T> ::add(T value)
{
    first = new Link <T>(value, first);
}

template <class T> T List <T> ::firstElement() const
{
    assert(first != nullptr);
    return first->value;
}


template <class T> bool List <T> ::isEmpty() const
{
    return first == nullptr;
}


template <class T> bool List <T> ::includes(T value) const
{
    for (Link <T> *p = first; p; p = p->next)
        if (value == p->value)return true;
    return false;
}

template <class T> void List <T> ::removeFirst() {
    assert(first != nullptr);
    Link <T> *ptr = first;  // save pointer to the first item
    first = ptr->next;      // reassign the first node
    delete ptr;
}

template <class T> void List <T> ::deleteAll() {
    Link <T> *next;
    for (Link <T> *p = first; p; p = next) {
        next = p->next;
        delete p;
    }
    first = nullptr;
}

// ======================================================================
//                            main
// ======================================================================

int main() {
  DoubleEnded<float> list;
  float item;
  int n = 4;

  for (int i = 0; i < n; i++) {
    std::cin >> item;
    list.addAfter(item);
  }

  for (int i = 0; i < n; i++) {
    std::cout << list.firstElement() << " ";
    list.removeFirst();
  }

  return 0;
}
// ======================================================================