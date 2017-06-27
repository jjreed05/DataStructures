/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a Vector: bucket to hold
*    data for the user. 
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Container
* Author
*    Jason Reed
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H


#include <cassert>
#include <iostream>
#include <string>


// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int cap) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }
   
   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // add an item to the container
   void push_back(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}
   
   // overloaded assignment operator
   Vector& operator = (const Vector& rhs) throw (const char *);
   
   // bracket operator
   T & operator[] (const int index)
   { 
      if (index < 0 || index >= cap)
         throw false;
      return data[index];   
   }

   // constant bracket operator
   T & operator[] (const int index) const
   { 
      if (index < 0 || index >= cap)
         throw false;
      return data[index];
   }
 
   
   // return the number of elements that can be held by the allocated storage
   int capacity()       { return cap;                  }
   

   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;           // how many items can I put on the Container before full?
   
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
   VectorIterator() : p(NULL) {}

   // initialize to direct p to some item
   VectorIterator(T * p) : p(p) {}
  
   // copy constructor
   VectorIterator(const VectorIterator & rhs) { *this = rhs; }
   
   // assignment operator
   VectorIterator & operator = (const VectorIterator & rhs)
   {
      this-> p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   } 

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
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
 * VECTOR: NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int cap) throw (const char *)
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
 * VECTOR :: PUSH_BACK
 * Insert an item on the end of the vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
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
   data[numItems] = t;
   numItems ++;
   
}

/***************************************************
 * VECTOR :: operator =
 * Copies the data from one vector to another
 **************************************************/
template <class T>
Vector <T> & Vector <T> ::operator = (const Vector & rtSide) 
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


#endif // VECTOR_H

