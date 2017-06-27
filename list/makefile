###############################################################
# Program:
#     Week 07, LIST
#     Brother Ercanbrack, CS235
# Author:
#     Jason Reed
# Summary:
#     This is my container that functions like the standard 
#     template library's list. This program also holds my
#     implementation of the fibonacci program.
# Time:
#     30 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o wholeNumber.o
	g++ -o a.out week07.o fibonacci.o wholeNumber.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      wholeNumber.o  : the object to hold big integers
##############################################################
week07.o: list.h week07.cpp
	g++ -c week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp

wholeNumber.o: list.h wholeNumber.h wholeNumber.cpp 
	g++ -c wholeNumber.cpp -g



