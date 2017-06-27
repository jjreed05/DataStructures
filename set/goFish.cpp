/***********************************************************************
* Source File:
*    Implementation of goFish.
* Summary: 
*    This file will implement all the methods described in goFish.h
* Author:
*    Jason Reed
************************************************************************/

#include "goFish.h"
#include "set.h"
#include "card.h"
#include <fstream>
#include <iostream>

using namespace std;
 
/**************************************************
 * GO FISH
 * The game of "Go Fish"
 *************************************************/
 void goFish()
 {
    // variables needed for the game
    int round = 1;
    int match = 0;
    Card userPick;
    Set <Card> hand;
    
    // read the file and insert into hand
    ifstream fin("/home/cs235e/week05/hand.txt");
    do
    {
      fin >> pair;
    }
    while (!fin.eof());    
    fin.close();
    
    cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
    
    // prompt the user until then end of the 5th round
    while (round != 6)
    {
       cout << "round " << round << ": ";
       // get the user's fish
       cin >> userPick;
       // use the find fundtion to see if it is in the set
       if (hand.find(userPick) != -1)
       {
          cout << "\tYou got a match!\n";
          // erase the item off the set
          hand.erase(hand.find(userPick));
          // we have a match
          match++;
       }
       else
          cout << "\tGo Fish!\n";
       // increment the round
       round++;
    }
    
    cout << "You have 2 matches!\n";
    cout << "The remaining cards: ";
    
    // use an iterator to go through the remaining items
    SetIterator <Card> it;
    for (it = hand.begin(); it != hand.end(); it++)
    {
       if (it != hand.begin())
          cout << ", " << *it;
       else
          cout << *it;
    }
    
    cout << endl;
 }
