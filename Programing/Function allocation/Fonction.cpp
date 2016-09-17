
#include <string>
#include <vector>
#include "Fonction.h"
const float eps = 1e-5;

// Méthodes pour la classe parente Fonction.
float Fonction::operator()(float x) const{
    assert(integrale!=0);
    return ((*integrale)(x+eps) - (*integrale)(x))/eps;
}

float Fonction::inverse(float y){
    float x1, x2;
    x1 = 1;
    Fonction* D = derivee();
    for (int i = 0; i<100; i++){
        x2 = x1 + (y - operator()(x1))/(D->operator()(x1));
        x1 = x2;
    }
    return x2;
}

// Méthodes pour la classe enfant Polynome.
float Polynome::operator()(float x) const{
    float sum = 0;
    for (int i=0; i < coeff.size(); i++){
        sum = coeff[i]*pow(x, coeff.size()-(i+1)) + sum;
    }
    return sum;
}

Fonction* Polynome::derivee() const{
    if (coeff.size() == 1){
        return 0;
    }
    else{
        vector<float> coeffDerive;
        for (int i=0; i < coeff.size()-1; i++){
            coeffDerive.push_back(coeff[i]*(coeff.size()-(i+1)));
        }
        Fonction* Pol = new Polynome(coeffDerive);
        return Pol;
    }
}







// Méthodes pour la classe enfant Trigo.
Trigo::Trigo(string type){
    nom = type;
}

Fonction* Trigo::derivee() const{
    Fonction* D = new Trigo("");
    D -> integrale = clone();
    return D;
}


