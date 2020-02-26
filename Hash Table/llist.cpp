//CS311
//INSTRUCTION:
//Must use the provided HW3P1_help.doc to create llist.cpp
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//- Make sure all if-then-else are commented describing which case it is
//- Make sure all local variables are described fully with their purposes
//EMACS HINT:
//  You can copy from a Word document to emacs (contrl-right click)
//  control-K cuts and control-Y pastes
//  Esc x replace-str does string replacements
//  Esc > goes to the end of the file; Esc < to the beginning
//  Tab on each line will indent perfectly for C++

// ====================================================
//HW#: HW3P1 llist
//Your name: Andrew Marston
//Complier:  g++
//File type: llist.cpp implementation file
//=====================================================

using namespace std;
#include<iostream>
#include"llist.h" 

using namespace std;
llist::llist()
{
  Front = NULL; //initiate the values of Front and Rear to Null
  Rear = NULL;
  Count = 0;
}

llist::~llist() 
{ 
  el_t x;
  while(!isEmpty())
    {
      deleteRear(x); //while there are elements in the list
    }
}

//PURPOSE: To check if the list is empty, helpful for trubble shooting.
//PARAMETER: No parameter because its doesn't need anything to check if its empty
bool llist::isEmpty() 
{ 
  if(Count == 0)
    {
      return true; //if the list is empty return true
    }
  else
    {
      return false; //return false if there are elements
    }
}

//PURPOSE: To display the whole list in order from thr front to the rear
//PARAMETER: No paramenter because it is just displaying the list
void llist::displayAll() 
{
  if(isEmpty())
    {
      cout << "[empty]" << endl; //if there are no elements, display empty
    }
  else
    {
      LNode *nodePtr = Front; //pointer to go through the list
      cout << "[";
      while(nodePtr != NULL) //while the pointer isn't at the end
	{
	  cout << " " << nodePtr->Elem; //cout the element that the pointer point to
	  nodePtr = nodePtr->Next; //set the pointer to the next node
	}
      cout << " ]" << endl;
    }
}
  
//PURPOSE: adds a node onto the rear of the list
//PARAMETER: the element that is inserted into the new node
void llist::addRear(el_t NewNum) 
{
  if(isEmpty()) //if the list is empty
    {
      Front = new LNode; //create a new node on front
      Front->Next = NULL;
      Front->Elem = NewNum;
      Rear = Front;
      Count++;
    }
  else
    {
      Rear->Next= new LNode; //add a node to the end
      Rear = Rear->Next; 
      Rear->Next = NULL;
      Rear->Elem = NewNum;
      Count++;
    }
}

//PURPOSE: Add a node to the front of the list
//PARAMETER: The element that is going to be inside of the new node
void llist::addFront(el_t NewNum) 
{
  if(isEmpty())
    {
      Front = new LNode;
      Front->Next = NULL;
      Front->Elem = NewNum;
      Rear = Front;
      Count++;
    }
  else
    {
      LNode *nodePtr = new LNode; //the new node
      nodePtr->Elem = NewNum; 
      nodePtr->Next = Front; //add the next of the new node as the current front
      Front = nodePtr; //update so that the front is the new node
      Count++;
    }
}

//PURPOSE: To delete the front node
//PARAMETER: The element number to return after deletion
void llist::deleteFront(el_t& OldNum)
{
  if(isEmpty())
    {
      throw Underflow();
    }
  else if(Front->Next == NULL) //if there is only one node
    {
      OldNum = Front->Elem;
      delete Front;
      Front = NULL;
      Rear = NULL;
      Count--;
    }
  else
    {
      OldNum = Front->Elem; //set the removed node's element to the return
      LNode *T; //create a pointer to get around the first node
      T = Front->Next;
      delete Front;
      Front = T; //update the node
      Count--;
    }
}

//PURPOSE: To delete the last node in the list
//PARAMETER: the el_t& OldNum)lement that will be returned from the deleted number
void llist::deleteRear(el_t& OldNum) 
{
  if(isEmpty())
    {
      throw Underflow();
    }
  else if(Front == Rear) //if there is only one node
    {
      OldNum = Rear->Elem;
      delete Rear;
      Front = NULL;
      Rear = NULL;
      Count--;
    }
  else
    {
      OldNum = Rear->Elem; //set the return num to the node's element
      LNode *T = Front; //pointer to get through the list
      while(T->Next != Rear)
	{
	  T = T->Next; //loop to get to the node before the end
	}
      delete Rear;
      Rear = T;
      Rear->Next = NULL;
      Count--;
    }
}

//PURPOSE: Go the the Ith node and delete the element and return the num
//PARAMETER: Which node we need to delete and the Element to return
void llist::deleteIth(int I, el_t& OldNum) 
{
  if(I > Count || I < 1) //if the number is lower than the minimum or higher than the amount of nodes in the list
    {
      throw OutOfRange();
    }
  else if(I == 1) //if we delete the first node
    {
      deleteFront(OldNum);
    }
  else if(I == Count) //if we delete the last node
    {
      deleteRear(OldNum);
    }
  else
    {
      LNode *T = Front; //pointer to get through the list
      for(int j = 1; j<I-1; j++) //stop before the node we want to delete
	{
	  T = T->Next;
	}
      OldNum = T->Next->Elem;
      LNode *S = T->Next->Next; //get to the node after the one about to be deleted
      delete T->Next;
      T->Next = S; //set the node's next that was before the deleted node equal to the one after the deleted
      Count--;
    }
}

//PURPOSE: To insert a node at the Ith spot in the list
//PARAMETER: I is the node we need to insert at and the other is the new number
void llist::insertIth(int I, el_t newNum) 
{
  if(I > Count+1 || I < 1) //if the number is lower than the minimum or higher than the amount of nodes in the list
    {
      throw OutOfRange();
    }
  else if(I == 1) //if inserting at the front
    {
      addFront(newNum);
    }
  else if(I == Count+1) //if inserting at the end of the list
    {
      addRear(newNum);
    }
  else
    {
      LNode *T = Front; //pointer to travers the list
      for(int j = 1; j < I-1; j++) //stop one before where we want to insert
	{
	  T = T->Next; 
	}
      LNode *S = T->Next; //pointer the original node in that space
      T->Next = NULL;
      T->Next = new LNode;
      T = T->Next;
      T->Elem = newNum;
      T->Next = S;
      Count++;
    }
}

//PURPOSE: The copy constructor to make a copy of the original list
//PARAMETER: The original linked list
llist::llist(const llist& Original) 
{
  this->Front = NULL;
  this->Rear = NULL;
  this->Count = 0;
  LNode *T = Original.Front; //pointer to traverse the list and copy the elements
  while(T != NULL)
    {
      this->addRear(T->Elem); //add the the list using the T element
      T = T->Next;
    }
}

//PURPOSE: To check and then set one list equal to the other one
//PARAMETER: The list that is to be copied
llist& llist::operator=(const llist& OtherOne) 
{
  if(&OtherOne != this) //if the lists are not pointing to the same spot
    { 
      while(!this->isEmpty()) //go through and delete the list we want to copy to
	{
	  el_t x;
	  this->deleteRear(x);
	}
      LNode *T = OtherOne.Front;
      while(T != NULL) //go through the list and copy to the desired list
	{
	  this->addRear(T->Elem);
	  T = T->Next;
	}
      return *this;
    }
}

