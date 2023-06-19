#include <iostream>
#include <cassert>

using namespace std;

template <class T> class Tree;
template <class T> class Node;

template <class T> 
class Tree {
	public:
		Node<T> *root = nullptr;
    int T_low = 0;
    int T_max = 0;

		void addElem(T);
		Node<T>* remElem(Node<T> *ptr, T);
    void dispPreOrder(Node<T> *ptr);
    void dispPostOrder(Node<T> *ptr);
    void dispInOrder(Node<T> *ptr);
    int longestPath(Node<T> *ptr, int c);
    int shortestPath(Node<T> *ptr, int c);



    Node<T> *maxNo(Node<T>* ptr) {
      if (!ptr->leftPtr) {
        return ptr;
      }
      return maxNo(ptr->leftPtr);
    }

};

template <class T> 
class Node {
	public:
		T value;
		Node<T> *leftPtr;
		Node<T> *rightPtr;

		Node(T value) {
			this->value = value;
			leftPtr = nullptr;
			rightPtr = nullptr;
		}

};

//// 
//   TREE FUNCTIONS
////
template <class T>
void Tree <T> :: addElem(T val) {
  if (!root) {
    root = new Node<T>(val);
    // std::cout << "v of r " << root->value << std::endl;
    return;
  }
  Node<T> *current = root;
  //child - miejsce gdzie wezel moze przejsc
  Node<T> *child;
  
  //!= nullptr
  while (current) {
  // std::cout << "v of curr; " << current->value << std::endl;
    if (val >= current->value) {
      child = current->leftPtr;
      if (!child) {
        current->leftPtr = new Node<T>(val);
        return;
      }
    } else {
      child = current->rightPtr;
      if (!child) {
        current->rightPtr = new Node<T>(val);
        return;
      }
    }
    current = child;
  }
}

template<class T>
Node<T>* Tree<T> :: remElem(Node<T> *ptr, T toRem) {
  if (!ptr) return nullptr;

  //classy
  else if (toRem > ptr->value) {
    // ptr->leftPtr = remElem(ptr->leftPtr, toRem);
    ptr->leftPtr = remElem(ptr->leftPtr, toRem);
  } else if (toRem < ptr->value) {
    // ptr->rightPtr = remElem(ptr->rightPtr, toRem); 
    ptr->rightPtr = remElem(ptr->rightPtr, toRem);
  } else {
    //no child given
    if (!ptr->leftPtr && !ptr->rightPtr) { ptr = nullptr; } 
    //left is missing
    else if (!ptr->leftPtr) { ptr = ptr->rightPtr; return ptr; }
    //right is missing
    else if (!ptr->rightPtr) { ptr = ptr->leftPtr; return ptr; } 
    
    //both children (move to top, then change val)
    else {
      Node<T>* holder = maxNo(ptr->leftPtr);
      ptr->value = holder->value;
      
      ptr->leftPtr = remElem(ptr->leftPtr, holder->value);
    }

  }

  return ptr;
}

template<class T>
void Tree<T> :: dispPreOrder(Node<T> *ptr) {
  if (!ptr) return;
  std::cout << ptr->value << " ";
  dispPreOrder(ptr->leftPtr);
  dispPreOrder(ptr->rightPtr);
}

template<class T>
void Tree<T> :: dispPostOrder(Node<T> *ptr) {
  if (!ptr) return;
  dispPostOrder(ptr->leftPtr);
  dispPostOrder(ptr->rightPtr);
  std::cout << ptr->value << " ";
}

template<class T>
void Tree<T> :: dispInOrder(Node<T> *ptr) {
  if (!ptr) return;
  dispInOrder(ptr->leftPtr);
  std::cout << ptr->value << " ";
  dispInOrder(ptr->rightPtr);
}

template<class T>
int Tree<T> :: longestPath(Node<T> *ptr, int c) {
  if (!ptr) return 0;

  // std::cout << ptr->value << " " << c << std::endl;
  if (!ptr->leftPtr && !ptr->leftPtr) {
    if (c > this->T_max) {
      this->T_max = c;
      c = 0;
    }
  }

  longestPath(ptr->leftPtr, ++c);
  longestPath(ptr->rightPtr, c++);

  return this->T_max;
}

template<class T>
int Tree<T> :: shortestPath(Node<T> *ptr, int c) {
  if (!ptr) return 0;

  if (!ptr->leftPtr && !ptr->leftPtr) {
    if (!this->T_low) {
      T_low = c;
    } else if (c < this->T_low) {
      this->T_low = c;
      c = 0;
    }
  }

  shortestPath(ptr->leftPtr, ++c);
  shortestPath(ptr->rightPtr, c++);

  return this->T_low;
}

//// 
//   NODE FUNCTIONS
////

int main() {
	Tree<double> tree;
	int K, L, M;
  double num;

  std::cout << "num of elems to add: ";
	std::cin >> K;
	for (int i = 0; i < K; i++) {
		std::cin >> num;
    tree.addElem(num);
	}

  std::cout<<"num of elems to delete: ";
  std::cin >> L;
  for (int i = 0; i < L; i++) {
    std::cin >> num;
    tree.remElem(tree.root, num);
  }
  
	
  std::cout<<"display: 0->preorder; 1->inOrder; 2->postOrder";
  std::cin >> M;
  switch(M) {
    case 0:
      tree.dispPreOrder(tree.root);
      break;
    case 1:
      tree.dispInOrder(tree.root);
      break;
    case 2:
      tree.dispPostOrder(tree.root);
      break; 
  }

  std::cout << tree.longestPath(tree.root, 0) << " ";
  std::cout << tree.shortestPath(tree.root, 0);

// std::cout << tree.root->rightPtr->leftPtr->value;
  // std::cout << std::endl << tree.root->maxNo(tree.root);



	return 0;
}