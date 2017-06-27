/***********************************************************************
 * Module:
 *    Week 12, Hash
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Jason Reed
 * Summary:
 *    
 ************************************************************************/

#ifndef HASH_H
#define HASH_H

#include "list.h"

/**********************************************************************
 * class Hash
 * This is my implementation of the Hash table. This table is an array
 * of lists that will alow us to handle collisions. It inserts an items
 * into the table. If the item already exists in a slot, it will then
 * put it into the next slot on the list.
 ***********************************************************************/
template <class T>
class Hash
{
public:
   // Default Constructor
   Hash() throw (const char*);
   
   // Non-Default Constructor
   Hash(int & numBuckets) throw (const char*);
   
   // Copy Constructor
   Hash(const Hash<T> & rhs) throw (const char*);
   
   // Destructor
   ~Hash() { clear(); numBuckets = 0; delete[] table;}
   
   // Determines whether the Hash is empty
   bool empty() {return numItems == 0;}
   
   // Returns the number of elements
   int size() {return numItems;}
   
   // Returns the number of buckets
   int capacity() const {return numBuckets;}
   
   // Clear the contents
   void clear();
   
   // Finds the parameter
   bool find(const T item);
   
   // Inserts the parameter into the Hash
   void insert(const T & item);
   
   // Assignment operator
   Hash & operator = (const Hash<T> & rhs) throw (const char*);

protected:
   // Virtual function that determines the key value
   virtual int hash(const T & item) const = 0;
   List<T> * table; 
   int numItems;
   int numBuckets;
   
};

/*******************************************
 * Hash :: Default Constructor
 * This is the default constructor for the
 * hash table. 
 ******************************************/
template <class T>
Hash<T> :: Hash() throw (const char*)
{
   try
   {
      numItems = 0;
      numBuckets = 0;
      table = new List<T>[numBuckets];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: unable to allocate memory for the hash";
   }
}

/*******************************************
 * Hash :: Non-Default Constructor
 * This takes the numBuckets as a parameter
 * and sets the object's numBuckets to that
 * parameter.
 ******************************************/
template <class T>
Hash<T> :: Hash(int & numBuckets) throw (const char*)
{
   try
   {
      this->numItems = 0;
      this->numBuckets = numBuckets;
      this->table = new List<T>[numBuckets];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: unable to allocate memory for the hash";
   }
}

/*******************************************
 * Hash :: Copy Constructor
 * This copies the items from one hash table
 * to the other.
 ******************************************/
 template <class T>
 Hash<T> :: Hash(const Hash<T> & rhs) throw (const char*)
 {
    // Copy over the items
    try
    {
       this->numItems = rhs.numItems;
       this->numBuckets = rhs.numBuckets;
       this->table = new List<T>[numBuckets];
       
       // use a for loop to go through the list and 
       // copy the items over
       for (int i = 0; i < rhs.numBuckets; i++)
       {
          this->table[i] = rhs.table[i];
       }
    }
    catch(std::bad_alloc)
    {
       throw "ERROR: unable to allocate memory for the hash";
    }
 }
 
/*******************************************
 * Hash :: clear()
 * This function will clear the contents
 * off the table and set the number of items
 * to 0.
 ******************************************/
 template <class T>
 void Hash<T> :: clear()
 {
    if(!empty())
    {
       for (int i = 0; i < numBuckets; i++)
       {
          table[i].clear();
       }
    }
    numItems = 0;
 }
 
/*******************************************
 * Hash :: Assignment Operator
 * This takes an item from the right hand side
 * and sets this object equal to it. 
 ******************************************/
 template <class T>
 Hash<T> & Hash<T> :: operator = (const Hash<T> & rhs) throw (const char*)
 {
    try
    {
       // ensure that this table is empty
       if (table != NULL)
       {
          // clear the contents from the table
          clear();
          delete[] table;
       }
       
       // set the variables
       this->numItems = rhs.numItems;
       this->numBuckets = rhs.numBuckets;
       
       // allocate a new table
       this->table = new List<T> [numBuckets];
       
       // copy over the contents
       for (int i = 0; i < rhs.numBuckets; i++)
       {
          this->table[i] = rhs.table[i];
       }
    }
    catch(std::bad_alloc)
    {
       throw "ERROR: unable to allocate memory for the hash";
    }
    
    return *this;
 }
 
/*******************************************
 * Hash :: Insert()
 * Puts the item into the bucket using the
 * pure virtual function. 
 ******************************************/
 template <class T>
 void Hash<T> :: insert(const T & item)
 {
    // determine the key placement on the array
    int place = hash(item);
    // push the item into the array of lists
    table[place].push_back(item);
    // increment
    numItems++;
 }
 
/*******************************************
 * Hash :: find()
 * Finds the item in the array 
 ******************************************/
 template <class T>
 bool Hash<T> :: find(const T item)
 {
    // determine the key placement on the array
    int place = hash(item);
    // Iterate through the list 
    ListIterator <T> it;
    for(it = table[place].begin(); it != table[place].end(); it++)
    {
       // return true if found
       if(*it == item)
          return true;
    }
 }

#endif // HASH_H
