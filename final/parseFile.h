/***********************************************************************
 * File:
 *    parseFile.h
 * Author:
 *    Jason Reed
 * Summary:
 *    This file holds my prototype for the parse file.
 ************************************************************************/
 #ifndef PARSEFILE_H
 #define PARSEFILE_H
 
 #include <iostream>
 #include <sstream>
 #include "list.h"
 #include "node.h"
 
 using namespace std;
 
 // Parse the file
 List parse(ifstream & inputFile);
 
 #endif