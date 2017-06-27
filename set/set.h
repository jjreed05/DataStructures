/***********************************************************************
* Header:
*    Set
* Summary:
*    This class contains the notion of a Set: bucket to hold
*    data for the user. 
*
*    This will contain the class definition of:
*       Set        : A class that holds stuff
* Author
*    Jason Reed
************************************************************************/

#ifndef SET_H
#define SET_H


#include <cassert>
#include <iostream>
#include <string>


// forward declaration for VectorIterator
template <class T>
class SetIterator;

/************************************************
 * Set
 * A class that holds stuff
 ***********************************************/
template <class T>
class Set
{
public:
   // default constructor : empty and kinda useless
   Set() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Set(const Set & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Set(int cap) throw (const char *);
   
   // destructor : free everything
   ~Set()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }
   
   // remove all the items from the container
   void clear()        { numItems = 0;                 }
   
   // return the number of elements that can be held by the allocated storage
   int capacity()       { return cap;                  }

   // how many items are currently in the container?
   int size() const    { return numItems;              }
   
   // find an item in the set
   int find(const T & t) const throw(const char *);

   // add an item to the container
   void insert(const T & t) throw (const char *);
   
   // erase an item off the set
   void erase(int item);
   
   // return an iterator to the beginning of the list
   SetIterator <T> begin() { return SetIterator<T>(data); }

   // return an iterator to the end of the list
   SetIterator <T> end() { return SetIterator<T>(data + numItems);}
   
   // overloaded assignment operator
   Set& operator = (const Set& rhs) throw (const char *);
   
   // intersection operator
   Set<T> operator && (const Set<T> rhs);
   
   // union operator
   Set<T> operator || (const Set<T> rhs);
   
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
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;           // how many items can I put on the Container before full?
   
};

/**************************************************
 * SET ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
   SetIterator() : p(NULL) {}

   // initialize to direct p to some item
   SetIterator(T * p) : p(p) {}
  
   // copy constructor
   SetIterator(const SetIterator & rhs) { *this = rhs; }
   
   // assignment operator
   SetIterator & operator = (const SetIterator & rhs)
   {
      this-> p = rhs.p;
      return *this;
   }

   // not equal operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   } 
   
   // equals operator
   bool operator == (const SetIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator ++ (int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   SetIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }
   
   // postfix decrement
   SetIterator <T> operator -- (int postfix)
   {
      SetIterator tmp(*this);
      p--;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * SET :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
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
 * SET: NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Set <T> :: Set(int cap) throw (const char *)
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
 * SET :: INSERT
 * Insert an item on the end of the vector
 **************************************************/
template <class T>
void Set <T> :: insert(const T & t) throw (const char *)
{
   // the value of find(t)
   int variable = find(t);
   SetIterator<T> location;
   
   // we are going to use this to find the location of t
   for(location = begin(); location != end(); location++)
   {
      if (*location == t)
         break;
   }
   // std::cerr << "Variable: " << variable << "  ";
   
   // push the item if it is not found on the original
   if (variable == -1)
   {
      // std::cerr << "CAP: " << cap << ". ";
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
         {
            data[i] = tmp[i];
         }
        
         // delete the temporary array  
         delete [] tmp;
         // restart the function
         insert(t);
      }
   
      // push the item if the set is empty
      if(empty())
      {
         data[0]=t;
         numItems++;
      }
      
      // if it's not empty, this is how we will push
      else if(location == end())
      {
         // std::cerr << "We are Pushing ";
         for (int i = 0; i < numItems; i++)
         {  
            // loop until the variable is greater than t
            if (data[i] > t)
            {
               // move the variables that are ahead of t
               // by one
               for (int j = numItems - 1; j >= i; j--)
               {
                  data[j+1] = data[j];
               }
               data[i] = t;
               numItems++;
               return;
            }
            // if t is greater than the last item, add 
            // t to the end
            else if(t > data[numItems-1])
            {
               data[numItems]=t;
               numItems++;
               return;
            }
         }
      }
   }
   else
      return;
   
}

/***************************************************
 * SET :: FIND
 * Finds an item in the set
 **************************************************/
 template <class T>
 int Set <T> :: find(const T & t) const throw (const char*)
 {
    // if we cannot find the item, then return -1
    int variable = -1;
    // loop through to find the item
    for(int i = 0; i < numItems; i++)
    {
       // if the item is found, return the location
       if (data[i] == t)
          variable = i;
    }
    
    return variable;
 }
 
/***************************************************
 * SET :: ERASE
 * Erase an item off the set
 **************************************************/
 template <class T>
 void Set <T> :: erase(int item)
 {
    // decrease number of items
    data[item] = data[--numItems];
    // hold the items temporarily
    T tmp;
    // loop through the items 
    for (int i = 0; i < numItems; i++)
    {  
       // loops to push the items one over
       for (int j = i + 1; j < numItems; j++)
       {
          if (data[i] > data[j])
          {
             tmp = data[i];
             data[i] = data[j];
             data[j] = tmp;
          }
       }
    }
 } 

/***************************************************
 * SET :: operator =
 * Copies the data from one vector to another
 **************************************************/
template <class T>
Set <T> & Set <T> :: operator = (const Set & rhs) 
  throw (const char *)
{
   // dont do anyting if arrays equal
   if (this == &rhs)
   {
      return *this;
   }
   else
   {
      // attempt to allocate
      try
      {
         if (rhs.cap > cap)
         {
            // deletes the old array
            delete [] data;
            
            // sets variables and conditions 
            cap = rhs.cap;
            numItems = rhs.numItems;
            
            // create the new pointer
            data = new T[rhs.cap];
         }
      }
      // throw an error code if memory cannot allocate
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
       
      // copy the data
      for (int i = 0; i < numItems; i++)
         data [i] = rhs.data[i];

      return *this;
   }
}

/***************************************************
 * SET :: OPERATOR &&
 * Combines the data from two arrays
 **************************************************/
template <class T>
Set <T> Set <T> :: operator && (const Set <T> rhs) 
{
   // the variable to return
   Set <T> intersection;
   Set <T> rtSide = rhs;
   
   // iterate through the passed in item
   for (SetIterator <T> it = rtSide.begin(); it != rtSide.end(); it++)
   {  
      // set item to the iterator
      T item = *it;
      // find the item in the left hand side set
      if (find(item) != -1)
      {
         // push it onto the new set
         intersection.insert(item);
      }
   }
   // return the new set
   return intersection;
}

/***************************************************
 * SET :: OPERATOR ||
 * Only keeps the data that are in both arrays
 **************************************************/
template <class T>
Set <T> Set <T> :: operator || (const Set<T> rhs) 
{
   // the set to return
   Set <T> intersection;
   Set <T> rtSide = rhs;
   
   // insert the left hand side to the new set
   for (int i = 0; i < numItems; i++)
   {
      intersection.insert(data[i]);
   }
   // insert the right hand side to the new set
   // the insert function will sort the variables
   for (SetIterator <T> it = rtSide.begin(); it != rtSide.end(); it++)
   {
      T item = *it;
      intersection.insert(item);
   }
   // return the new set
   return intersection;
}


#endif // SET_H

