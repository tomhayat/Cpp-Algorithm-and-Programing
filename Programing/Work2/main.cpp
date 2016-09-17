#include <iostream>
#include <vector>
#include <algorithm>
#include "Eleve.h"
using namespace std;


int main()
{
    int c1;
    int c2;
    CompareNom cmp1(&c1);
    CompareNote cmp2(&c2);

    vector<Eleve> E;
    E.push_back(Eleve("jean", 12));
    E.push_back(Eleve("marc", 14));
    E.push_back(Eleve("alex", 18));
    Eleve E1("",0); // On remplit le vecteur avec des Eleves.
    for (int i =0; i<10; i++){
        E.push_back(E1.Random());
    }

    // Utilisation d' "iterator" qui fonctionne comme un pointeur.
    for (vector<Eleve>::iterator  it = E.begin(); it != E.end(); ++ it){
        cout << *it;
    }
    cout << endl;
    
    
    
    
    cout << "Comparaison par Nom : " << endl;
    sort(E.begin(), E.end(), cmp1);
    for (vector<Eleve>::iterator  it = E.begin(); it != E.end(); ++ it){
        cout << *it;
    }
    cout << endl;
    
    
    cout << "Comparaison par note : " << endl;
    sort(E.begin(), E.end(), cmp2);
    for (vector<Eleve>::iterator  it = E.begin(); it != E.end(); ++ it){
        cout << *it;
    }
    cout << cmp1.getCompteur() << endl;
    
    cout << endl;


    return 0;
    
}





