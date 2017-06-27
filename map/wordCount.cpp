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

#include "wordCount.h"

/*****************************************************
 * WORD COUNT
 * This is the driver function of the program. It creates
 * a map. It uses a readfile function to initialize the map.
 * The function then reads the map into a vector of pairs for
 * sorting purposes. Then, function sorts the vector and
 * displays the content.
 *****************************************************/
int main()
{
   // name of the file
   string filename = getFilename();
   // word to read in
   string word;
   // number of words processed
   int processed;
   // the map to hold the words and frequencies
   map<string, int> wordCount;
   // map iterator
   map<string, int>::const_iterator it;
   
   // these variables are used to sort the data
   pair<int, string> pairs;
   vector<pair<int, string> > mapSort;
   vector<pair<int, string> >::reverse_iterator it2;
   
   // pass in the map, filename, and processed variable
   // and read the file
   readFile(wordCount, filename, word, processed);
   
   // used to set the pairs and push the pair into vector
   for(it = wordCount.begin(); it != wordCount.end(); it++)
   {
       // set first item to the map value
       pairs.first = it->second;
       // set secont item to the map key
       pairs.second = it->first;
       // push onto vector
       mapSort.push_back(pairs);
      
      //cerr << it->first << " " << it->second << endl;
   }
   
   // sort the vector by integer and then by string
   sort(mapSort.begin(), mapSort.end(), sortAlpha);  
   
   // display the top 100 words 
   display(mapSort, processed, it2);
   
   // free up memory
   wordCount.clear();
   mapSort.clear();
   
   return 0;
}

/*****************************************************
 * GET FILENAME
 * This function takes no parameters. It prompts the 
 * user for a filename. The function then returns the 
 * user's input.
 *****************************************************/
string getFilename()
{
   string filename;
   
   // prompt the user
   cout << "Enter filename: ";
   cin >> filename;
   
   // return the input
   return filename;
}

/*****************************************************
 * READ FILE
 * This function takes in a map, string, and integer 
 * parameter. The function opens a file stream and then
 * reads each word into a string. The string is then
 * edited by converting the uppercase characters into
 * lower case characters and taking out all of the 
 * punctuation except for "-". The function returns 
 * nothing.
 *****************************************************/
void readFile(map <string, int> & wordCount, string & filename, 
              string & word, int & processed)
{  
   // initialize the stream
   ifstream fin(filename.c_str());
   
   // read each word into string word
   while (fin >> word)
   {  
      // edit the word
      for (int i = 0; i < word.length(); i++)
      {
         // convert to lower case
         if (isupper(word[i]))
            word[i] = tolower(word[i]);
            
         // remove punctuation
         else if (word[i] != '-' && ispunct(word[i]))
         {
            word.erase(i, 1);
            i--;
         }
      }
      
      // find the word on the map and increment value if found
      if (wordCount.find(word) != wordCount.end())
         wordCount[word]++;
      
      // insert a new item onto the string
      else
         wordCount.insert(map<string, int>::value_type(word, 1));
      
      // keep track of number of words being processed
      processed += 1;
   }
}

/*****************************************************
 * SORT ALPHA
 * This function takes in two pair paramters. It will
 * ensure that the integers will get sorted in descending
 * order. If there are integers equal to each other, then
 * this function will sort the strings in ascending order.
 * This function either returns true or false.
 *****************************************************/
bool sortAlpha(pair<int, string> i, pair<int, string> j)
{
   // compare the integers
   if (i.first < j.first)
      return true;
      
   // compare the alphas 
   else if (i.first == j.first)
      return (i.second > j.second);
      
   // return false
   else
      return false;
}

/*****************************************************
 * Display
 * This function takes in three parameters: a vector, 
 * integer, and vector iterator. This function will display
 * our top 100 words. It iterates the sorted vector from
 * the end to the beginning and prints out the items off of
 * the pair.
 *****************************************************/
void display(vector<pair<int, string> > mapSort, int processed,
             vector<pair<int, string> >::reverse_iterator it2)
{
   cout << endl;
   cout << "Number of words processed: " << processed << endl;
   cout << "100 most common words found and their frequencies:\n";
   
   // used to only go through top 100
   int i = 0;
   // reverse iterate
   for (it2 = mapSort.rbegin(); it2 != mapSort.rend(); it2++)
   {
      // stop at the 100th word
      if (i == 100)
         break;
      // print out 
      cout << setw(23) << it2->second << " - " << it2->first << endl;
      // increment
      i++;
   }
}
