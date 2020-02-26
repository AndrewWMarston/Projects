// CS311 : This is the BST implementation file template by Rika Yoshii
// Each node has an Up link to make it easy to go up the tree.  It must be set as nodes are inserted.  Some deletion
// cases require Up link to be updated.
//
// INSTRUCTIONS:
// Look for ** comments to complete this file for HW4
// Try not to delete the ** comments
// Make sure all { } match. Doing Tab on each line helps.

// =========================================================
//HW#: HW4 BST
//Your name: Andrew Marston
//Complier:  g++
//File type: implementation file binstree.cpp
//================================================================

using namespace std;
#include <iostream>
#include "binstreeEC.h"

// constructor  initializes Root
BST::BST()
{
  Root = NULL;   // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  dtraverse(Root); // traverse to delete all vertices in post order
  Root = NULL;    
}
// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::dtraverse(Vertex *V)  // recursive post order traversal
{   
  if (V != NULL) 
    {
      dtraverse(V->Left);         // destroy left sub tree of V
      dtraverse(V->Right);       //  destroy right sub tree of V
      delete V;                  //  delete V
    }
}

// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display()
{
  cout << left << setw(40) << "Name" << setw(20) << "Genre" << setw(10) << "Platform" << endl;
  for(int i = 0; i < 75; i++)
    {
      cout << "=";
    }
  cout << endl;
  INorderTraversal(Root);  // start in-order traversal from the root
  cout << endl;
  for(int i = 0; i < 75; i++)
    {
      cout << "=";
    }
  cout << endl;
}
// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
// For non EC, the height and balance will always be 0 
void BST::INorderTraversal(Vertex *V)
{
  if (V != NULL)
    {
      INorderTraversal(V->Left); // ** traverse left sub-tree of V recursively
      cout << endl << V->Elem;
      //cout << " Height = " << V->Height << " Balance = " << V->Balance << endl; //** display V's element, height and balance and do endl;
      INorderTraversal(V->Right); // ** traverse right sub-tree of V recursively
    }
}

// PURPOSE: Searches for an element in PRE-order traversal
// This is the same as Depth First Traversal
bool BST::Search(el_t K)
{
  return PREorderSearch(Root, K);  // start pre-order traversal from the root 
}
// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
//        K is what we are looking for
bool BST::PREorderSearch(Vertex *V, el_t K)
{
  if(V != NULL)
    {
      if(V->Elem == K)
	{
	  return true; // found the element in V
	}
      else if(V->Elem > K)
	{
	  return PREorderSearch(V->Left, K);   //** traverse left sub-tree of V recursively
	} 
      else 
	{
	  return PREorderSearch(V->Right, K); //** traverse right sub-tree of V recursively
	}      
    }
  else 
    {
      return false;
    }
}

// ------ The following are for adding and deleting vertices -----


