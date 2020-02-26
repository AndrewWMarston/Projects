/*
Name: Andrew Marston
Compilier: g++
Purpose: The cpp file for the class slist that includes all the Functions for the class
*/

#include "slist.h"


slist::slist()
{
}   

int slist::search(el_t k)
{
  LNode *nodePtr = Front;
  int count = 1;
  while(nodePtr != NULL && !(nodePtr->Elem == k))
    {
      Count++;
      nodePtr = nodePtr->Next;
    }
  if(nodePtr == NULL)
    {
      return 0;
    }
  else
    {
      return count;
    }
}
// search through the list to see if any node contains the key.
// If so, return its position (>=1). Otherwise, return 0.

el_t slist::search2(el_t k)
{
  LNode *nodePtr = Front;
  int count = 1;
  while(nodePtr != NULL && !(nodePtr->Elem == k))
    {
      Count++;
      nodePtr = nodePtr->Next;
    }
  if(nodePtr == NULL)
    {
      el_t b;
      return b; 
    }
  else
    {
      return nodePtr->Elem;
    }
}

void slist::replace(el_t p, int x)
{
  if(Count < x || x > 1)
    {
      throw OutOfRange();
    }
  else
    {
      LNode *nodePtr = Front;
      int pos = 1;
      while(nodePtr != NULL && pos != x)
    {
      nodePtr = nodePtr->Next;
    }
      if(nodePtr != NULL)
	{
	  nodePtr->Elem = p;
	}
    }
}
// go to the Ith node (if I is between 1 and Count) and
// replace the element there with the new element.
// If I was an illegal value, throw OutOfRange

bool slist::operator==(const slist& l2)
{
  LNode *Ptr1 = this->Front;
  LNode *Ptr2 = l2.Front;
  while(Ptr1 != NULL && Ptr2 != NULL)
    {
      if(Ptr1->Elem == Ptr2->Elem)
	{
	  Ptr1 = Ptr1->Next;
	  Ptr2 = Ptr2->Next;
	}
      else
	{
	  return false;
	}
    }

  if(Ptr1 != NULL || Ptr2 != NULL)
    {
      return false;;
    }
  else
    {
      return true;
    }
}

