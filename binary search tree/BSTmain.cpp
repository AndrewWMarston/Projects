//CS311 Final Program
//Andrew Marston

#include "binstreeEC.h"

int main()
{
  string n; //for getting the name of the game from a text
  string g; //for getting the genre of a game from a text
  string p; //for getting the platform from a text
  char c; //for gettting the y/n response
  int user; //for the commands later in the program
  BST gList;
  cout << "Would you like to import from the current list? Enter y for yes and n for no: ";
  cin >> c;
  if(c == 'y')
    {
      gList.import();
    }
  gList.Display();
  do
    {
      cout << "What would you like to do?" << endl;
      for(int i = 0; i < 30; i++)
	{
	  cout << "=";
	}
      cout << endl;
      cout << "1. Search for a game." << endl;
      cout << "2. Add a game to the library." << endl;
      cout << "3. Remove a game from the library." << endl;
      cout << "4. Search for a specific genre." << endl;
      cout << "5. Search for a specific platform." << endl;
      cout << "6. Display all the games currently on the library." << endl;
      cout << "7. Exit and Save the current library." << endl;    
      for(int i = 0; i < 30; i++)
        {
          cout << "=";
        }
      cout << endl;
      cout << "Enter the number of the command you want to perform: ";  
      cin >> user;
      switch(user)
	{
	case 1:
	  {
	    cout << "Enter the name of the game you wish to search for: ";
	    cin >> n;
	    cout << "Enter the genre: ";
	    cin >> g;
	    cout << "Now enter the platform: ";
	    cin >> p;
	    el_t s(n,g,p);
	    if(gList.Search(s))
	      {
		cout << "It is currently in the library." << endl << endl;
	      }
	    else
	      {
		cout << "It is not currently in the library. Would you like to add it? (y/n): ";
		cin >> c;
		if(c == 'y')
		  {
		    gList.InsertVertex(s);
		  }
		cout << endl << endl;
	      }
	  }
	    break;
	case 2:
	  {
	    cout << "Enter the name of the game you wish to add: ";
	    cin >> n;
	    cout << "Enter the genre: ";
	    cin >> g;
	    cout << "Now enter the platform: ";
	    cin >> p;
	    el_t a(n,g,p);
	    gList.InsertVertex(a);
	    cout << endl << endl;
	  }
	  break;
	case 3:
	  {
	    cout << "Enter the name of the game you wish to delete: ";
	    cin >> n;
	    cout << "Now enter the platform: ";
	    cin >> p;
	    el_t d(n,g,p);
	    gList.DeleteVertex(d);
	    cout << endl << endl;
	  }
	  break;
	case 4:
	  {
	    cout << "Enter the genre you wish to search for: ";
	    cin >> g;
	    gList.searchG(g);
	    cout << endl << endl;
	  }
	  break;
	case 5:
	  {
	    cout << "Enter the platform that you wish to search for: ";
	    cin >> p;
	    gList.searchP(p);
	    cout << endl << endl;
	  }
	  break;
	case 6:
	  {
	    gList.Display();
	    cout << endl << endl;
	  }
	  break;
	case 7:
	  {
	    cout << "Are you sure you want to save changes? (y/n): ";
	    cin >> c;
	    if(c == 'y')
	      {
		cout << "Saving changes." << endl;
		gList.saveB();
	      }
	  else
	    {
	      cout << "Changes will not be saved." << endl;
	    }
	  }
	  break;
	default:
	  cout << "Invalid number/character. Please enter another one." << endl << endl;
	}
    }
  while(user != 7);
}