// PURPOSE: Adds a vertex to the binary search tree for a new element 
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(el_t E)
{
  // Set up a new vertex first
   Vertex *N;         // N will point to the new vertex to be inserted
   N = new Vertex;    // a new vertex is created
   N->Left  = NULL;   // make sure it does not
   N->Right = NULL; // point to anything
   N->Elem  = E;      // put element E in it
   N->Height = 0;
   N->Balance = 0;
   N->Up = NULL;      // no parent for now
   //cout << "Trying to insert " << E << endl;

   if (Root == NULL)  // Special case: we have a brand new empty tree
     {
       Root = N;      // the new vertex is added as the root
       //cout << "...adding " << E << " as the root" << endl; 
     }// end of the special case

   else  // the tree is not empty
     {
        Vertex *V;       // V will point to the current vertex
        Vertex *Parent;  // Parent will point to V's parent

        V = Root;        // start with the root as V

	// go down the tree until you cannot go any further        
	while (V != NULL)
	  {
	    if (N->Elem == V->Elem) // the element already exists
              {	
 
		cout << "...error: the element already exists" << endl;
		return;  
	      }
	    else
	      if (N->Elem < V->Elem)  // what I have is smaller than V
		{  
		  //cout << "...going to the left" << endl; 
		  Parent = V; // **change Parent to be V to go down 
		  V = V->Left; // ** change V to be V's Left 
		}
	      else // what I have is bigger than V
		{  
		  //cout << "...going to the right" << endl;
		  Parent = V; // ** change Parent to be V to go down
		  V = V->Right; // ** change V to be V's Right 
		}
	  }//end of while
        
   // reached NULL -- Must add N as the Parent's child
        
        if (N->Elem < Parent->Elem)  
          {  
	    Parent->Left = N;// ** Parent's Left should point to the same place as N 
            N->Up = Parent;// ** N should point UP to the Parent 
	    //cout << "...adding " << E << " as the left child of " << Parent->Elem << endl;	
	    climbup(N);
	    //Display();
	  }
        else 
           {
	     Parent->Right = N;// ** Parent's Right should point to the same place as N 
	     N->Up = Parent;// ** N should point UP to the Parent
	     //cout << "...adding " << E << " as the right child of " << Parent->Elem << endl;	
	     climbup(N);
	     //Display();
	   }
      }// end of normal case

}// end of InsertVertex


// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove
void BST::DeleteVertex(el_t E)
{
  //cout << "Trying to delete " << E << endl;
  
  Vertex *V;              // the current vertex
  // start with the root to look for E

  // case 1: Lonely Root  
  if ((E == Root->Elem) && (Root->Left == NULL) && (Root->Right == NULL))
    { 
      //cout << "...deleting the lonely root" << endl;
      delete Root; 
      Root = NULL;
      return; 
    }  // only the Root was there and deleted it
  
  // case 2:  One Substree Root
  else if(Root->Elem == E)// ** if what you want to delete is the root
  {
    if(Root->Elem == E && Root->Left != NULL && Root->Right == NULL)// ** and it has only the left subtree
    { 
      Root = Root->Left;//** change the root to the left child and return
      delete Root->Up;
      Root->Up = NULL;
      return;
    }
    else if(Root->Elem == E && Root->Left == NULL && Root->Right != NULL)// ** and it has only the right subtree
    { 
      Root = Root->Right; // ** change the root to the right child and return
      delete Root->Up;
      Root->Up = NULL;
      return;
    }
    
    else
      {
	V = Root;
	Vertex *P = Root;
	remove(V, P);
	return;
      }
  }
  // end of deleting the root with one subtree
  
  // Otherwise deleting something else
  else
    {
      V = Root;
      Vertex *Parent = V;
      
      // going down the tree looking for E
      while (V != NULL)
	{ 
	  if ( E == V->Elem)   // found it
	    {  
	      //cout << "...removing " << V->Elem << endl;
	      remove(V, Parent);// ** call remove here to remove V
	      return; 
	    }
	  else
	    {
	      if (E < V->Elem)
		{  
		  //cout << "...going to the left" << endl;
		  Parent = V;
		  V = V->Left; // ** update Parent and V here to go down 
		}
	else
	  {  
	    //cout << "...going to the right" << endl;
	    Parent = V; // ** update Parent and V here to go down
	    V = V->Right;
	  }      
	    }// end of while
	}  // reached NULL  -- did not find it
      cout << "Did not find the key in the tree." << endl;
      
    }// end of DeleteVertex
}
// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P)
{
  if(V->Right == NULL && V->Left == NULL)// ** if V is a leaf (case 1)
      {
	//cout << "removing a leaf" << endl;
	if(P->Left == V)// ** if V is a left child of P
	  {
	    //delete V;
	    P->Left = NULL;   // ** delete V and also make Parent's left NULL 
	    climbup(P);
	  }
	else // V is a right child of the Parent
	  { 
	    delete V;
	    P->Right = NULL;// ** delete V and also make Parent's right NULL 
	    climbup(P);
	  }
      }//end of leaf case
    
  else if(V->Left != NULL && V->Right == NULL)// ** if V has just the left child so bypass V (case 2)
	{
	  //cout << "removing a vertex with just the left child" << endl;
	  if(P->Right == V)
	    {
	      V = V->Left;
              delete P->Right;
              P->Right = V;
              V->Up = P;
	      climbup(V);
	      delete V;
	    }
	  else
	    {
	      V = V->Left;
              delete P->Left;
              P->Right = V;
	      V->Up = P;
	      climbup(V);
              delete V;
	    }
	  // ** You need if then else to determine Parent's left or right
	  // ** should point to V's left child; Make the left child
	  // ** point UP to the parent;
	  // ** Be sure to delete V
	} // end of V with left child       
 
  else if(V->Left == NULL && V->Right != NULL)// ** if V has just the right child so bypass V (case 2)
	{
	  //cout << "removing a vertex with just the right child" << endl;
	  if(P->Right == V)
	    {
	      V = V->Right;
	      delete P->Right;
              P->Right = V;
	      V->Up = P;
	      climbup(V);
              delete V;
	    }
	  else
	    {
	      V = V->Right;
              delete P->Left;
              P->Left = V;
	      V->Up = P;
	      climbup(V);
              delete V;
	    }
	  // ** You need if then else to determine Parent's left or right
	  // ** should point to V's right child; make the right child
          // ** point UP to the parent;   
	  // ** Be sure to delete V
        }//end of V with right child
      
   else // V has two children (case 3)
	{ 
	  //cout << "removing an internal vertex with children" << endl;
	  //cout << "..find the MAX of its left sub-tree" << endl;
	  el_t Melem;
	  // find MAX element in the left sub-tree of V
          Melem = findMax(V); 
          //cout << "..replacing " << V->Elem << " with " << Melem << endl;
          V->Elem = Melem;// ** Replace V's element with Melem here
        }//end of V with two children 
}// end of remove

