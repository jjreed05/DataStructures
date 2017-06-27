/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This sorts the linked list
 * Author
 *    Jason Reed
 ************************************************************************/
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "node.h"
using namespace std;


/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   if (num > 0) 
   {
      // initialize a node
      Node <T> * sort = NULL;
      // insert the first array to the front
      insert(array[0], sort, true);
      // insert the rest of the items and sort
      for (int i = 1; i < num; ++i)
      {
         Node <T> * tmp = insertionFind(sort, array[i]);
         if (tmp == NULL)
            insert(array[i], sort, true);
         else
            insert(array[i], tmp); 
      }
      // read the list back to the array
      int i = 0;
      Node <T> * temp = sort;
      while(temp)
      {
         array[i++] = temp->data;
         temp = temp->pNext;
      }
      // free up the list
      freeData(sort); 
   }
}

/****************************************************************
 * INSERTION FIND
 * Finds an item in the list and returns a node
 ****************************************************************/
template<class T>
Node <T> * insertionFind(Node <T> * sort, T item)
{
   // We will use NULL to know if we need to insert to the head
   if (item < sort->data)
   {
      return NULL; 
   }
   else
   {
      for (Node <T> * tmp = sort; tmp; tmp = tmp->pNext)
      {
         // return the end
         if (!tmp->pNext)
         {
            return tmp; 
         }
         // return here if not head or end
         else if (!(item > tmp->pNext->data))
         {
            return tmp; 
         }
         
      }
   }
}

#endif