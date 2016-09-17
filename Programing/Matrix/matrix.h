
#pragma once
#ifndef Matrix_hpp
#define Matrix_hpp
#include <cassert>
#include <stdio.h>
using namespace std;

class Matrice
{ // C'est la structure de données : à mettre en privée.
    float* tab;
    int nlig;
    int ncol;
    int* count; // Les matrices doivent avoir le même compteur.
    
public:
    Matrice(int m, int n);
    ~Matrice(); // Destructeur.
    Matrice(const Matrice& A); // Constructeur par copie. Bien mettre le const et la référence.
    
    int nlignes(){
        return (nlig);
    };
    int ncolones(){
        return(ncol);
    }; // on peut mettre un const à la fin.
    void RandomMatrice(); // Les éléments sont aléatoires.

    float operator()(int i, int j) const; // Retourne une valeur.
    float& operator()(int i, int j); // Retourne et change la valeur.
    Matrice operator+(Matrice B) const;
    Matrice operator*(Matrice B) const; // Il va y avoir une construction par copie. ON met const car ne modifie ni A ni B.
};
ostream& operator<<(ostream& out, Matrice A) ;

#endif /* Matrix_hpp */
