/***********************************************************************
* Header:
*    fibonacci.cpp
* Summary:
*    This is the source file for my fibonacci file.  
* Author
*    Jason Reed
************************************************************************/

#include "fibonacci.h"


using namespace std;

/************************************************
 * fibonacci() 
 * This function will generate the fibonacci number
 * by prompting the user which number he or she
 * wants to see. It will then generate a sequence
 * of fibonacci numbers. Then, it will prompt the
 * user which single fibonacci number he or she
 * wants to see.
 ***********************************************/
void fibonacci()
{
   int input;
   
   // we will use this to add our numbers together
   WholeNumber number1(1);
   WholeNumber number2(1); 
   WholeNumber number3(1);
   
   // prompt the user
   cout << "How many Fibonacci numbers would you like to see? ";
   cin >> input;
   
   // display 1
   cout << "\t" << number3 << endl;
   
   // display the remaining numbers
   for (int i = 0; i < input - 1; i++)
   {
      cout << "\t" << number3 << endl;
      // the new number will equal the sum of the previous
      // two numbers
      number3 = (number1 + number2);
      // change the numbers to the next two numbers
      number1 = number2;
      number2 = number3;
      //cerr << number1 << " " << number2 << " " << number3 << endl;
   }
   
   // reset the variables
   number1 = 1;
   number2 = 1;
   number3 = 1;
   
   // cerr << number1 << " " << number2 << " " << number3 << endl;
   
   // prompt the users
   cout << "Which Fibonacci number would you like to display? ";
   cin >> input;
   
   // calculate the fibonacci numbers
   for (int i = 0; i < input - 2; i++)
   {
      // the new number will equal the sum of the previous
      // two numbers
      number3 = number1 + number2;
      // change the numbers to the next two numbers
      number1 = number2;
      number2 = number3;
      
   }
   
   // display the number
   cout << "\t" << number3 << endl;
   
   return;
}