// PURPOSE: Finds the Maximum element in the left sub-tree of V
// and also deletes that vertex
el_t BST::findMax(Vertex *V)
{
  Vertex *Parent = V;
  V = V->Left;          // start with the left child of V
  
  while(V->Right != NULL)// ** while the right child of V is still available
  {
    Parent = V;
    V = V->Right;// ** update Parent and V to go to the right
  }
  
  // reached NULL Right  -- V now has the MAX element
  el_t X = V->Elem;
  //cout << "...Max is " << X << endl;
  remove(V, Parent);    // remove the MAX vertex 
  return X;             // return the MAX element
}// end of FindMax

void BST::climbup(Vertex* V)
{
  //cout << "...Start climbing up to adjust heights ......" << endl;
  while (V != NULL)
    {
      // ** compute V->Height  based on the left/right children
      if(V->Right == NULL && V->Left == NULL)
	{
	  V->Height = 0;
	}
      else if(V->Left == NULL && V->Right != NULL)
	{
	  V->Height = V->Right->Height+1;
	}
      else if(V->Left != NULL && V->Right == NULL)
        {
          V->Height = V->Left->Height+1;
        }
      else if(V->Left->Height > V->Right->Height)
	{
	  V->Height = V->Left->Height + 1;
	}
      else
        {
          V->Height = V->Right->Height + 1;
        }
      // ** compute V->Balance based on the left/right children
      if(V->Right == NULL && V->Left == NULL)
	{
	  V->Balance = 0;
	}
      else if(V->Right != NULL && V->Left == NULL)
	{
	  V->Balance = V->Right->Height - (-1);	 
	}
      else if(V->Right == NULL && V->Left != NULL)
	{
	  V->Balance = (-1) - (V->Left->Height);
	}
      else
	{
	  V->Balance = (V->Right->Height) - (V->Left->Height);
	}
      //cout << "..." << V->Elem << "'s height: " << V->Height << " with balance: " << V->Balance << endl;
      // ** go up to the parent 
      if(V->Balance > 1 || V->Balance < -1)
        {
	  fixIt(V);
        }  
      V = V->Up;
    }
  //Display();
}

