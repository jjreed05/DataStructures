/***********************************************************************
* Header:
*    list.h
* Summary:
*    This is the header file for my implementation of the List Class and
*    a List Iterator. The List class will work similarly to the standard
*    template library's notion of a list
*
* Author
*    Jason Reed
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <iostream>

// forward declarations
template <class T>
class List;

template <class T>
class ListIterator;

using namespace std;

/************************************************
 * NODE
 * A class that holds pointers and variables needed
 * for the List. The only changes I have made to 
 * this Node class from last week was that I added
 * a pointer for previous item and added friends.
 ***********************************************/
template <class T>
class Node
{  
public:
   // Default Constructor
   Node() {pNext = NULL;}
   
   // Non-Default Constructor
   Node(T data) {this->data = data; pNext = NULL; pPrevious = NULL;}

   // Allow these classes to mdify the node class by making them friends
   friend class List <T>;
   friend class ListIterator <T>;
   
   // The data of the Node
   T data;
   
   // Pointer that points to the next Node
   Node * pNext;
   
   // Pointer to the previous node
   Node * pPrevious;
};

/************************************************
 * LIST
 * A container for the linked list. This class
 * will use the Node and ListIterator classes. 
 * This List class has several functions that
 * allows insertion anywhere. We have an iterator
 * class that lets us iterate through the list
 * container by uisng begin and end functions as 
 * well as reverse begin and end functions.
 ***********************************************/
template <class T>
class List
{
public:
   // default constructor
   List() {pHead = NULL; pTail = NULL; numItems = 0;}
   
   // copy constructor
   List(const List & rhs) throw (const char *);
   
   // destructor
   ~List() {freeData(this->pHead);}
   
   // assignment operator
   List <T> & operator = (const List & rhs) throw (const char*);
   
   // check to see if the list is empty
   bool empty() const {return numItems == 0;}
   
   // clear the data in the container
   void clear() {freeData(this->pHead);}
   
   // return the size of the container
   int size () const {return numItems;}
   
   // insert an item to the tail of the list
   void push_back(const T & t) throw (const char *);
   
   // insert an item to the head of the list
   void push_front(const T & t) throw (const char *);
   
   // return the first item in the list
   T & front() throw (const char *);
   
   // return the last item in the list
   T & back() throw (const char *);
   
   // return an iterator of the head
   ListIterator <T> begin() const {return ListIterator <T> (pHead);}
   
   // return an iterator to the end of the list
   ListIterator <T> end() const {return ListIterator <T> (NULL);}
   
   // return a reverse iterator from the tail
   ListIterator <T> rbegin() const {return ListIterator <T> (pTail);}
   
   // return a reverse iterator to the end of the list
   ListIterator <T> rend() const {return ListIterator <T> (NULL);}
   
   // insert an item in the middle
   void insert(ListIterator <T> it, const T & t) throw (const char *);
   
   // remove from the middle of the list
   void remove(ListIterator <T> it) throw (const char *);
   
   
private:
   // pointer to the items
   Node <T> * pHead;
   
   // pointer to the last item
   Node <T> * pTail;
   
   // variable for the number of items
   int numItems;
   
   // clear all of the data
   void freeData(Node <T> *& pHead);
};

/************************************************
 * LIST ITERATOR
 * This is the class that allows us to iterate
 * through the list container. I assigned the 
 * needed operators. I have added the functions,
 * remove() and insert(), as friends in order to 
 * access the pointer in the class from the list.
 ***********************************************/
template <class T>
class ListIterator
{
public:
   // default constructor
   ListIterator() : p(NULL) {}

   // initialize p to some item
   ListIterator(Node <T> * p) : p(p) {}
  
   // copy constructor
   ListIterator(const ListIterator & rhs) { *this = rhs; }
   
   // assignment operator
   ListIterator & operator = (const ListIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equal operator
   bool operator != (const ListIterator & rhs) const
   {
      return rhs.p != this->p;
   } 
   
   // equals operator
   bool operator == (const ListIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return p->data;
   }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }

   // postfix increment
   ListIterator <T> operator ++ (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pNext;
      return tmp;
   }
   
   // prefix decrement
   ListIterator <T> & operator -- ()
   {
      p = p->pPrevious;
      return *this;
   }
   
   // postfix decrement
   ListIterator <T> operator -- (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pPrevious;
      return tmp;
   }
   
  private:
   Node <T> * p;
   
