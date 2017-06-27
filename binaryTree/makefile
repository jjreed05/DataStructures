###############################################################
# Program:
#     Week 08, Binary Tree
#     Brother Ercanbrack, CS235
# Author:
#     Jason Reed
# Summary:
#     This is my binary node class. It is similar to linked
#     list. Instead of using a linear storage algorithm, we 
#     will use a binary tree that links a parent node to two
#     child nodes. This also contains my implementation of the
#     binary tree to create a huffman code program.
# Time:
#     20 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week08.o huffman.o 
	g++ -o a.out week08.o huffman.o -g
	tar -cf week08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week08.o     : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
week08.o: bnode.h huffman.h week08.cpp
	g++ -c week08.cpp -g

huffman.o: bnode.h huffman.h huffman.cpp pair.h
	g++ -c huffman.cpp -g

