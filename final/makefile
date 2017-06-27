###############################################################
# Program:
#     Week 13, Final Project
#     Brother Ercanbrack, CS235
# Author:
#     Jason Reed
# Summary:
#     This is my program for genealogy. I used a list class to 
#     sort the names alphabetically using an insertion sort.
#     I also used node pointers to link the parents and child together.
#     In summary, I used a list of node pointers to organize the
#     data.
# Time: 
#     27 Hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: main.o parseFile.o list.o node.o
	g++ -o a.out main.o parseFile.o list.o node.o -g
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      main.o       : the driver program
#      paseFile.o   : program to read in the data
#      list.o       : list class
#      node.o       : node class
##############################################################
main.o: main.cpp
	g++ -c main.cpp -g

parseFile.o: parseFile.h parseFile.cpp
	g++ -c parseFile.cpp -g
 
list.o: list.h list.cpp
	g++ -c list.cpp -g
  
node.o: node.h node.cpp
	g++ -c node.cpp -g 




