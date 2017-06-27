/***********************************************************************
 * Module:
 *    Week 13, Final
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Jason Reed
 * Summary:
 *    This is my implementation of the genealogy program. This file holds
 *    my main function. Main will get a filename, call a parse function, read
 *    the alphabetical sort into a file, and print out the generations.
 ************************************************************************/

#include "node.h"
#include "list.h"
#include "parseFile.h"
#include <iostream>

using namespace std;

/*******************************************
 * main()
 * The driver function for the genealogy
 * program.
 ******************************************/
int main(int argc, const char * argv[])
{
  ifstream inputFile; 
  if (argc > 1)
  {
     inputFile.open(argv[1]);
     
     // Break the Program and throw an error statement
     if(inputFile.fail())
     {
        cout << "ERROR: Failed to open file." << endl;
        return -1;
     }
  }
  else
  {
     cout << "ERROR: Please specify file." << endl;
     return -1;
  }
  
  // Create the family tree by parsing the file
  List tree = parse(inputFile);
  // Print the alpahbetical list into sorted.dat
  tree.printList();
  // Print the tree
  tree.printGen();
  
  return 0;
}