   // make friends with this function in order to access p
   friend void List <T> :: insert(ListIterator <T> it, const T & t) throw (const char *);
   
   friend void List <T> :: remove(ListIterator <T> it) throw (const char *);

};

/************************************************
 * LIST :: COPY CONSTRUCTOR
 * Constructs a container by copying in another
 * container
 * Parameters:
 *   - List <T> rhs: Pass in a list container by 
 *                   reference to copy the data.
 ***********************************************/
template <class T>
List <T> :: List(const List <T> & rhs) throw (const char *)
{
   // set the items to null
   this->pHead = NULL;
   this->pTail = NULL;
   
   // no items yet
   this->numItems = 0;
   
   // create a temporary node and set it to the rhs head
   Node<T> * tmp = rhs.pHead;
   // loop tmp until NULL
   while (tmp != NULL)
   {
      // push items from tmp to actual node
      this->push_back(tmp->data);
      // advance the temporary node
      tmp = tmp->pNext;
   }
}

/************************************************
 * LIST :: ASSINGMENT OPERATOR
 * Copies over data from one list to the other
 * Parameters:
 *    - List <T> rhs: Pass in a list container by
 *                    reference to copy the data.
 * Return: this pointer
 ***********************************************/
template <class T>
List <T> & List <T> :: operator = (const List <T> & rhs) 
   throw (const char *)
{
   try
   {
      // first we need to clear the items off of 
      // the original list
      this->freeData(this->pHead);
      
      // set the number of items from rhs to the actual
      this->numItems = rhs.numItems;
      
      // create a new node for the head
      this->pHead = new Node <T>;
      
      // create a tmp node and set it to the head
      Node <T> * tmp = this->pHead;
      
      // create a tmp node for rhs and set it to rhs head
      Node <T> * rhsTmp = rhs.pHead;
      
      // insert the rhs tmp data to tmp
      tmp->data = rhsTmp->data;
      
      // set the tail of actual to tmp
      this->pTail = tmp;
      
      // loop through to the end of the list
      while(rhsTmp->pNext)
      {
         // create a new node and input rhs data
         tmp->pNext = new Node <T> (rhsTmp->pNext->data);
         
         // set the previous node to tmp
         tmp->pNext->pPrevious = tmp;
         
         // advance tmp
         tmp = tmp->pNext;
         
         // advance rhs tmp
         rhsTmp = rhsTmp->pNext;
         
         // set the actual node's tail to tmp
         this->pTail = tmp;
      }
      // return the actual list
      return *this;
   }
   
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   
}

/************************************************
 * LIST :: FREE DATA
 * A private function that deletes all of the 
 * nodes in the list
 * Parameters:
 *  - Node <T> pHead: Pass in a head node by 
 *                    reference.
 * Return: nothing
 ***********************************************/
template <class T>
void List <T> :: freeData(Node <T> *& pHead)
{
   // create a temporary node pointer
   Node <T> * tmp = pHead;
   
   // iterate through the temporary node pointer
   while (tmp != NULL)
   {
      // set the head to next node
      pHead = pHead->pNext;
      // delete the item that tmp is pointing to
      delete tmp;
      // set tmp to the head again
      tmp = pHead;
   }
   
   // all items deleted, set the head to NULL
   this->pHead = NULL;
   // set the tail to NULL
   this->pTail = NULL;
   // set numItems to 0
   this->numItems = 0; 
}

/************************************************
 * LIST :: PUSH_BACK
 * A fucntion that allows us to push an item to 
 * the back of the list
 * Parameters:
 *    - T t: a data item passed in by reference
 * Return: nothing
 ***********************************************/
template <class T>
void List <T> :: push_back(const T & t) throw (const char *)
{
   try
   {
      // create a new node for the item
      Node <T> * newNode = new Node <T> (t);
      
      // set the node's data to the parameter
      newNode->pPrevious = this->pTail;
      
      // point to the new tail if its not a first time insertion
      if (this->pTail)
         this->pTail->pNext = newNode;
      
      // set the new tail
      pTail = newNode;
      
      // for pushing an item for the first time
      if (pHead == NULL)
         pHead = newNode;
      
      numItems++;
   }
   
   catch (bad_alloc)
   {
      throw "Error: Could not allocate a new node for list";
   }
}

/************************************************
 * LIST :: PUSH_FRONT
 * A fucntion that allows us to push an item to 
 * the front of the list
 * Parameter:
 *   - T t: a data item passed in by reference
 * Return: nothing
 ***********************************************/
