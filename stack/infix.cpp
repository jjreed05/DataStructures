/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Jason Reed
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <cctype>
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   // the item that we will return
   string postfix;
   // initialize a stack of char
   Stack <char> stack;
   // characters for infix
   char token;
   char topToken;
   // used to make a space if needed
   const string BLANK = " ";
   
   // loops through the infix string
   for (int i = 0; i < infix.length(); i++)
   {
      // assigns the char to a value within the string
      token = infix[i];
      
      // pushes unto stack or adds to the postfix string
      switch (token)
      {
         // do nothing and skip blanks
         case ' ': break;
         case '(': stack.push(token);
                   break;
         // allows us to go through the parentheses and
         // adds unto the postfix string 
         case ')': for (;;)
                   {
                      assert (!stack.empty());
                      topToken = stack.top();
                      stack.pop();
                      if (topToken == '(') 
                         break;
                      postfix.append(BLANK + topToken);
                   }
                   break;
         case '+':
         case '-':
         case '*':
         case '/':
         case '%': 
         // creates the precedence that we need for the functon
         // and pushes the tokens unto the stack
         case '^': for (;;)
                   {
                      if (stack.empty()||
                          stack.top() == '(' ||
                          token == '^' ||
                          (token == '*' || token == '/' || token == '%') &&
                          (stack.top() == '+' || stack.top() == '-'))
                      {
                         stack.push(token);
                         break;
                      }
                      else
                      {
                         topToken = stack.top();
                         stack.pop();
                         postfix.append(BLANK + topToken);
                      }
                      
                   }
                   break;
         // what to do with the operands such as spacing 
         // and the usage of decimals          
         default : postfix.append(BLANK + token);
                   for (;;)
                   {
                      if (!(isalnum(infix[i + 1]) || infix[i + 1] == '.' )) break;
                      i++;
                      token = infix[i];
                      postfix.append(1, token);
                   }
                   
         
      }
   }
   // take what we have on the stack and put
   // put it in our string
   for (;;)
   {
      if (stack.empty()) break;
      topToken = stack.top();
      stack.pop();
      if (topToken != '(')
      {
         postfix.append(BLANK + topToken);
      }
      else
      {
         break;
      }
   }

   // return the string 
   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
