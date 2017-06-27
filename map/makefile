###############################################################
# Program:
#     Week 10, Map
#     Brother Ercanbrack, CS235
# Author:
#     Jason Reed
# Summary:
#     This programs implements the usage of a map STL. This program reads
#     in a text file. It cleans up all punctuation except for the hyphen.
#     The program then reads the words into a map and increments it's frequency.
#     Then, the program will sort and display the top 100 words from the 
#     text file.
# Time:
#     4 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: wordCount.o
	g++ -o a.out wordCount.o
	tar -cf week10.tar *.h *.cpp makefile

make clean:
	rm *.o *.out *.tar

wordCount.o:  wordCount.h wordCount.cpp
	g++ -c wordCount.cpp