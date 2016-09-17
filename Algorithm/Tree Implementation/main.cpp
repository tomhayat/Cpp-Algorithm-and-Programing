#include <iostream>
#include <cerrno>
#include <vector>


using namespace std;
#include "IntTree.h"


int main() {
    
    // Affichage de l'arbre.
    IntTree* root = new IntTree(12);
    try {
        root->addAsLastSon(new IntTree(8));
        root->addAsLastSon(new IntTree(23));
        root->getSon(0)->addAsLastSon(new IntTree(4));
        root->getSon(0)->addAsLastSon(new IntTree(9));
        root->getSon(1)->addAsLastSon(new IntTree(17));
        root->getSon(1)->getSon(0)->addAsLastSon(new IntTree(15));
    } catch (const char* e) {
        cerr << e << endl;
    }
    root->display("* ");
    delete root;
    
    
    
    // Les différentes erreurs.
    IntTree* root1 = new IntTree(12);
    try {
        root1->removeLastSon();
    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
    delete root1;
    
    IntTree* root2 = new IntTree(12);
    try {
        root2->addAsLastSon(new IntTree(8));
        root2->addAsLastSon(new IntTree(23));
        root->getSon(4);
    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
    delete root2;

    IntTree* root3 = new IntTree(12);
    IntTree* root4= new IntTree(3);

    try {
        root3->addAsLastSon(new IntTree(8));
        root3->addAsLastSon(new IntTree(23));
        root3->setSon(4,root4);
    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
    delete root3;

    return 0;

}

