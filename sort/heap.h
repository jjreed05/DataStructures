/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Jason Reed 
* Summary: 
*   This is my iplementation of the heapsort. This folder will swap the 
*   numbers in an array representation of the tree so that the nodes 
*   childrens is not larger than the node. This is called heapify. The
*   file utilizes the percolate down to prune the leaves.
************************************************************************/
#include <vector>
   
using namespace std;

// forward declarations
template<class T>
void heapify(vector<T> & data, int n);

template<class T>
void percolateDown(vector<T> & data, int r, int n);


/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(vector<T> & data)
{
   // get the size of the vector
   int n = data.size() - 1;
   // start from index 0
   int r = 0;
   // used for swap
   T tmp;
   
   // heapify the array
   heapify(data, n);
   
   for (int i = n; i >= 0; --i)
   {
      // do a root to leaf exchange
      tmp = data[i];
      data[i] = data[r];
      data[r] = tmp;
      
      // prune the leaf and percolate down
      percolateDown(data, r, i-1);
   }
      
}

/*************************************************************************
* This function heapifies the vector.
* Input:  data -  Vector to be heapified.
*            n -  The size of the Vector  
* Output: data -  Heapified Vector
**************************************************************************/
template<class T>
void heapify(vector<T> & data, int n)
{
   // make it so the children aren't larger 
   // than the parent
   for(int r = n/2; r >= 0; --r)
   {
      percolateDown(data, r, n);
   }
   return;
}

/*************************************************************************
* This function moves the larger children towards the end of the Vector.
* Input:  data -  Vector to be heapified.
*            r -  Variable needed to be passed in for the initial index
*            n -  Variable needed for the size of the array index
* Output: data -  Percolated Vector
**************************************************************************/
template<class T>
void percolateDown(vector<T> & data, int r, int n)
{
   // location of the left child
   int c = 2 * r;
   
   while (c <= n)
   {
      // if r has 2 children and right child is larger,
      // make c the right child
      if (c < n && data[c] < data[c + 1])
      {
         c += 1;
      }
      
      // Swap the largest child and move down to next subtree
      if (data[r] < data[c])
      {
         T tmp = data[r];
         data[r] = data[c];
         data[c] = tmp;
         
         r = c;
         c = 2 * c;
      }
      else
         break; 
   }
}
