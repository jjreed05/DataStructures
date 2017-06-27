/***********************************************************************
* Header:
*    Queue
* Summary:
*    This class contains the notion of a Stack: bucket to hold
*    data for the user as a last in, first out data structure.

* Author
*    Jason Reed
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H


#include <cassert>
#include <iostream>
#include <string>

using namespace std;

/************************************************
 * Queue
 * A class that holds the data
 ***********************************************/
template <class T>
class Queue
{
public:
   // default constructor : empty and kinda useless
   Queue() : numItems(0), cap(0), data(NULL), myFront(0), myBack(0) {}

   // copy constructor : copy it
   Queue(const Queue & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Queue(int cap) throw (const char *);
   
   // destructor : free everything
   ~Queue()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return !numItems; }
   
   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }
   
   // the function to return the value of the top
   T & front() throw (const char *);
   
   T & back() throw (const char *);
   
   // modifies a stack by removing the value at the top
   void pop() throw (const char *);
   

   // add an item to the container
   void push(const T & t) throw (const char *);
   
   
   // overloaded assignment operator
   Queue& operator = (const Queue& rhs) throw (const char *);
   
   
   // return the number of elements that can be held by the allocated storage
   int capacity()       { return cap;                  }

   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;           // how many items can I put on the Container before full?
   int myFront; 
   int myBack;
   
};


/*******************************************
 * Queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      myFront = 0;
      myBack = 0;
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
   
   // copy over the values
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;
   myFront = rhs.myFront;
   myBack = rhs.myBack;
   
   int index;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
   {
      index = (i + rhs.myFront) % cap;
      data[index] = rhs.data[index];
   }
   
   //cerr << "myFront: " << myFront << " ";
   //cerr << "myBack: " << myBack << " ";
}

/**********************************************
 * Queue: NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Queue <T> :: Queue(int cap) throw (const char *)
{
   assert(cap >= 0);
   
   // do nothing if there is nothing to do
   if (cap == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      this->myFront = 0;
      this->myBack = 0;
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
   
   this->cap      = cap;
   this->numItems = 0;
   this->myFront  = 0;
   this->myBack   = 0;

   // initialize the container by calling the default constructor
   for (int i = myFront; i < cap; i++)
      data[i] = T();
}

/***************************************************
 * Queue :: PUSH
 * Insert an item on the end of the vector
 **************************************************/
template <class T>
void Queue <T> :: push(const T & t) throw (const char *)
{
 // do we have space?
   if (numItems < cap)
   {
      // circular queue push implementations
      myBack = (myBack % cap + 1) ;
      data[myBack - 1] = t;
      // we have more items
      numItems++;
   }
   
   else 
   {
      //cerr << "We are allocating" << endl;
      if (cap == 0)
      {
         cap = 1;
         data = new T[cap];
         data [0] = t;
         numItems++;
         return;
      }
      
      // double the capacity
      T * newData = new T[cap * 2];
      int j = myFront;
      
      // copy over the items
      for (int i = 0; i < numItems; i++, j = (j + 1) % cap)
      {
         newData[i] = data[j];
      }
      // delete the old array
      delete [] data;
      data = newData;
      myFront = 0;
      myBack = numItems;
      cap *= 2;
      
      // recursion
      push(t);
   }
   return;
}

/***************************************************
 * Queue :: operator =
 * Copies the data from one stack to another
 **************************************************/
template <class T>
Queue <T> & Queue <T> :: operator = (const Queue & rtSide) 
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
            myFront = rtSide.myFront;
            myBack = rtSide.myBack;
            
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
      for (int i = myFront; i < cap; i++)
         data[i] = rtSide.data[i];
      
      return *this;
   }
}

/***************************************************
 * Queue :: front()
 * Gives us the front item of the que. The program
 * cannot access any other part of the stack
 **************************************************/
template <class T>
T & Queue <T> :: front() throw (const char *)
{
   if (!empty())
   {
      // return the top item of the stack
      return data[myFront];
   }
   else
   {
      // throw error if the stack is empty
      throw "ERROR: attempting to access an item in an empty queue";
   }
}

/*******************************
 * BACK
 *  Return LAST item
 *******************************/
template <class T>
T & Queue <T> :: back() throw (const char *)
{
   if (!empty())
      return data[myBack - 1];
   else
      throw "ERROR: attempting to access an item in an empty queue";
}

/***************************************************
 * Queue :: pop()
 * Allows us to remove the top item of the stack
 **************************************************/
template <class T>
void Queue <T> :: pop() throw (const char *)
{
   if (numItems > 0)
   {
      // keeps the circular implementation of the queue
      myFront = ((myFront + 1) % cap);
      numItems--;
   }
   else
      throw "ERROR: attempting to pop from an empty queue";
}




#endif // QUEUE_H