template <class T>
void List <T> :: push_front(const T & t) throw (const char *)
{
   try
   {
      // create a new node for the item
      Node <T> * newNode = new Node <T> (t);
      
      // set the node's data to the parameter
      newNode->pNext = this->pHead;
      
      // since we do not have an item before the head,
      // then set the new nodes pPrev to NULL
      newNode->pPrevious = NULL;
      
      // have the original previous node equal the head if it's
      // not a first time insertion
      if (pHead != NULL)
         this->pHead->pPrevious = newNode;
      
      // for first time insertions,
      // make the tail point to the new node
      if(pTail == NULL)
         pTail = newNode;
      
      // set the new head
      pHead = newNode;
      // increase the number of items
      numItems++;
   }
   
   catch (bad_alloc)
   {
      throw "Error: Could not allocate a new node for list";
   }
}

/************************************************
 * LIST :: FRONT
 * A fucntion that allows us to return the data
 * from the front of the list
 * Return: T data
 ***********************************************/
template <class T>
T & List <T> :: front() throw (const char *)
{
   try
   {
      return pHead->data;
   }
   
   catch (bad_alloc)
   {
      throw "Error: Could not allocate a new node for list";
   }
}

/************************************************
 * LIST :: BACK
 * A fucntion that allows us to return the data 
 * of the tail of the list
 * Return: T data
 ***********************************************/
template <class T>
T & List <T> :: back() throw (const char *)
{
   try
   {
      return pTail->data;
   }
   
   catch (bad_alloc)
   {
      throw "Error: Could not allocate a new node for list";
   }
}

/************************************************
 * LIST :: INSERT
 * A function that allows us to insert anywhere 
 * in the list. It will create a new node and place
 * that Node at specific location. This function
 * reorganizes the pointers according the placement
 * of the new Node.
 * Parameters:
 *  - ListIterator <T> it: An iterator object for
 *                         the location
 *  - T t: data item
 * Return: nothing
 ***********************************************/
template <class T>
void List <T> :: insert(ListIterator <T> it, const T & t) 
   throw (const char *)
{
   try
   {
      // create a temporary node
      Node <T> * tmp = new Node <T> (t);
   
      // if there are no items, then set head
      // and tail to tmp
      if (pHead == NULL)
      {
         pHead = tmp;
         pTail = tmp;
      }
   
      // if the point is at the end,
      // then insert at the end
      else if (it == end())
      {
         // set the next item to tmp
         pTail->pNext = tmp;
      
         // the previous item is the old tail
         tmp->pPrevious = pTail;
      
         // the new tail is tmp
         pTail = tmp;
      }
   
      // this will insert in the middle
      else
      {
         // place the item in the list
         tmp->pNext = it.p;
      
         // set the previous item
         tmp->pPrevious = it.p->pPrevious;
      
         // set it's previous item to tmp
         it.p->pPrevious = tmp;
      
         // insert at the beginning
         if (it == pHead)
            pHead = tmp;
         
         // insert in the middle
         else
            tmp->pPrevious->pNext = tmp;
      }
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to remove from an empty list";
   }
   
}

/************************************************
 * LIST :: REMOVE
 * A function that allows us to remove anywhere 
 * in the list. It will reorganize the pointers
 * accordingly and delete the item off the list.
 *  - ListIterator <T> it: An iterator object for
 *                         the location
 * Return: nothing
 ***********************************************/
template <class T>
void List <T> :: remove(ListIterator <T> it) throw (const char *)
{
   try
   {
      // delete the tail
      if (it.p == pTail)
      {
         // set the pointer to NULL
         it.p->pPrevious->pNext = NULL;
         // the tail is now the previous item
         pTail = it.p->pPrevious;
         // delete the item
         delete it.p;
      }
      // delete the head
      else if (it.p == pHead)
      {   
         // set the pointer to NULL
         it.p->pNext->pPrevious = NULL;
         // the head is now the next item on the list
         pHead = it.p->pNext;
         // delete the item
         delete it.p;
      }
      // delete in the middle
      else
      {
         // the pointer points to the item after it
         it.p->pPrevious->pNext = it.p->pNext;
         // the pointer after it points to the item before it
         it.p->pNext->pPrevious = it.p->pPrevious;
         // delete the item
         delete it.p;
      }
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to remove from an empty list";
   }
   
}
#endif