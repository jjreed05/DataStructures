/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Jason Reed
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/
 
#include "spellCheck.h"

/*****************************************
 * GET FILENAME
 * This function will prompts the user for
 * a file
 ****************************************/
string getFilename()
{
   string filename;
   cout << "What file do you want to check? ";
   cin >> filename;
   
   return filename;
}

/*****************************************
 * READ FILE
 * This function will read a file into a 
 * vector.
 ****************************************/
void readFile(const string & filename, vector<string> & words)
{
   ifstream fin(filename.c_str());
   
   // check for errors. In the spellCheck function, we
   // will break the program if the file size is equal
   // to 0.
   if(fin.fail())
   {
      cout << "ERROR: reading the file" << endl;
      return;
   }
   
   // read strings into the variable
   string items;
   
   // read the items into the vector
   while(fin >> items)
   {
      words.push_back(items);
   }
   
   fin.close();   
}

/*****************************************
 * SPELL CHECK
 * This function will call getFilename and
 * readFile. It checks to see if a word is 
 * misspelled by seeing if the word can be
 * found in the dictionary through a hash 
 * table. If the word is found, then it
 * is spelled correctly. Otherwise, it
 * is a mispelled word.
 ****************************************/
void spellCheck()
{  
   // we will use this vector to hold the words
   vector<string> words;
   
   // we will use this vector to temporarily hold the 
   // dictionary words and misspelled words
   vector<string> items;
   // iterator
   vector<string> :: iterator it;
   // name of the file
   string filename;
   
   // read the dictionary.txt file in
   readFile("/home/cs235/week12/dictionary.txt", items);
   
   // set the capacity of table to two times the amount of items
   int size = 2 * items.size();
   
   // hash table for our dictionary
   sHash table(size);
   
   // read the items into the table
   for(it = items.begin(); it != items.end(); it++)
   {
      table.insert(*it);
   }
   
   // clear the vector
   items.clear(); 
   
   // prompt the user for the filename
   filename = getFilename();
   
   // break the program if the filename is corrupted
   if (filename.length() == 0)
      return;
   
   // read the file into the words vector
   readFile(filename, words);
   
   // find a mispelled word using the hash table
   for(it = words.begin(); it != words.end(); it++)
   {
      string lowerCased = *it;
      
      // convert the word into a lower cased word
      for(int i = 0; i < lowerCased.length(); i++)
      {
         lowerCased[i] = tolower(lowerCased[i]);
      }
      
      // if not found, then add it to a vector
      if(!table.find(lowerCased))
      {
         items.push_back(*it);
      }
   }
   
   // display the misspelled words
   if (items.size() > 0)
   {
      cout << "Misspelled: " << items[0];
      
      for(int i = 1; i < items.size(); i++)
         cout << ", " << items[i];
      
      cout << endl;
   }
   // display this message otherwise
   else
      cout << "File contains no spelling errors\n";
   
   // clear the data 
   items.clear();
   words.clear();
   table.clear();
      
   return;
}
