
#include <string>
#include "Eleve.h"

Eleve::Eleve(string name, int grade){
    nom = name;
    note = grade;
}

ostream& operator<<(ostream& out, Eleve E) {
    out << "Nom: " << E.getNom() << "; ";
    out << "Note: " << E.getNote() << endl;
    return out;
}


// Génère un élève aléatoirement.
Eleve Eleve::Random(){
    Eleve e1("",0);
    int length = rand()%15;
    for (int i=0; i< length; i++){
        e1.nom.append(1, 'a'+rand()%26);
        
    }
    e1.note = rand()%20;
    return e1;
}


// Constructeur
CompareNom::CompareNom(int *c){
    compteur = c;
    *compteur = 0;
}

// Comparateur
bool CompareNom::operator()(Eleve E1, Eleve E2){
    ++*compteur;
    return (E1.getNom() < E2.getNom());
}

// Constructeur
CompareNote::CompareNote(int *c){
    compteur = c;
    *compteur = 0;
}

// Comparateur
bool CompareNote::operator()(Eleve E1, Eleve E2){
    ++*compteur;
    return (E1.getNote() < E2.getNote());
}