void BST::fixIt(Vertex *V)
{
  if(V->Balance == 2)
    {
      if(V->Right->Balance == -1)
	{
	  //cout << "Case 3" << endl;
	  case3(V);
	}
      else
	{
	  //cout << "Case 1" << endl;
	  case1(V);
	}
    }
  else
    {
      if(V->Left->Balance == 1)
	{
	  //cout << "Case 4" << endl;
	  case4(V);
	}
      else
	{
	  //cout << "Case 2" << endl;
	  case2(V);
	}
    } 
}

void BST::case1(Vertex *V)
{
  Vertex *Pivot = V->Right;          // Right child of the root is the pivot
  V->Right = Pivot->Left;   // this is Y
  Pivot->Left = V;  //The Pivot becomes the root of this subtree.;
  Pivot->Up = V->Up;
  V->Up = Pivot;

  if(Root == V)  //if the shifting node was the root make the root point to the pivot
    {
      Root = Pivot;
    }
  if(V->Right != NULL)
    {
      V->Right->Up = V;
    }
  if(Pivot->Up != NULL)
     {
      if(Pivot->Up->Right == V)
	{
	  Pivot->Up->Right = Pivot;
	}
      else
	{
	  Pivot->Up->Left = Pivot;
	}
     }

  climbup(V);
}

void BST::case2(Vertex *V)
{
  Vertex *Pivot = V->Left;  // Left child of the root is the pivot
  V->Left = Pivot->Right;   // this is Y
  Pivot->Right = V; //The Pivot becomes the root of this sub-tree.
  Pivot->Up = V->Up;
  V->Up = Pivot;
  if(Root == V)
    {
      Root = Pivot;
    }
  if(V->Left != NULL)
    {
      V->Left->Up = V;
    }
  if(Pivot->Up != NULL)
    {
      if(Pivot->Up->Left == V)
	{
	  Pivot->Up->Left = Pivot;
	}
      else
	{
	  Pivot->Up->Right = Pivot;
	}
    }
  climbup(V);
}

void BST::case3(Vertex *V)
{
  case2(V->Right); //because I call climbup in the other case, it calls fixit in the climb up
  //Display();
}

void BST::case4(Vertex *V)
{
  case1(V->Left); //because I call climbup in the other case, it calls fixit in the climb up
  //Display();
}

void BST::saveB()
{
  ofstream fout("game.txt", ios_base::trunc);
  fout.close();
  save(Root);
}
void BST::save(Vertex *V)
{
  ofstream fout("game.txt", ios_base::app);
  if (V != NULL)
    {
      save(V->Left); 
      fout << V->Elem << endl;
      save(V->Right); 
    }
  fout.close();
}

void BST::import()
{
  string n;
  string g;
  string p;
  ifstream fin;
  fin.open("game.txt");
  if(fin)
    {
      while(fin >> n)
	{
	  fin >> g >> p;
	  el_t nElem(n,g,p);
	  InsertVertex(nElem);
      }
      fin.close();
    }
  else
   {
     cout << "File did not open properly." << endl;
   }
}

void BST::searchG(string g)
{
  sGenre(Root, g);
}

void BST::sGenre(Vertex *V, string g)
{
  if(V != NULL)
    {
      sGenre(V->Left, g);
      if(V->Elem.genre == g)
	{
	  cout << V->Elem << endl;
	}
      sGenre(V->Right, g);
    }
}

void BST::searchP(string p)
{
  sPlatform(Root, p);
}

void BST::sPlatform(Vertex *V, string p)
{
  if(V != NULL)
    {
      sPlatform(V->Left, p);
      if(V->Elem.platform == p)
        {
          cout << V->Elem << endl;
        }
      sPlatform(V->Right, p);
    }
}
