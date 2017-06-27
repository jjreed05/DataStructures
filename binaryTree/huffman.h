/***********************************************************************
 * Module:
 *    Week 08, Huffman
 * Author:
 *    Jason Reed
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <algorithm>
#include "bnode.h"
#include "pair.h"
#include <vector>
#include <string>

using namespace std;

// create alias names for these data types
// to save time and better style
typedef Pair<string, float> PAIR;
typedef Pair<string, string> PAIR_STRING;
typedef BinaryNode<PAIR> TREE;
typedef vector<TREE*> VEC_TREE;
typedef vector<PAIR_STRING> VEC_PAIR;

// prototypes
void huffman(string fileName);
bool sortGreater(TREE* lhs, TREE * rhs);
bool sortLesser(PAIR_STRING lhs, PAIR_STRING rhs);
void encodeHuffman(TREE * root, string huffman, VEC_PAIR & huff);

#endif // HUFFMAN_h
