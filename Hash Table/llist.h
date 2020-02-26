//CS311 Yoshii
//INSTRUCTION:
//Llist class - header file template 
//You must complete the ** parts and then complete llist.cpp
//Don't forget PURPOSE and PARAMETERS 

// =======================================================
// HW#: HW3P1 llist
// Your name: Andrew Marston
// Compiler:  g++ 
// File type: headher file  llist.h
//=======================================================

#ifndef llist_h
#define llist_h

#include "elem.h"


class llist;

//a list node is defined here as a struct Node for now
struct LNode
{
  el_t Elem;   // elem is the element stored
  LNode *Next;  // next is the pointer to the next node
  friend class llist;
};
//---------------------------------------------------------

class llist
{
  
  protected:
  LNode *Front;       // pointer to the front node
  LNode *Rear;        // pointer to the rear node
  int  Count;        // counter for the number of nodes
  
 public:

  // Exception handling classes 
  class Underflow{};
  class OutOfRange{};  // thrown when the specified Node is out of range

  llist ();     // constructor to create a list object
  ~llist();     // destructor to destroy all nodes
  
  //Checks to see if the linked list is empty
  bool isEmpty();
    
  //displys the whole list from the front
  void displayAll();

  //adds a node onto the front of the list
  void addFront(el_t);
    
  //adds a node onto the back of the list
  void addRear(el_t);

  //deletes the front node on the list
  void deleteFront(el_t&);
    
  //deletes the last node on the list
  void deleteRear(el_t&);
    
  //deletes a specific node of the list
  void deleteIth(int, el_t&);

  //inserts a node at a specific number into the list
  void insertIth(int, el_t);
  
   //Copy Constructor to allow pass by value and return by value
  llist(const llist&);
  
  //Overloading of = 
  llist& operator=(const llist&); 

};

#endif
