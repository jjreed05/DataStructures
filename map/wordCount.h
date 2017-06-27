/***********************************************************************
* Header:
*    Word Count  
* Summary:
*    This programs implements the usage of a map STL. This program reads
*    in a text file. It cleans up all punctuation except for the hyphen.
*    The program then reads the words into a map and increments it's frequency.
*    Then, the program will sort and display the top 100 words from the 
*    text file.
* Author
*    Jason Reed
************************************************************************/

#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <fstream> 
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>

using namespace std;

/*****************************************************
 * WORD COUNT
 * This function will prompt the user for a file, and
 * outputs the top 100 words from that file.
 *****************************************************/
int main();

// Gets the name of the file
string getFilename();

// Reads the words into a map and cleans up punctuation
// and upper case letters
void readFile(map <string, int> & wordCount, string & filename,
              string & word, int & processed);

// Used for the sor function to sort by integer and then
// by string
bool sortAlpha(pair<int, string> i, pair<int, string> j);

// Display the top 100 words
void display(vector<pair<int, string> > mapSort, int processed,
             vector<pair<int, string> >::reverse_iterator it2);

#endif // WORDCOUNT_H