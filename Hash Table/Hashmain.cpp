// CS311 Yoshii - complete ** for HW8 client
// Note that the client knows about elem.h functions.
// It can create el_t objects.
//-----------------------------------------------

//============================================
// HW#: HW8 hashing client
// Name: Andrew Marston
// File type: client hw8client.cpp
//===========================================

using namespace std;
#include "htable.h"

// note that the second constructor of el_t can be used to
// create key+name to add to the table.
int main()
{ 
  /* 
 Loop:  
   Interactively add about 20 keys and names to the table,
     making sure some of them  collide. (function add)
     You can create el_t containing a key and name using a constructor.
 DisplayTable.
 Loop:
  Interactively look up names using keys. (function find)
  Display the key + name if found else error message. 
  */  
  htable h;
  int g = 1;
  cout << "Please enter 20 names." << endl;
  for(int i = 0; i < 20; i++)
    {
      string n;
      int k;
      cout << "Name " << i+1 << ": ";
      cin >> n;
      cout << "Enter a key for the name: ";
      cin >> k;
      el_t e(k,n);
      k = h.add(e);
      cout << "Added " << n << " to slot " << k << "." << endl;
    }
  cout << "Done adding all of the names." << endl;
  h.displayTable();
  while(g > -1)
    {
      int k;
      cout << "Enter a key to look up a name: ";
      cin >> k;
      cout << "Searching for " << k << endl; 
      el_t ET = h.find(k);
      cout << ET << endl;
      cout << "Do you wish to continue? Enter any postitive number to contiune and use -1 to stop." << endl;
      cin >> g;
    }
  return 0;
}

