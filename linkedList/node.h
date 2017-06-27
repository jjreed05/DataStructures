/***********************************************************************
* Header:
*    Node
* Summary:
*    This is my node class for the linked list assignment.
*
* Author
*    Jason Reed
************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

/************************************************
 * NODE
 * A class that holds pointers and variables
 ***********************************************/
template <class T>
class Node
{  
public:
   // Default Constructor
   Node() {pNext = NULL;}
   // Non-Default Constructor
   Node(T data) {this->data = data; pNext = NULL;}
   // Pointer that points to the next Node
   Node * pNext;
   // The data of the Node
   T data;
};

/************************************************
 * COPY
 * Non-member function that copies a linked list
 ***********************************************/
template <class T>
Node <T> * copy(Node <T> * pHead)
{
   // return Null if there are no items
   if (pHead == NULL)
   {
      return NULL;
   }
   // create the new node
   Node <T> * newLink = new Node <T>;
   // set the data from first pointer
   newLink->data = pHead->data;
   // set the rest of the values
   newLink->pNext = copy(pHead->pNext);
   
   return newLink;
}

/************************************************
 * INSERT
 * Non-member function that adds another node to 
 * the list
 ***********************************************/
template <class T>
void insert(T data, Node <T> *& previous, bool headInsert = false)
{
   // create a new node for the item
   Node <T> * newNode = new Node <T>;
   // set the node's data to the parameter
   newNode->data = data;
   // if we need to insert to the head
   if (headInsert || previous == NULL)
   {
      newNode->pNext = previous;
      previous = newNode;
   }
   // place the new node onto the current list
   else
   {
      newNode->pNext = previous->pNext;
      previous->pNext = newNode;
   }
}

/************************************************
 * FIND
 * Non-member function that finds an item
 ***********************************************/
template <class T>
Node <T> * find(Node <T> *& pHead, const T & item)
{
   // create a temporary node
   Node <T> * tmp = pHead;
   // iterate through the temporary node
   while (tmp != NULL)
   {
      // if found, then return
      if (tmp->data == item)
         return tmp;
      // increment to the next node
      tmp = tmp->pNext;
   }
   return tmp;
}

/************************************************
 * DISPLAY OPERATOR
 * An operator that displays the linked list
 ***********************************************/
template <class T>
ostream & operator << (ostream & out, const Node <T> * pHead)
{
   // iterate through the data
   for (const Node <T> * p = pHead; p; p = p->pNext)
   {
      // if its the last item, display no comma
      if(p->pNext == NULL)
         out << p->data;
      // all the other items, place a comma after
      else
         out << p->data << ", ";
   }
   // return the display
   return out;
}

/************************************************
 * FREE DATA
 * A non-member function that clears the data
 ***********************************************/
template <class T>
void freeData(Node <T> *& pHead)
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
   pHead = NULL;
}


#endif