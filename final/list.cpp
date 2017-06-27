/***********************************************************************
 * Module:
 *    list.cpp
 * Author:
 *    Jason Reed
 * Summary:
 *    This holds the function definitions of my list class. We have two
 *    non-member functions needed for the program declared here.
 ************************************************************************/

#include "list.h"

/*******************************************
 * toLower()
 * This function will take a string as a parameter.
 * It will then convert any uppercase letters to 
 * lower case letter.
 ******************************************/
void toLower(string & stringToModify)
{
   string result = "";
   char currentChar;       
   
   for (int i = 0; i < stringToModify.length(); i++)
   {
      currentChar = stringToModify[i];
     
      if ((int)currentChar >= 65 && (int)currentChar < 97)
      {
         result += currentChar + 32; 
      }
      else 
      {
         result += currentChar;
      }
   }
   stringToModify = result;
}

/*******************************************
 * generationLevel()
 * This a non-member function that prints out
 * the generation level. It takes in an integer
 * and returns a string to be printed
 ******************************************/
string generationLevel(int generation)
{
   string level = "";
   
   // determine the generation level
   switch (generation)
   {
      case 1:
         break;
      case 2:
         level = "Parents:";
         break;
      case 3:
         level = "Grandparents:";
         break;
      case 4:
         level = "Great Grandparents:";
         break;
      
      // Nth level grandparens
      default:
      {
         generation -= 3;
         
         // convert the int to a string
         string integer;
         ostringstream data;
         data << generation;
         integer = data.str();
         
         // compare the last digit
         char digit = integer.at(integer.length() - 1);
         
         string last = "";
         
         // Number endings
         switch(digit)
         {
            case '1':
               if(generation != 11)
                  last = "st";
               else
                  last = "th";
               break;
            case '2':
               last = "nd";
               break;
            case '3':
               last = "rd";
               break;
            default:
               last = "th";
               break;
         }
         // create the string to return
         level = integer + last + " Great Grandparents:";
      }
      break;
   }
   // return the string
   return level;
}

/*******************************************
 * List :: Destructor
 * This will delete the items off the list.
 ******************************************/
 List :: ~List()
 {
    if (numItems > 0)
    {
       Node * track = node;
       Node * tmp = node;
       
       while (track != NULL)
       {
          track = track->getNext();
          delete tmp;
          tmp = track;
       }
    }
 }
 
/*******************************************
 * List :: Push_Back
 * This function will take in a node as a parameter.
 * It will then do a comparison by last, first,
 * and then by birthday before inserting into the 
 * list.
 ******************************************/
 void List :: push_alpha(Node * newNode)
 {
    Node * track = node;
    Node * tmp = NULL;

    int it = 0;
    
    while(track != NULL)
    {
       // newNode's string compare
       string compareLast1 = newNode->getLast();
       // track's string compare
       string compareLast2 = track->getLast(); 
       
       // convert the string to all lower case
       toLower(compareLast1);
       toLower(compareLast2);
       
       // compare last name
       if(compareLast1 < compareLast2)
          break;
          
       else if(compareLast1 == compareLast2 || compareLast1 == "")
       {
          string compareFirst1 = newNode->getFirst();
          string compareFirst2 = track->getFirst();
          
          // convert the string to all lower case
          toLower(compareFirst1);
          toLower(compareFirst2);
          
          // compare first name
          if(compareFirst1 < compareFirst2)
             break;
          
          else if(compareFirst1 == compareFirst2)
          {
             string compareBirth1 = newNode->getBirth();
             string compareBirth2 = track->getBirth();
             
             // compare birthday
             if(compareBirth1 < compareBirth2)
             {
                // here we will cut the year out of the string 
                // and do a comparison
                string compareYear = compareBirth1;
                compareYear = compareYear.substr(compareYear.length() - 4,  
                   compareYear.length());
                
                string compareYear2 = compareBirth2;
                compareYear2 = compareYear2.substr(compareYear2.length() - 4,
                   compareYear.length());
                // break
                if(compareYear < compareYear2)
                   break;
             }
             break;
          }
       }
       // incrment to keep track of position
       it++;
    
       // Increment
       tmp = track;
       track = track->getNext();
    }
    
    // set the node
    if (it == 0)
    {
       newNode->setNext(node);
       node = newNode;
    }
    else
    {
       int count = 0;
       
       // place the node into the list
       for (Node * current = node;;current = current->getNext())
       {
          if (count == it - 1)
          {
             newNode->setNext(current->getNext());
             current->setNext(newNode);
             break;
          }
          else if(current->getNext() == NULL)
          {
             current->setNext(newNode);
             break;
          }
          count++;
       }
    }
    // we have inserted, so increment numItems
    numItems++;   
 }
 
