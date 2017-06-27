/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Jason Reed
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
#include "struct.h"     // structure for data
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   int timer = 0;                  // initialize the timer of the program
   Information information;        // struct to hold the current information
   Deque <Information> deque;      // deque to hold the strcuts
   
   cout << "<" << timer << "> ";
   
   getUserInput(information);      // prompt the user for information
   information.stop = false;       // this allows to end the loop
   display(information);           // display the current information
   timer++;                        // increment the timer
   information.minutes--;          // decrement the minutes

   // we will start our loop
   do
   {
      // second struct is used to hold information of the user in line
      Information addInformation;
      
      // finish, emergency, normal, none
      string option;
      cout << "<" << timer << "> ";
      cin >> option;
      
      // do not push any items in 
      if (option == "none")
      {
         if (information.minutes > 0)
            display(information);   
         timer++;
         information.minutes--;
      }
      
      // emergency
      else if (option == "!!")
      {
         getUserInput(addInformation);
         
         // tells the display its an emergency
         addInformation.emergency = true;
         display(information);
         
         // pushes to the front since its priority
         deque.push_front(addInformation);
         
         timer++;
         information.minutes--;
      }
      
      // stop the program
      else if (option == "finished")
      {
         information.stop = true;
      }
      
      // handles normal input 
      else
      {
         // the input is a class name
         addInformation.className = option;
         
         // continue to get the rest of the user's input
         cin >> addInformation.userName >> addInformation.minutes;
         
         // not an emergency
         addInformation.emergency = false;
         
         // push to the back
         deque.push_back(addInformation);
         
         // make the information current if previous information
         // is at 0 minutes
         if (information.minutes <= 0)
         {
            // create a struct to hold the items temporarily
            Information tmp;
            // copy the front item of the deck
            tmp = deque.front();
            // pop the front item off the deck
            deque.pop_front();
            // copy the information and make it current
            information.className = tmp.className;
            information.userName  = tmp.userName;
            information.minutes   = tmp.minutes;
            information.emergency = tmp.emergency;
         }
         // displays current information
         display(information);
         // decrement the minutes
         information.minutes --;
         // increment timer
         timer++;
      }
      
      // make the information current if previous information
      // is at 0 minutes  
      if (information.minutes == 0)
      {
         if (!deque.empty())
         {
            // create a struct to hold the items temporarily
            Information tmp;
            tmp = deque.front();
            deque.pop_front();
            // copy the information and make it current
            information.className = tmp.className;
            information.userName  = tmp.userName;
            information.minutes   = tmp.minutes;
            information.emergency = tmp.emergency;
         }
      }
   } while(!information.stop);
   
   
   // end
   cout << "End of simulation\n";
   
}

/***************************************************
 * DISPLAY
 * This allow us to display the current information
 **************************************************/
void display(Information & information)
{
  if (information.emergency == false)
  {
     cout << "\tCurrently serving " << information.userName  << " " 
          << "for class "           << information.className << ". "
          << "Time left: "          << information.minutes   << endl;
  }
  else
  {
     cout << "\tEmergency for "     << information.userName  << " "
          << "for class "           << information.className << ". "
          << "Time left: "          << information.minutes   << endl;
  }
}

/**************************************************
 * GETUSERINPUT
 * This gets the user's input.
 **************************************************/
void getUserInput(Information & information)
{
   cin >> information.className >> information.userName >> information.minutes;
   information.stop = false;
}


