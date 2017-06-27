/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
* Author:
*    Jason Reed
* Summary: 
*    The driver function to test the heap and merge algorithms. This program
*    will prompt the user if he or she wants to see a heap or merge sort. 
*    It will then prompt the user for a file to be sorted. This program 
*    will read in a file and then call either heap or merge sort depending
*    on the user's input.
************************************************************************/

#include <iostream>        // for CIN and COUT
#include <cstring>         // for strcmp
#include <iomanip>         // for SETW
#include <fstream>         // for fin 
#include <vector>          // for vector
#include <list>            // for list
#include "heap.h"
#include "merge.h"

using namespace std;

/**********************************************************************
 * MAIN
 * Gets the sort type and filename from the command line. If the sort type
 * or filename are not entered on the command line, the user will be
 * prompted for the sort type and/or filename.
 * Call the appropriate sort to sort the data contained in the vector or
 * linked list and display the sorted data to the console.
 ***********************************************************************/
int main(int argc, const char* argv[])
{
   char sortType[10];
   char fileName[50];
   if (argc == 1)
   {
      cout << "Which sort merge or heap? ";
      cin >> sortType;
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }
   else if (argc == 2)
   {
      strcpy(sortType,argv[1]);
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }
   else if (argc == 3)
   {
      strcpy(sortType,argv[1]);    
      strcpy(fileName,argv[2]);
   }
   
   if (strcmp(sortType, "heap") == 0)
   {
         // TO DO: read the file into a vector
         //        call your heapsort passing the vector as a parameter
         //        output the sorted vector to the console.
         
         // vector to hold the data to be sorted
         vector<int> data;
         
         // item to be inserted
         int items;
         
         // open the file stream
         ifstream fin(fileName);
         
         // break the program if corrupted filename
         if (fin.fail())
         {
            cout << "Error reading file. " << endl;
            return -1;
         }
         
         // read the file into the vector
         while (fin >> items)
         {
            data.push_back(items);
         }       
         
         // sort the data
         heapSort(data);
         
         // Variable to only allow max of 10 words per line
         int count = 0;
         
         // iterate through the vector and display 3 spaces apart
         // and 10 numbers per line
         vector<int> :: iterator it;
         for (it = data.begin(); it != data.end(); it++)
         {
            if (count != 10)
               cout << setw(3) << *it;
            if (count == 10)
            {
               cout << endl;
               cout << setw(3) << *it;
               count = 0;
            }
            count ++;
         }
         cout << endl;
         
         // free up memory
         data.clear();
         
   }
   else if (strcmp(sortType, "merge") == 0)
   {
         // TO DO: read the file into a linked list
         //        call your natural merge sort
         //        output the sorted linked list to the console.
         
         // linked list to hold the data to be sorted
         list<int> data;
         
         // item to be inserted
         int items;
         
         // open the file stream
         ifstream fin(fileName);
         
         // break the program if fileName is corrupt
         if (fin.fail())
         {
            cout << "Error reading file. " << endl;
            return -1;
         }
         
         // read the items into the linked list
         while (fin >> items)
         {
            data.push_back(items);
         }
         
         // Sort the items using a natural mergesort
         mergeSort(data);
         
         // Display the sorted list correctly
         int count = 0;
         list<int> :: iterator it;
         for (it = data.begin(); it != data.end(); it++)
         {
            if (count != 10)
               cout << setw(3) << *it;
            if (count == 10)
            {
               cout << endl;
               cout << setw(3) << *it;
               count = 0;
            }
            count ++;
         }
         cout << endl;  
         
         // free up the memory
         data.clear();   
   }
   else
   {
      cout << "\nInvalid sort name - must be 'heap' or 'merge'" << endl;
   }
   
   return 0;
}