/*******************************************
 * List :: search()
 * This function will take in an integer.
 * It will try to find that integer within
 * the list by searching through each node's
 * ID's.
 ******************************************/
 int List :: search(int id) const
 {
    // if the list is empty
    if(numItems == 0)
       return -1;
    
    // iterate through the list
    int it = 0;
    
    for(Node * iterator = node; iterator != NULL;
       iterator = iterator->getNext(), it++)
    {
       if (iterator->getId() == id)
          return it;
    }
    
    return -1;
 }
 
/*******************************************
 * List :: getNode()
 * This function will take in an integer and
 * retrieve the node from a position
 ******************************************/
 Node * List::getNode(int it) const
 {
    if (numItems == 0 || it > numItems)
       return NULL;
    
    Node * iterator = node;
    int it2 = 0;
    
    for(; it2 != it && iterator != NULL; ++it2)
    {
       iterator = iterator->getNext();
    }
    
    return iterator;
 }
 
/*******************************************
 * List :: printList
 * This function will print the sorted list
 ******************************************/
 void List :: printList() const
 {
    // iterator to get the position of the original node
    Node * iterator = getNode(0);
    // open the file stream
    ofstream file;
    
    // open sorted.dat
    file.open("sorted.dat", ios::trunc);
    
    // output the list into the file
    while (iterator != NULL)
    {  
       // print the first name
       if(iterator->getFirst() != "")
          file << iterator->getFirst();
       // put a space if needed
       if(iterator->getFirst() != "" && iterator->getLast() != "")
          file << " ";
       // print the last name
       if(iterator->getLast() != "")
          file << iterator->getLast();
       // print the birthday
       if(iterator->getBirth() != "")
          file << ", b. " << iterator->getBirth();
       // endline each record
       file << endl;
       // go to the next item on the list
       iterator = iterator->getNext(); 
    }
 }
 
 /*******************************************
 * List :: printGen()
 * This function will print the nodes in generation
 * order by going through each node pointer. We 
 * will use queue like implementation inorder 
 * to get the right generation level. 
 ******************************************/
 void List :: printGen()
 {
     // Max number 
     const int MAX = 500; 
     // Create a queue of node pointers        
     Node * queue[MAX]; 
     // We will use this node to print things out              
     Node * tmp; 
     // Keep track of the front                  
     int front = 0;  
     // Keep track of the back         
     int back = 0;              
     // Keep track of the generation
     int generation = 0;  
     // Tab needed for the display         
     string tab = "        "; 
     // Start at the root node
     Node * descendant = this->getNode(this->search(1));
     // Used to keep track of the generation
     Node * parent = descendant;
  
     // Push the descendant to the back
     queue[back++] = descendant; 
  
     while (front != back)
     {
        tmp = queue[front];
        front = (front + 1) % MAX;
  
        if (tmp == parent)
        {
           generation++;
  
           // Print out a new generation if tmp equals parent
           if (generation == 1)
           {
              // First level to print out
              cout << "The Ancestors of ";
              cout << tmp->getFirst();
              cout << " ";
              cout << tmp->getLast();
              cout << ":\n";
           }
           // The rest of the levels
           else
              cout << generationLevel(generation) << endl;
        }
  
        if (tmp != NULL)
        {
           // Display the Node
           if (generation > 1)
           {
              cout << tab;
              tmp->display();
           }
           queue[back] = tmp->getFather();
           // Record father of fathers
           if (queue[back] != NULL)
           {
              if (parent->getFather() == queue[back])
                 parent = queue[back];
           }
           // Set the back
           back = (back + 1) % MAX;
           queue[back] = tmp->getMother();
           back = (back + 1) % MAX;
        }
     }
 }
