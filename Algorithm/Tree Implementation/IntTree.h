
# pragma once
#include <iostream>
#include <vector>
using namespace std;


#ifndef IntTree_h
#define IntTree_h

class IntTree {
    // Node information
    int data;
    // Sequence of sons (empty if none)
    vector<IntTree*> sons;
public:
    // Create a node with given information
    IntTree(int d);
    // Return information of this node
    int getData();
    // Set information of this node
    void setData(int d);
    // Return the number of sons of this node
    int nbSons();
    // Return the son at position pos, if any (considering left-most son is at position 0)
    IntTree* getSon(int pos);
    // Replace the exisiting son at position pos with newSon (left-most son at position 0)
    void setSon(int pos, IntTree* newSon);
    // Add newSon as supplementary right-most son of this node
    void addAsLastSon(IntTree* newSon);
    // Remove right-most son of this node
    void removeLastSon();
    // Displays the tree.
    void display(string prefix = "", string indent = "  ");
    // Destructeur
    ~IntTree();
    
};

#endif /* IntTree_h */
