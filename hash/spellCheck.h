/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include "hash.h"
#include "sHash.h"

using namespace std;

string getFilename();
void readFile(const string & filename, vector<string> & words);
void spellCheck();

#endif // SPELL_CHECK_H
