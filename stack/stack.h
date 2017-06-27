/***********************************************************************
* Header:
*    Stack
* Summary:
*    This class contains the notion of a Stack: bucket to hold
*    data for the user as a last in, first out data structure.

* Author
*    Jason Reed
************************************************************************/

#ifndef STACK_H
#define STACK_H


#include <cassert>
#include <iostream>
#include <string>

/************************************************
 * Stack
 * A class that holds the data
 ***********************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Stack(int cap) throw (const char *);
   
   // destructor : free everything
   ~Stack()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }
   
   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }
   
   // the function to return the value of the top
   T & top() throw (const char *);
   
   // modifies a stack by removing the value at the top
   void pop() throw (const char *);
   

   // add an item to the container
   void push(const T & t) throw (const char *);
   
   
   // overloaded assignment operator
   Stack& operator = (const Stack& rhs) throw (const char *);
   
   
   // return the number of elements that can be held by the allocated storage
   int capacity()       { return cap;                  }
   

   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;           // how many items can I put on the Container before full?
   
};


/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/**********************************************
 * Stack: NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int cap) throw (const char *)
{
   assert(cap >= 0);
   
   // do nothing if there is nothing to do
   if (cap == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the stuff
   this->cap      = cap;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < cap; i++)
      data[i] = T();
}

/***************************************************
 * STACK :: PUSH
 * Insert an item on the end of the vector
 **************************************************/
template <class T>
void Stack <T> :: push(const T & t) throw (const char *)
{
   // do we have space?
   if (cap == 0)
   {
      cap = 1;
      data = new T[cap];
   }
   
   else if (cap <= numItems)
   {
      // double the capacity if we are over capicity
      cap *= 2;
      // create a temporary array
      T * tmp = data;
      // attempt to allocate
      try
      {
         data = new T[cap];
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
      
      // read the information into the new array
      for (int i = 0; i < numItems; i++)
         data[i] = tmp[i];
         
      // delete the temporary array  
      delete [] tmp;
   }
   
   // add an item to the end
   data[numItems++] = t;

   
}

/***************************************************
 * Stack :: operator =
 * Copies the data from one stack to another
 **************************************************/
template <class T>
Stack <T> & Stack <T> :: operator = (const Stack & rtSide) 
  throw (const char *)
{
   // dont do anyting if arrays equal
   if (this == &rtSide)
   {
      return *this;
   }
   else
   {
      // attempt to allocate
      try
      {
         if (rtSide.cap > cap)
         {
            // deletes the old array
            delete [] data;
            
            // sets variables and conditions 
            cap = rtSide.cap;
            numItems = rtSide.numItems;
            
            // create the new pointer
            data = new T[rtSide.cap];
         }
      }
      // throw an error code if memory cannot allocate
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
       
      // copy the data
      for (int i = 0; i < numItems; i++)
         data [i] = rtSide.data[i];

      return *this;
   }
}

/***************************************************
 * Stack :: top()
 * Gives us the top item of the stack. The program
 * cannot access any other part of the stack
 **************************************************/
template <class T>
T & Stack <T> :: top() throw (const char *)
{
   if (!empty())
   {
      // return the top item of the stack
      return data[numItems - 1];
   }
   else
   {
      // throw error if the stack is empty
      throw "ERROR: Unable to reference the element from an empty Stack";
   }
}

/***************************************************
 * Stack :: pop()
 * Allows us to remove the top item of the stack
 **************************************************/
template <class T>
void Stack <T> :: pop() throw (const char *)
{
   if (!empty())
   {
      numItems--;
   }
   else
      throw "ERROR: Unable to pop from an empty Stack";
}


#endif // STACK_H

