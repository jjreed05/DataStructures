/***********************************************************************
* Header:
*    bnode.h
* Summary:
*    This is my implementation of the binary node. This class connects
*    binary nodes which creates a binary tree. Each binary node has an
*    add left and add righ in order to add children to the binary node. 
*    This is all connected using pointers. We also have a pointer that 
*    will point to the parent node. Each binary node has a template variable
*    that will hold information.
*
* Author
*    Jason Reed
************************************************************************/

#ifndef BNODE_H
#define BNODE_H

template <class T>
class BinaryNode
{
// All items are public for this class
public:
   // Default Constructor
   BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL), data(NULL) {}
      
   // Non-Default Constructor
   BinaryNode(T data) : pLeft(NULL), pRight(NULL), pParent(NULL)
      { this->data = data; }
   
   // Assignment Operator
   BinaryNode<T> & operator = (const BinaryNode * rhs);
   
   // Add a new node to the left
   BinaryNode & addLeft(T data) throw (const char *);
   BinaryNode & addLeft(BinaryNode * node) throw (const char *);
   
   // Add a new node to the right
   BinaryNode & addRight(T data) throw (const char *);
   BinaryNode & addRight(BinaryNode * node) throw (const char *);
   
   // Use this to calculate numItems
   void calculateSize(BinaryNode * node);
   
   // Initialize numItems and call the calculateSize function
   int size() {numItems = 0; calculateSize(this); return numItems;}
   
   // Variables needed for our BNode
   BinaryNode * pParent;
   BinaryNode * pLeft;
   BinaryNode * pRight;
   int numItems;
   T data;
};

/*******************************************
 * Operator: equals
 * Summary: Will take in a right hand side 
 * binary node. This operator will set all
 * the variables equal to the right hand side
 * variables.
 * Parameters: BinaryNode<T> * rhs
 * Return: *this
 *******************************************/
template <class T>
BinaryNode<T> & BinaryNode<T> :: operator = (const BinaryNode<T> * rhs)
{
   // set everything to the right hand side
   this->parent = rhs.parent;
   this->pLeft = rhs.pLeft;
   this->pRight = rhs.pRight;
   this->data = rhs.data;
   
   return *this;
}

/*******************************************
 * Function: Add Left
 * Summary: This function takes in a T data parameter 
 * and creates a new binary node and pushing the 
 * data into it by using the non-default constructor.
 * This function will then link the pointers.
 * It will add to the left of the parent node.
 * Parameters: T data
 * Return: *this
 *******************************************/
template <class T>
BinaryNode<T> & BinaryNode<T> :: addLeft(T data) throw (const char *)
{
   try
   {  
      // allocate a new node and use the non-default constructor
      BinaryNode<T> * newLeft = new BinaryNode<T>(data);
      // link the left pointer for this object
      this->pLeft = newLeft;
      // link the parent pointer for the new node
      newLeft->pParent = this;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}

/*******************************************
 * Function: Add Left
 * Summary: This function takes in a node * parameter.
 * We do not need to allocate a new binary node since
 * one has been passed in. This function just links
 * the pointers to the parent node and links it as
 * a child. It will add to left of the parent node.
 * Parameters: BinaryNode * node
 * Return: *this
 *******************************************/
template <class T>
BinaryNode<T> & BinaryNode<T> :: addLeft(BinaryNode * node) throw (const char *)
{   
   try
   {  
      // Link the pointers
      if (node != NULL)
      {
         this->pLeft = node;
         node->pParent = this;
      }
      // we do not want to link a null binary node 
      else
      {
         this->pLeft = NULL;
      }
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}

/*******************************************
 * Function: Add Right
 * Summary: This function takes in a T data parameter 
 * and creates a new binary node and pushing the 
 * data into it by using the non-default constructor.
 * This function will then link the pointers.
 * It will add to the right of the parent node.
 * Parameters: T data
 * Return: *this
 *******************************************/
template <class T>
BinaryNode<T> & BinaryNode<T> :: addRight(T data) throw (const char *)
{
   try
   {
      // allocate a new Binary Node
      BinaryNode<T> * newRight = new BinaryNode<T>(data);
      // link the pointers
      this->pRight = newRight;
      newRight->pParent = this;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}

/*******************************************
 * Function: Add Right
 * Summary: This function takes in a node * parameter.
 * We do not need to allocate a new binary node since
 * one has been passed in. This function just links
 * the pointers to the parent node and links it as
 * a child. It will add to right of the parent node.
 * Parameters: BinaryNode * node
 * Return: *this
 *******************************************/
template <class T>
BinaryNode<T> & BinaryNode<T> :: addRight(BinaryNode * node) throw (const char *)
{  
   try
   {
      // link the pointers
      if (node != NULL)
      {
         this->pRight = node;
         node->pParent = this;
      }
      // do not link a null node
      else
      {
         this->pRight = NULL;
      }
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return *this;
}

/*******************************************
 * Function: Calculate Size
 * Summary: This function takes in a node * parameter.
 * It uses recursion to count the number of items by
 * going through the pointers until it reaches NULL.
 * Parameters: BinaryNode * node
 *******************************************/
template <class T>
void BinaryNode<T> :: calculateSize(BinaryNode<T> * node)
{
   if(node == NULL)
      return;
   // Go through each left binary node
   if (node->pLeft)
      calculateSize(node->pLeft);
   // Go through each right binary node  
   if (node->pRight)
      calculateSize(node->pRight);
   // increment numItems each time   
   numItems++;
}

/*******************************************
 * Function: Delete Binary Tree
 * Summary: This function takes in a node * parameter.
 * It uses recursion to delete the binary nodes by
 * going through the pointers until it reaches NULL.
 * Parameters: BinaryNode * node
 *******************************************/
template <class T>
void deleteBinaryTree(BinaryNode<T> * node)
{
   if (node == NULL)
      return;
   // go through the left
   if(node->pLeft)
      deleteBinaryTree(node->pLeft);
   // go through the right  
   if(node->pRight)
      deleteBinaryTree(node->pRight);
   
   node = NULL;
   delete node;
}

/*******************************************
 * Operator: stream extraction operator
 * Summary: This operator will display the
 * data held in the binary node.
 * Parameters: ostream & out, BinaryNode * rhs
 *******************************************/
template <class T>
std::ostream & operator << (std::ostream & out, const BinaryNode<T> *rhs)
{
   if(!rhs) 
      return out;
   // if its not NULL, return the display
   return out << rhs->pLeft << rhs->data << " " << rhs->pRight;
}

#endif

