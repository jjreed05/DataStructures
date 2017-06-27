/***********************************************************************
 * File:
 *    Node.cpp
 * Author:
 *    Jason Reed 
 * Summary:
 *    This contains my function definitons for my node class.
 ************************************************************************/

#include "node.h"

/*******************************************
 * NODE :: Node()
 * Default constructor for the Node Class 
 ******************************************/
 Node :: Node()
 {
    birth = first = last = "";
    id = 0;
    father = mother = next = NULL;
 }
 
/*******************************************
 * NODE :: Node()
 * Non-Default constructor. This constructor
 * will take in four parameters to set the 
 * the person's information.
 ******************************************/
 Node :: Node(string birth, string first, string last, int id)
 {
    this->birth = birth;
    this->first = first;
    this->last = last;
    this->id = id;
    
    father = mother = next = NULL;
 }
 
/*******************************************
 * NODE :: DISPLAY
 * This will print out the person's info. 
 ******************************************/
 void Node :: display()
 {
    if(first != "" && last != "")
       cout << first << " ";
       
    if(first != "" && last == "")
       cout << first;
    
    if(last != "")
       cout << last;
       
    if(birth != "")
       cout << ", b. " << birth;
    
    cout << endl;
 }