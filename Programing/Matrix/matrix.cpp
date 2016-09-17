
#include <iostream>
#include "Matrix.h"
using namespace std;

// Les matrices n'ont pas de secret entre elles.



Matrice::Matrice(int m, int n){
    nlig = m;
    ncol = n;
    tab = new float [nlig*ncol];
    count = new int;
    (*count) = 1; // count = new int (1);
    cout << "constructeur normal" << endl;
}


Matrice::~Matrice(){
    --(*count);
    if((*count)==0) {
        delete [] tab;
        delete count;
    }
    cout << "Destroy" << endl;
} // On ne doit pas appeler le destructeur soit-même.

//Shallow copy
Matrice::Matrice(const Matrice& A){
    nlig = A.nlig;
    ncol = A.ncol;
    tab = A.tab;
    count = A.count;
    (*count) ++; // 2 matrices partagent la même zone mémoire. Comme ++ *count.
    cout << "Constructeur par copie." << endl; // const Matrice car count reste le même alors que *count marche.
}

float Matrice::operator()(int i, int j) const{
    assert(0 <= i && i < nlig && 0 <=j && j < ncol);
    return (tab[i+j*nlig]);
}


float& Matrice::operator()(int i, int j){
    assert(0 <= i && i < nlig && 0 <=j && j < ncol);
    return (tab[i+j*nlig]);
}



void Matrice::RandomMatrice(){
    for (int i = 0; i < nlig; i++){
        for (int j = 0; j < ncol; j++){
            tab[i+j*nlig] = rand()%100;
        }
    }
}


Matrice Matrice::operator+(Matrice B) const{
    assert(B.nlig == nlig && B.ncol== ncol);
    Matrice C=Matrice(nlig, ncol);
    for(int i=0; i < nlig; i++){
        for(int j =0; j < ncol; j++){
            C.tab[i+j*nlig]= tab[i+j*nlig]+ B.tab[i+j*nlig];
        }
    }
    return(C);
}
Matrice Matrice::operator*(Matrice B) const{
    assert(nlig == B.ncol);
    Matrice C=Matrice(nlig, ncol);
    for(int i=0; i < nlig; i++){
        for(int j =0; j < B.ncol; j++){
            for(int k=0; k <nlig; k++){
                C.tab[i+j*nlig] = C.tab[i+j*nlig]+ (*this)(i,k)*B(k,j);
            }
        }
    }
    return(C);
}





ostream& operator<<(ostream& out, Matrice A) {
    for (int i = 0; i < A.nlignes(); i++){
        for (int j = 0; j < A.ncolones(); j++){
            out << A(i,j)<<" ";
        }
        out << endl;
    }
    return out;
}

