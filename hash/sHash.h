/***********************************************************************
 * Module:
 *    Week 12, Hash
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Jason Reed
 * Summary:
 *    Used for the spell checker implementation. It will create a hash
 *    table for string items.
 ************************************************************************/

#ifndef SHASH_H
#define SHASH_H

#include <string>
#include <cassert>
#include "hash.h"

using namespace std;

/**********************************************************************
 * class sHash
 * This is a hash class for strings. I implemented the same structure as
 * the IHash function in the week12.cpp file.
 * 
 * function hash()
 * This function will take in a string parameter and return an integer.
 * It will sum up the ascii numbers of each char in the string. I got this
 * idea after reading page 714 in the text. It will then modulus it by the 
 * capacity. After I read in the file, I set the capacity of the hash table 
 * to 2 times the number of items being processed because our text book said 
 * that we should use a number that is between 1.5 and 2 times the number of 
 * items due to emperical studies. FYI: the compiler would only allow me to 
 * declare this function inline.
 ***********************************************************************/
 class sHash : public Hash<string>
 {
 public:
    // Non-Default constructor
    sHash(int numBuckets) throw (const char *) : 
       Hash <string> (numBuckets) {}
       
    // Determine the array placement  
    int hash(const string & value) const
    {
       int ascii = 0;
       // sum up the ASCII values  
       for (int i = 0; i < value.length(); i++)
          ascii += value.c_str()[i];
       // return the integer
       return ascii % capacity();
    }
 };


 #endif