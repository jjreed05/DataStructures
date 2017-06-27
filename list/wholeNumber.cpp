/***********************************************************************
* Header:
*    wholeNumber.cpp
* Summary:
*    This is the source file for my WholeNumber class.  
* Author
*    Jason Reed
************************************************************************/

#include "wholeNumber.h"
#include <iomanip>

/************************************************
 * WholeNumber :: Addition Operator
 * This function allows us to add two WholeNumber
 * classes together by using an iterator. It will
 * iterate through both classe's numbers. The nodes
 * can only hold 1,000. We will use modulus and 
 * push the remainder and add the carry to the next
 * node.
 *  - WholeNumber rhs: A whole number class
 * Return: sum 
 ***********************************************/
WholeNumber WholeNumber :: operator + (const WholeNumber & rhs)
{  
   // The object to return
   WholeNumber sum;
   // We will use these to help us add
   unsigned int first = 0;
   unsigned int second = 0;
   unsigned int result = 0;
   unsigned int carry = 0;
   
   // Iterator for this object
   ListIterator <unsigned int> it1 = num.rbegin();
   // Iterator for the righ hand side object
   ListIterator <unsigned int> it2 = rhs.num.rbegin();
   
   // Loop both objects and add the nodes' integers together
   while (it1 != num.rend() || it2 != rhs.num.rend())
   {
      // Decrement this iterator
      if (it1 != num.rend())
      {
         first = *it1;
         it1--;
      }
      else
        // Set it to 0 
        first = 0;
      
      // Decrement the rhs iterator
      if (it2 != rhs.num.rend())
      {
         second = *it2;
         it2--;
      }
      else
        // Set it to 0
        second = 0;
        
      //cerr << carry << endl;
      
      // Creating a temporary integer
      unsigned int tmp = first + second + carry;
      // Remainder if its bigger than 1,000
      result = tmp % 1000;
      // We will use this for the next node
      carry = tmp / 1000;
      sum.num.push_front(result); 
      
      /*cerr << "First: " << first     << " "    << "Second: "  << second 
           << " "       << "Third: " << result << " Carry: "  << carry
           << endl      << endl;*/
   } 
   
   //cerr << "We are out of the loop. \n";
   
   // Nothing else to add except the left over carry
   if (carry > 0)
      sum.num.push_front(carry);
   
   return sum;
   
}

/************************************************
 * WholeNumber :: Display Operator
 * This will allow us to display the list of 
 * integers so that it is organized into each
 * thousand's place and with commas.
 * Return: out
 ***********************************************/
ostream & operator << (ostream & out, const WholeNumber & rhs)
{
   ListIterator <unsigned int> it = rhs.num.begin();
   // Display the first node
   out << *it;
   it++;
   // Display the remaining nodes
   for ( ; it != NULL; it++)
   {
      out << ",";
      out << setfill('0') << setw(3) << *it;
   }
   // return the display
   return out;
}

