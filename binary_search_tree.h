#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_h

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <time.h>


class Node{
  
  public:
    Node();
    Node(int key);
    ~Node();
    
    Node * parent;
    Node * right;
    Node * left;
    int key;
};

class Tree{
  
  public:
    Tree();  
    ~Tree();
    
    Node * root;
    
    // function
    // modification
    void insertKey(int value, Node * node);
    void insertMinimal(int values[], int start, int end); 
    
    void deleteKey(int value);
    void destroy(Node * node);
    
    // traversals
    void inOrder(Node * node);
    void preOrder(Node * node);
    void postOrder(Node * node);
    
    // lookup
    Node * searchKey(int value, Node * node);
    
    int  findMinimum(Node * node);
    int  findMaximum(Node * node);
    
    Node * findMin(Node * node);
    Node * findMax(Node * node);  
    int findMaxHeight(Node * node);
    int findMinHeight(Node * node);
    
    //special 
    bool checkBalance(Node * node);
    
  
};












#endif
