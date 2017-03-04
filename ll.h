#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <stdexcept>  
#include <string.h>

template<typename T>
class LinkedList{
 private:
  class Node{
  public:
    T data;
    Node* next;
    Node* previous;
    // Constructors for Node
  Node(const T& d): data(d), next(NULL), previous(NULL){}
  Node(const T& d, Node* n, Node* p): data(d), next(n), previous(p){}
  };
  Node * head;
  Node * tail;
  int size;
 public:
  
  // Constructors for LinkedList
 LinkedList(): head(NULL), tail(NULL), size(0){}
  
  // Add item to front
  virtual void addFront(const T &item) {
    head = new Node(item,head,NULL);
    if (tail == NULL){
      tail = head; 
    }
    else{
      head->next->previous = head;
    }
    size++;
  }

  
  // Add item to back
  virtual void addBack(const T &item) {
    tail = new Node(item,NULL,tail);
    if (head == NULL){
      head = tail;
    }
    else{
      tail->previous->next = tail;
    }
    size++;
  }
  
  // Remove specified item, return true if item removed, false if not present
  // Only remove first occurence starting from head
  bool remove(const T &item) {
    Node *pPre = NULL;
    Node *pDel = NULL;
    
    if (head == NULL){
      return false;
    } 
  
    // Check whether it is the head node
    if (head->data == item) {
      pDel = head;
      head = pDel->next;
      if (head != NULL){
	head->previous = NULL;
      }
      else{
	tail = head;
      }
      delete pDel;
      size--;
      return true;
    }
    
    pPre = head;
    pDel = head->next;
    
    // Go through list
    while (pDel != NULL) {
      if (pDel->data == item) {
	pPre->next = pDel->next;
	// Check if tail
	if (pDel == tail) {
	  tail = pPre;
	}
	else{
	  pDel->next->previous = pDel->previous;
	}
	delete pDel;
	size--;
	return true; 
      }
      pPre = pDel;
      pDel = pDel->next;
    }
    return false;

  }
  
  // Return reference to data in index element
  // make exception class that extends std::exception, throw if item d.n.e.
  virtual T& operator[](int index) {
    Node * curr = head; 
 
    if (index >= size){
      throw(std::out_of_range("Index out of range"));
    }

    for (int i = 0; i < index; i++){
      curr = curr->next;
    }
    return curr->data;

  }



  virtual const T& operator[](int index) const{
    Node * curr = head; 
    
    if (index >= size){
      throw(std::out_of_range("Index out of range"));
    }

    for (int i = 0; i < index; i++){
      curr = curr->next;
    }
    return curr->data;
   
    
  }
  
  // Return index of item in the list, -1 if no such item exists
  int find(const T &item) {
    Node * curr = head;
    int i = 0;
    while(i < size){
      if (curr->data == item){
	return i;
      }
      curr = curr->next;
      i++;
    }
    return -1;
  }

  
  // Return number of items in the list
  int getSize() const{
    return size;
  }

  // Copy Constructor  
  LinkedList<T>(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0) {   

    Node * curr = rhs.head;
    while (curr != NULL){
      addBack(curr->data);
      curr = curr->next;
    }
    
  }

  virtual LinkedList<T>& operator=(const LinkedList<T> & rhs) {
    if(this != &rhs){
      LinkedList temp(rhs);
      std::swap(head,temp.head);
      std::swap(tail,temp.tail);
      std::swap(size,temp.size);
    }
    return *this;
  }

  // Destroy fxn
  void destroy(){
    Node * temp;
    while (head != NULL){
      temp = head->next;
      if (head->next != NULL){
	temp->previous = NULL;
      }
      delete head;
      head = temp;
      size--;
    }
    tail = head;
  }
  
  // Destructor for list
  virtual ~LinkedList(){
    destroy();
  }

};

#endif
