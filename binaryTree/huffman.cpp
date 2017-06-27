/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Jason Reed
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype


using namespace std;

/*******************************************
 * Function: HUFFMAN
 * Summary: This is our driver function for
 * the huffman code. It will read a file in.
 * It innserts the data into a vector of pointers.
 * This function then sorts the data into a 
 * Binary Node called tree.
 *******************************************/
void huffman(string fileName)
{
    //intialize the stream
    ifstream fin(fileName.c_str());
    
    PAIR pair;     // object to hold frequencies and characters
    TREE * tree;   // binary nodes of pairs
    VEC_TREE data; // vector of tree pointers 
    
    // read the file into a vector
    while(fin >> pair)
    {
       tree = new TREE(pair);
       data.push_back(tree);
    }
    // close the stream
    fin.close();
    
    // sort the data
    sort(data.begin(), data.end(), sortGreater);
    
    // sort the pairs withing the binary node called tree
    while (data.size() > 1)
    {
       int size = data.size();
       
       // our binary node that will hold the result of 2 nodes
       // using the addition operator
       TREE * combined;
       
       //cerr << data[size - 1]->data.first << endl;
       //cerr << data[size - 2]->data.first << endl;
       
       // combine two pairs off the end of the vector
       combined = new TREE(*(new PAIR(data[size - 1]->data.first +
          data[size - 2]->data.first, data[size - 1]->data.second +
          data[size - 2]->data.second)));
       
       // push the greater to data to the right
       combined->addLeft(data[size - 1]);
       // push lesser data to the left
       combined->addRight(data[size - 2]);
       
       // pop the combined tree off the vector
       data.pop_back();
       data.pop_back();
       
       // push the combined data in its place
       data.push_back(combined);
       
       // sort it again
       sort(data.begin(), data.end(), sortGreater);
    }
    
    VEC_PAIR huff;
    
    //cerr << data[0]->data.first << endl;
    
    // encode the huffman codes
    encodeHuffman(data[0], "", huff);
    
    // sort starting with the first pair of strings
    sort(huff.begin(), huff.end(), sortLesser);
    
    for(int i = 0; i < huff.size(); i++)
    {
       cout << huff[i].first << " = " << huff[i].second << endl;
    }
    
   return;
}

/*******************************************
 * Function: sortGreater
 * Summary: Will take in tree pointers and
 * compare them.
 * Parameters: TREE * lhs, TREE * rhs
 * Return: True or False
 *******************************************/
 bool sortGreater(TREE * lhs, TREE * rhs)
 {
    if (lhs->data.second == rhs->data.second)
       return (lhs->data >= rhs->data);
    else
       return (lhs->data.second > rhs->data.second);
 }
 
 /*******************************************
 * Function: sortLesser
 * Summary: Will take in vector of string pairs and
 * compare them.
 * Parameters: PAIR_STRING lhs, PAIR_STRING rhs
 * Return: True or False
 *******************************************/
 bool sortLesser(PAIR_STRING lhs, PAIR_STRING rhs)
 {
    return (lhs < rhs);
 }
 
  /*******************************************
 * Function: encodeHuffman
 * Summary: It will encode our huffman codes
 * by adding either a 0(left) or 1(right) 
 * when it goes through the tree.
 * Parameters: TREE * root, string huffman,
 *    and VEC_PAIR huff.
 *******************************************/
 void encodeHuffman(TREE * root, string huffman, VEC_PAIR & huff)
 {
    
    // push back unto a vector if its a leaf
    if ((root->pLeft == NULL) && (root->pRight == NULL))
    {
       //cerr << "We are in the if" << endl;
       //cerr << root->data.first << endl;
       huff.push_back(PAIR_STRING(root->data.first, huffman));
       return;
    }
    
    // Recurse through the tree if its not a leaf
    else
    {
       // add a 0 to the left
       if (root->pLeft != NULL)
       {
          //cerr << "We are Left" << endl;
          encodeHuffman(root->pLeft, huffman + "0", huff);
       }
       
       // add a 1 to the right
       //cerr << "We are Right" << endl;
       if (root->pRight != NULL)
          encodeHuffman(root->pRight, huffman + "1", huff);
       return;
    }
 }
 
 
