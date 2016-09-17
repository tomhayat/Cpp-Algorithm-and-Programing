#include <iostream>
#include <vector>
#include <algorithm>
#include "Fonction.h"
using namespace std;



int main()
{
    vector<float> v;
    //P(x) = 3*x^2 + 5*x + 6
    v.push_back(3);
    v.push_back(5);
    v.push_back(6);
    Polynome P(v);
    float x = P.operator()(1);

    // Polynome dérivé.
    Fonction* d = P.derivee();
    float y = d->operator()(1);
    cout << x << endl << y << endl;
    
    
    // Fonction trigonométrique.
    Trigo T("cos");
    cout << T(3.14) << endl;
    Fonction* T2 = T.derivee();
    cout << T2 -> operator()(3.14);
    
    
    // Fonction affine.
    Affine A(3,4);
    float x1 = A.operator()(2);
    Fonction* D = A.derivee();
    float y1 = D -> operator()(2);
    cout << endl << x1 << endl << y1;
    
    
    //******* Fonction Cube *******
    
    vector<float> v1;
    v1.push_back(1);
    v1.push_back(0);
    v1.push_back(0);
    v1.push_back(0);
    Polynome P1(v1);
    
    cout << endl << P1(2);
    float im = 27;
    float ant = P1.inverse(im);
    cout << endl << ant;
    
    
    Trigo T1("tan");
    float im1 = 1;
    float ant1 = T1.inverse(im1);
    cout << endl << ant1;
    

    return 0;
    
}





