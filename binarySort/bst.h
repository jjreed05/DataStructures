/***********************************************************************
* Header:
*    bst.h
* Summary:
*     This is my creation of the Binary Search Tree. It uses Binary Nodes
*     to store data and point either right, left, or up to a parent node.
*     These pointers sort the data into a tree structure. This file uses
*     an iterator to go through the data in the tree. This Binary Search
*     tree is similar to the STL Binary Search Tree.
*    
* Author
*    Jason Reed
************************************************************************/


#ifndef BST_H
#define BST_H

#include <cassert>
#include <iostream>
#include "stack.h"
#include "bnode.h"

// forward declaration for the BST iterator
template <class T>
class BSTIterator;

/*******************************************
 * Class: BST
 * Summary: An object that is similar to the 
 * STL Binary Search Tree. This class will
 * use a Binary Node to sort a tree to the
 * specifications of a Binary Search Tree.
 * The right data will always be larger than
 * the left.
 *******************************************/
template <class T>
class BST
{
public:
   // Default Constructor
   BST() : pRoot(NULL) {}
   
   // Copy Constructor
   BST(BST<T> & rhs) throw (const char *);
   
   // Destructor
   ~BST() {clear(); }
   
   // Assignment Operator
   BST<T> & operator = (BST<T> & rhs) throw (const char *);
   
   // Returns true if empty
   bool empty() {return pRoot == NULL; }
   
   // Returns the size of the object
   int size() {if(!empty()) return pRoot->size(); }
   
   // Deletes all the itemts in the binary tree
   void clear() { deleteBinaryTree(pRoot); pRoot = NULL; }   
   
   // Inserts a data item and creates a node
   void insert(const T & t) throw (const char *);
   
   // remove an item
   void remove(BSTIterator<T> & it) throw (const char *);
   
   // we will use this to copy the items over               
   void copyRHS(BinaryNode<T> * & lhs, BinaryNode<T> * & rhs);
   
   // find a given item
   BSTIterator <T> find(const T & t);
   
   // items needed for the iterator
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
   
private:
   BinaryNode <T> * pRoot;
};

/*******************************************
 * Constructor: Copy
 * Summary: This will take in a right hand side
 * BST object by reference and copy the items
 * from it to construct a new BST object.
 * Parameters: const BST & rhs
 *******************************************/
template <class T>
BST<T> :: BST(BST<T> & rhs) throw (const char *)
{
   // use this function to copy the items over
    copyRHS(pRoot, rhs.pRoot);
}

/*******************************************
 * Operator: Assignment
 * Summary: This will take in a right hand side
 * BST object by reference and copy the items
 * over to this BST.
 * Parameters: const BST & rhs
 *******************************************/
template <class T>
BST<T> & BST<T> :: operator = (BST<T> & rhs) throw (const char *)
{  
   // set it to NULL if rhs is NULL
   if (rhs.pRoot == NULL)
      pRoot = NULL;
      
   else
      try
      {
         // allocate a new binary node using the copy 
         // copy constructor
         pRoot = new BinaryNode<T>(rhs.pRoot->data);
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      } 
   // copy the items over 
   copyRHS(pRoot, rhs.pRoot);
      
   return *this;
}

/*******************************************
 * Function: Insert
 * Summary: This will take in a data item. 
 * This function will then create a node
 * to hold the data and place that node in 
 * the correct place on the binary tree.
 * Parameters: T & t
 *******************************************/
template <class T>
void BST<T> :: insert(const T & t) throw (const char *)
{
   // algorithm from the text
   // few modifications
   try
   {
      // location pointer
      BinaryNode<T> * locptr = pRoot;
      BinaryNode<T> * parent = NULL;

      while (locptr != NULL) 
      {
         parent = locptr;
         
         if (t < locptr->data)       // descend left
            locptr = locptr->pLeft;
            
         else
            locptr = locptr->pRight; // descend right
      }
      
      // create a new node using the copy constructor
      locptr = new BinaryNode<T>(t);
      
      // empty tree
      if(parent == NULL)
         pRoot = locptr;
         
      // insert to the left  
      else if (t < parent->data)
      {
         parent->pLeft = locptr;
         locptr->pParent = parent;
      }
      
      // insert to the right
      else
      {
         parent->pRight = locptr;
         locptr->pParent = parent;
      }

   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(BSTIterator<T> & it) throw (const char *)
{

   if (it.getNode() == NULL)
      throw "ERROR: null iterator";
   
   // if the items has two children
   if (it.getNode()->pLeft != NULL && it.getNode()->pRight != NULL)
   {
      // create a temp to hold the data
      BinaryNode <T> * pTemp = it.getNode();
      // inorder successor
      ++it;
      // copy over the items off temp
      pTemp->data = it.getNode()->data;
      // recurse
      remove(it);
   }
   
   // less than two children
   else
   {
      // left
      if (it.getNode()->pParent->pLeft == it.getNode())
      {
         // left or right child?
         if (it.getNode()->pLeft != NULL)
         {
            // link child and link parent
            it.getNode()->pParent->pLeft = it.getNode()->pLeft;
            it.getNode()->pLeft->pParent = it.getNode()->pParent;
         }
         else
         {
            // link child and link parent
            it.getNode()->pParent->pLeft = it.getNode()->pRight;
            if (it.getNode()->pLeft != NULL)
               it.getNode()->pLeft->pParent = it.getNode()->pParent;
         }
      }
      else
      {
         // right child
         if (it.getNode()->pLeft != NULL)
         {
            it.getNode()->pParent->pRight = it.getNode()->pLeft;
            it.getNode()->pLeft->pParent = it.getNode()->pParent;
         }
         else
         {
            it.getNode()->pParent->pRight = it.getNode()->pRight;
            if (it.getNode()->pRight != NULL)
               it.getNode()->pRight->pParent = it.getNode()->pParent;
         }
      }

      // delete the node
      delete it.getNode();
      
   }
}

/*************************************************
 * BST :: copyRHS
 * This allows us to copy the items from one Binary
 * Node to the other. We will use this for our 
 * assignment operator and copy constructor.
 ************************************************/
template <class T>
void BST<T> :: copyRHS(BinaryNode<T> * & lhs, BinaryNode<T> * & rhs)
{
   // Do not proceed if rhs is NULL
   if (rhs == NULL)
   {
      lhs = NULL;
   }
   else
   {
      // allocate a new binary node
      lhs = new BinaryNode<T>(rhs->data);
      
      // copy the left and the right recursively from rhs 
      copyRHS(lhs->pLeft, rhs->pLeft);
      copyRHS(lhs->pRight, rhs->pRight);
   }
   
      
}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   // create a new variable and set it to the root
   BinaryNode<T> * findNode = pRoot;
   // go down findNode
   while (findNode)
   {
      // go down the left
      if (findNode->data > t)
         findNode = findNode->pLeft;
      // return iterator if we have found the node  
      else if (findNode->data == t)
         return BSTIterator<T>(findNode);
      // go down the right
      else
         findNode = findNode->pRight;
   }
   
   return end();
}

/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(pRoot);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return BSTIterator<T>(nodes);   
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(pRoot);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return BSTIterator<T>(nodes);
}  

/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }
   bool operator < (const T & t)
   {
      return nodes.const_top() < t;
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()  
   {
      return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(BSTIterator <T> & it);

private:
   
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }
      
   return *this;      
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}


#endif