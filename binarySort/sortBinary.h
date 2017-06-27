/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Jason Reed
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include "bnode.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   // create a BST variable
   BST<T> sortTree;
   
   // loop through the array and insert the 
   // data onto the sortTree
   for (int i = 0; i < num; i++)
   {
      sortTree.insert(array[i]);
   }
   
   // reset i to 0 for the iterator
   int i = 0;
   // create an iterator variable
   BSTIterator<T> it;
   // iterate through the sortTree
   for (it = sortTree.begin(); it!= sortTree.end(); it++)
   {
      array[i] = *it;
      i++;
   }
   // clear the sortTree
   sortTree.clear();
   
}


#endif // SORT_BINARY_H
