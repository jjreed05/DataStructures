###############################################################
# Program:
#     Week 02, STACK
#     Brother Ercanbrack, CS235
# Author:
#     Jason Reed
# Summary:
#     This program implements my creation of the Stack ADT.
#     The stack works as a buffet plate holder. This means 
#     that the program can only access the data at the top 
#     of the stack. We then have a file that tests the 
#     the correct usage of the stack. Also, I created an
#     algorithm that uses the stack to convert infix 
#     expressions to postfix expressions
#     
# Time:
#     18 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h week02.o infix.o 
	g++ -o a.out week02.o infix.o 
	tar -cf week02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week02.o: stack.h infix.h week02.cpp
	g++ -c week02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

