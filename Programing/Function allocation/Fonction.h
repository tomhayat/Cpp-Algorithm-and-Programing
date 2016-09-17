
# pragma once
#ifndef Eleve_hpp
#define Eleve_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <assert.h>


using namespace std;



class Fonction{
public:
    Fonction* integrale; // mis en public
    Fonction(){integrale=0;};
    virtual float operator()(float x) const;
    virtual Fonction* derivee() const=0;        // On a le droit de retourner un pointeur sur fonction mais pas une classe abstraite.
    virtual Fonction* clone() const=0; //virtual pure.
    float inverse(float y);
    virtual ~Fonction(){delete integrale;};

};



class Polynome:public Fonction{
    vector<float> coeff;
public:
    Polynome(vector<float> coeff2){
        coeff = coeff2;
    };
    Polynome(float a, float b){
        vector<float> v{a, b};
        coeff = v;
    };
    vector<float> getCoeff(){return coeff;};
    void setCoeff(vector<float> coeff2){coeff = coeff2;};
    virtual float operator()(float x) const;
    virtual Fonction* clone() const{
        return new Polynome(*this);
    }
    virtual Fonction* derivee() const;              

};


class Affine:public Polynome{
public:
    Affine(float a, float b):Polynome(a, b){};
};


// L'intéret de faire un clone, c'est de ne pas dépendre de la classe parent.

class Trigo:public Fonction{
    string nom;
public:
    Trigo(string type);
    virtual Fonction* clone() const{
        return new Trigo(*this);
    }
    Fonction* derivee() const;
    float operator()(float x) const{
        if (nom == "cos") {
            return cos(x);
        }
        if (nom == "sin") {
            return sin(x);
        }
        if (nom == "tan") {
            return tan(x);
        }
        return Fonction::operator()(x);
    }
};


#endif /* Eleve_hpp */
