/***********************************************************************
 * File:
 *    node.h
 * Author:
 *    Jason Reed
 * Summary:
 *    This file holds our Node class. It pretty much holds all of the 
 *    need information about the person. It has a pointer to the person's
 *    relatives.
 ************************************************************************/
 
 #ifndef NODE_H
 #define NODE_H
 
 #include <iostream>
 #include <string>
 
 using namespace std;
 
 /*******************************************
 * Class: NODE
 * This is what will hold the information
 * for a single node in a linked list. The node
 * pointers play a vital role in linking relatives
 * together.
 ******************************************/
 class Node
 {
 public:
    // Node Constructors
    Node();
    Node(string birth, string first, string last, int id);
    
    // Getters for the Node
    string getBirth() const {return birth;}
    string getFirst() const {return first;}
    string getLast() const {return last;}
    int getId() const {return id;}
    Node * getFather() const {return father;}
    Node * getMother() const {return mother;}
    Node * getNext() const {return next;}
    
    // Setters for the Node
    void setBirth(string birth) {this->birth = birth;}
    void setFirst(string first) {this->first = first;}
    void setLast(string last) {this->last = last;}
    void setId(int id) {this->id = id;}
    void setFather(Node * father) {this->father = father;}
    void setMother(Node * mother) {this->mother = mother;}
    void setNext(Node * next) {this->next = next;}
    
    // Display the info
    void display();
    
 private:
    // Person's information
    string birth;
    string first;
    string last;
    int id;
    // Pointers
    Node * father;
    Node * mother;
    Node * next;
 };
 
 #endif