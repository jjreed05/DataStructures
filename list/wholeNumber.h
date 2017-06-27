/***********************************************************************
* Header:
*    wholeNumber.h
* Summary:
*    This is the header file for my WholeNumber class. This class will
*    allow us to store large numbers since int cannot handle large numbers.
*    By using the Linked List that I have implemented, this class will 
*    be able to add other WholeNumber objects by going through and adding
*    each digit together. 
*
* Author
*    Jason Reed
************************************************************************/

#include "list.h"
using namespace std;

#ifndef WHOLENUMBER_H
#define WHOLENUMBER_H

/************************************************
 * WholeNumber
 * A class that will hold our big integers. This
 * class will allow us to add and hold the data 
 * for big integers since a normal "int" can't 
 * hold a large integer. This class only has
 * one encapsulated item which is the data.
 ***********************************************/
class WholeNumber
{
public:
   // Default constructor (kind of useless)
   WholeNumber() {}
   
   // Non-Default constructor
   WholeNumber(unsigned int number) {num.push_back(number);}
   
   // Assignment operator
   WholeNumber & operator = (const WholeNumber & rhs) 
   {this->num = rhs.num; return *this; }
   
   // Addition operator
   WholeNumber operator + (const WholeNumber & rhs);
   
   // Our display function
   friend std::ostream & operator << (std::ostream & out, const WholeNumber & rhs);
   
private:
   // The structure to hold our data
   List <unsigned int> num;
   
};
#endif