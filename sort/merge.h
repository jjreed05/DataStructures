/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Jason Reed  
* Summary: 
*   This file is my creation of the mergesort. The mergeSort fuction calls
*   a function called split. The split function will split the list into
*   two different lists by organizing the data in sublists. The mergeSort
*   will then combine a sublist from both lists and place it back in the 
*   orginal list in sorted order. The mergeSort function will split and merge
*   the data until all of the items are sorted.
************************************************************************/
#include <list>
   
using namespace std;

// Forward Declarations
template<class T>
void split(list<T> & data, list<T> & list1, list<T> & list2);

template<class T>
void merge(list<T> & data, list<T> & list1, list<T> & list2, int & numSub);

/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template<class T>
void mergeSort(list<T> &data)
{
   // keep track of the subfolders in the data list
   int numSub;
   // these will hold the sublists
   list<T> list1;
   list<T> list2;
   
   // sort the data list
   do
   {
      split(data, list1, list2);
      merge(data, list1, list2, numSub);
      
   } while (numSub != 1);   
}

/*************************************************************************
* This function will split a linked list into two different linked lists. It
* alternately reads in a sublist into list1 or list2. A sublist is defined by
* reading an item into a sublist if it's larger than the previous item.
* If the item is smaller than the previous item, then it belongs in a new 
* sublist contained in the alternate linked list (list1 or list2).
* Input:  data -  linked list of data to be sorted.
*         list1 - linked list of data sorted in sublists
*         list2 - linked list of data sorted in sublists
* Output: data -  emptied
          list1 - sorted by sublists and holds a portion of the data
          list2 - sorted by sublists and holds the remaining portion of the
                  data
**************************************************************************/
template<class T>
void split(list<T> & data, list<T> & list1, list<T> & list2)
{
   // initialize the iterator
   typename list<T>:: iterator it = data.begin();
   // which list to push into
   bool firstList = true;
   // the previous item
   T item;
   
   // push the first item into the first list
   list1.push_back(*it);
   // set item equal to the current item
   item = *it;
   // iterate to the next item
   it++;
   
   // continue to split the list
   while(it != data.end())
   {
      // push into the first list until the item is smaller
      // than the previous item
      if(firstList == true)
      {
         // push into first list
         if(item <= *it)
         {
            list1.push_back(*it);
            item = *it;
            it++;
         }
         // push into the second list if larger than
         // the previous item
         else
         {  
            firstList = false;
            list2.push_back(*it);
            item = *it;
            it++;
         }
      }
      
      // push into the second list until the item is smaller
      // than the previous item
      else if(firstList == false)
      {
         // push into second list
         if(item <= *it)
         {
            list2.push_back(*it);
            item = *it;
            it++;
         }
         // push into first list if the item is larger
         // than the previous item
         else
         {
            firstList = true;
            list1.push_back(*it);
            item = *it;
            it++;
         }
      }
      else
         break;
   }
   
   // clear the list
   data.clear();
   
}

/*************************************************************************
* This function will merge one sublist from list1 and one sublist from list2.
* During the merge, it sorts the items in ascending order. The combined sublist
* will be pushed into the original linked list. The rest of the sublists in 
* list1 and list2 will be pushed back unto the original linked list as well.
* Input:  data -  empty
*         list1 - linked list of data sorted in sublists
*         list2 - linked list of data sorted in sublists
* Output: data -  sublist(s) of sorted data
          list1 - empty
          list2 - empty
**************************************************************************/
template<class T>
void merge(list<T> & data, list<T> & list1, list<T> & list2, int & numSub)
{
   T item;
   numSub = 0;
   
   // used to iterate through list1 and list2
   typename list<T>:: iterator it1 = list1.begin();
   typename list<T>:: iterator it2 = list2.begin();
   
   // used to keep track of where the first sublist
   // ends in list1 and list2
   typename list<T>:: iterator it3 = list1.begin();
   typename list<T>:: iterator it4 = list2.begin();
   
   // figure out where the first sublist ends for list1
   while(it3 != list1.end())
   {
      item = *it3;
      it3++;
      // break the while loop when found
      if(item > *it3)
         break;
   }

   // figure out where the first sublist ends for list2
   while(it4 != list2.end())
   {
      item = *it4;
      it4++;
      // break the while loop when found
      if(item > *it4)
         break;
   }
   
   while(it1 != list1.end() || it2 != list2.end())
   {
      // merge the first sublist from list1 and list2 together 
      // in ascending order
      while(it1 != it3 || it2 != it4)
      {
         // push list1's item unto the main list
         if(*it1 < *it2)
         {
            data.push_back(*it1);
            it1++;
         }
         // push list2's item unto the main list
         else
         {
            data.push_back(*it2);
            it2++;
         }
         
         // break the loop if these parameters are met
         if(it1 == it3)
            break;
         if(it2 == it4)
            break;
      }
      // push back the remainder of the sublist in list1
      if(it2 == it4 && it1 != it3)
      {
         while(it1 != it3)
         {
            data.push_back(*it1);
            it1++;
            if(it1 == it3)
               break;
         }
      }
      
      // push back the remainder of the sublist in list2
      if (it1 == it3 && it2 != it4 )
      {
         while(it2 != it4)
         {
            data.push_back(*it2);
            it2++;
            if(it2 == it4)
               break;
         }
      }
   
      // increment numSub
      numSub++;
      break;
   }
   
   // Copy any sublists remaining from list1
   // and increment numSub
   for(it1 = it3; it1 != list1.end(); it1++)
   {
      data.push_back(*it1);
      numSub++;
   }
   
   // Copy any sublists remaining from list2
   // and increment numSub
   for(it2 = it4; it2 != list2.end(); it2++)
   {
      data.push_back(*it2);
      numSub++;
   }
   
   // clear the lists
   list1.clear();
   list2.clear();   
   
}