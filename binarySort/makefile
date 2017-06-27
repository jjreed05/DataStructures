###############################################################
# Program:
#     Week 09, Binary Search Tree
#     Brother Ercanbrack, CS235
# Author:
#     Jason Reed
# Summary:
#     This file includes the Binary Search Tree, Binary Node,
#     Stack, and the Binary Sort. These files are tested by 
#     week09.cpp. The Binary Search Tree is similar to the 
#     STL's version.
# Time:
#     14 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week09.o
	g++ -o a.out week09.o 
	tar -cf week09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
	g++ -c week09.cpp

