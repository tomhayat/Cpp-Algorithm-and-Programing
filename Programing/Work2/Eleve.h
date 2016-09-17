
# pragma once
#ifndef Eleve_hpp
#define Eleve_hpp

#include <iostream>
#include <stdio.h>
using namespace std;


class Eleve{
    string nom;
    int note;
public:
    string getNom(){
        return(nom);
    };
    int getNote(){
        return(note);
    };
    Eleve(string name, int grade);
    static Eleve Random();
};
ostream& operator<<(ostream& out, Eleve E) ;



class CompareNom{
    int* compteur;
public:
    CompareNom(int *c);
    bool operator()(Eleve E1, Eleve E2); //True signifie e1<e2.
    int getCompteur(){
        return (*compteur);
    }
};



class CompareNote{
    int* compteur;
public:
    CompareNote(int *c);
    bool operator()(Eleve E1, Eleve E2); //True signifie e1<e2.
    int getCompteur(){
        return (*compteur);
    }
};



#endif /* Eleve_hpp */
