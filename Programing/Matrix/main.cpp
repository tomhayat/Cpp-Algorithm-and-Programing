#include <iostream>
#include "matrix.h"
#include <vector>

using namespace std;




int main()
{
    
    Matrice A(2,2);
    A(0,0)=5;
    A(0,1)=4;
    A(1,1)=1;
    A(1,0)=8;
    Matrice B(A); // Construction par copie.
    Matrice C = A*B;
    
    int nlig = rand()%100;
    
    vector<Matrice> Mat_Vect; // Construction normal.
    vector<Matrice> Mat_Vect2; // Construction par copie.
    vector<Matrice> Mat_Vect3; // Construction par copie d'une multiplication.

    
    for (int i = 0; i < 10; i++){
        Matrice A = Matrice(nlig, nlig);
        A.RandomMatrice();
        Mat_Vect.push_back(A);
    }
    for (int i = 0; i < 10; i++){
        Mat_Vect2.push_back(Mat_Vect[i]);
    }
    for (int i = 0; i < 10; i++){
        Mat_Vect3.push_back(Mat_Vect[i]*Mat_Vect2[9-i]);
    }
    
    return 0;
    
}

