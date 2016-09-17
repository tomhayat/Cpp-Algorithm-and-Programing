

#include "IntTree.h"

IntTree::IntTree(int d){
    data = d;
}
int IntTree::getData(){
    return data;
}

void IntTree::setData(int d){
    data = d;
}

int IntTree::nbSons(){
    return sons.size();
}


// Erreur si pos est en dehors de l'intervalle.
IntTree* IntTree::getSon(int pos){
    if (pos <0 || pos > nbSons()){
        throw out_of_range("ERROR : The position in getSon is out of range.");
    }
    return sons[pos];
}
// Erreur si pos est en dehors de l'intervalle.
void IntTree::setSon(int pos, IntTree* newSon){
    if (pos <0 || pos > nbSons()){
        throw out_of_range("ERROR : The position in setSon is out of range.");
    }
    sons[pos] = newSon;
}
void IntTree::addAsLastSon(IntTree* newSon){
    sons.push_back(newSon);
}

// Erreur si l'on tente de popback un vecteur vide.
void IntTree::removeLastSon(){
    if (nbSons() == 0){
        throw length_error("ERROR : There are no last sons.");
    }
    sons.pop_back();
}


// Méthode récursive d'affichage.
void IntTree::display(string prefix, string indent){
    cout << prefix;
    cout <<(data)<< endl;
    for (int i = 0; i < nbSons(); i++){
        getSon(i)->display(prefix + indent, indent);
    }
}


// On désalloue l'espace en profondeur puis on remonte.
IntTree::~IntTree(){
    for(int i=0; i < nbSons(); i++){
        delete sons[i];
    }
}


