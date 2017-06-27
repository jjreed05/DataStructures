/***********************************************************************
 * Module:
 *    list.h
 * Author:
 *    Jason Reed
 * Summary:
 *    This header file holds the means of my list class implementation.
 *    It is a list class tailored specifically for the genealogy program.
 *    The program inserts a node of records in alphabetical order.
 *    I did not need the remove, copy constructory, and assignment operator
 *    for my program. So, I coded what I needed for this list class.
 ************************************************************************/
 
 #ifndef LIST_H
 #define LIST_H
 
 #include "node.h"
 #include <fstream>
 #include <string>
 #include <iostream>
 #include <sstream>

 using namespace std;

 /*******************************************
 * Class: List
 * This is my implementation of list. It is
 * tailored specifically for the genealogy 
 * program. 
 ******************************************/
 class List
 {
  public:
    // Constructor
    List() {node = NULL; numItems = 0;}
    // Destructor
    ~List();
    // Insert a node to the List
    void push_alpha(Node * newNode);
    // Search for a position of an item
    int search(int id) const;
    // Getters
    Node * getNode(int it) const;
    int getNumItems() const {return numItems;}
    // Is the list empty
    bool empty() const {return numItems == 0;}
    // Print the alphabetical list
    void printList() const;
    // Go through the node pointers and print
    void printGen();
    
 private:
    Node * node;
    int numItems;
 };
 
#endif