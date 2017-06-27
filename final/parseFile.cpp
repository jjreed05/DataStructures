/***********************************************************************
 * Module:
 *    parseFile.cpp
 * Author:
 *    Jason Reed
 * Summary:
 *    This is my resource file for parseFile.
 ************************************************************************/
 
 #include "parseFile.h"
 
/*******************************************
 * Parse()
 * This function takes in a file stream as 
 * its parameter. It will read in a file
 * line by line and parse the items needed.
 * It gather's each person's information in
 * the file and puts it in a node. The node
 * is then pushed onto the list. The function
 * then links the node pointers together
 * to link family geneaology. This function 
 * will return a list of node pointers.
 ******************************************/
 List parse(ifstream & inputFile)
 {
     // List to items onto
     List tree; 
     // read each line into
     string line; 
     
     // scan the file
     while (getline(inputFile, line)) 
     {
         // break here
         if (line.find("0 @F") == 0) 
            break;
         // new record
         if (line.find("0 @I") == 0)
         {
            // allocate a new node
            Node * record = new(nothrow) Node();

            int iD = 0; 
            unsigned long start = 0; 
            start = line.find("@ INDI");
            
            // Cut the line to what we need
            string stringID = line.substr(4, (start - 4));
            istringstream(stringID) >> iD;
         
            // set the ID
            record->setId(iD);
            
            // variables needed for the record
            string last;     
            string first;  
            string birth;     
            string previous;  
            
            // advance the line
            getline(inputFile, line);
         
            while (line.find("0 @I") != 0)
            {
               // get the first name(s)
               if (line.find("2 GIVN") == 0)
               {
                  first = line.substr(7);
                  record->setFirst(first);
               }
               // get the last name
               else if (line.find("2 SURN") == 0)
               {
                  last = line.substr(7);
                  record->setLast(last);
               }
               // mulitiple date lines
               // use two strings to determine the birthday
               else if (line.find("2 DATE") == 0 && 
                     previous.find("1 BIRT") == 0)
               {
                  birth = line.substr(7);
                  record->setBirth(birth);
               }
               // break here
               else if (line.find("3 TIME") == 0)
                 break;
                 
               // advance the line
               previous = line;
               getline(inputFile, line);
            
         }
         // push into tree
         tree.push_alpha(record);
      }
   }

   // link the family members together
   while (line.find("0 @S1@ SOUR") != 0) 
   {
      if (line.find("0 @F") == 0) 
      {
         // ID numbers
         int husbandId = 0;  
         int wifeId = 0; 
         int childId = 0;  
         
         // advance
         getline(inputFile, line);
         
         // parse away
         while (line.find("0 @F") != 0)
         {
            // break here
            if (line.find("0 @S1@ SOUR") == 0)
               break;
            // get the husband's ID
            if (line.find("1 HUSB") == 0)
            {
               string husband;  
               husband = line.substr(9);
               husband = husband.substr(0, husband.length() - 1);
               istringstream(husband) >> husbandId;
            }
            // get the wife's ID
            else if (line.find("1 WIFE") == 0)
            {
               string wife;      
               wife = line.substr(9);
               wife = wife.substr(0, wife.length() - 1);
               istringstream(wife) >> wifeId;
            }
            // get the child's Id
            else if (line.find("1 CHIL") == 0)
            {
               string child;   
               child = line.substr(9);
               child = child.substr(0, child.length() - 1);
               istringstream(child) >> childId;
            }
            // advance the line
            getline(inputFile, line);
         }
         // pointer to the husband's info
         Node * husbandNode = NULL; 
         // pointer to the wife's info 
         Node * wifeNode = NULL;  
         // pointer to the child's info
         Node * childNode = NULL;  

         // initialize the nodes
         husbandNode = tree.getNode(tree.search(husbandId));
         wifeNode = tree.getNode(tree.search(wifeId));
         childNode = tree.getNode(tree.search(childId));

         // set the pointers
         if (childNode != NULL)
         {
            childNode->setFather(husbandNode);
            childNode->setMother(wifeNode);
         }  
      }
   }
   // return the list
   return tree;
 }