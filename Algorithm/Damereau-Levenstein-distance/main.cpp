#include <iostream>

using namespace std;

// On crée une fonction qui retourne le minimum de trois nombres.
int minimum(int a, int b, int c){
    if ( a>=b && c>=b ){
        return b;
    }
    else if ( a>=c && b>=c ){
        return c;
    }
    else {
        return a;
    }
}

void Distance_de_Levenshtein(string x, string y){
    const int n = x.length();
    const int m = y.length();
    int d[n+1][m+1]; // On crée un tableau qui va stocker les distances possibles.
    
    // Cas où au moins une des chaînes de caractères est vide.
    if (min(n,m)==0){
        cout << "La distance de Levenshtein est " << max(n,m) << endl;
    }
    else {
        // On initialise la distance une chaîne de caractère vide.
        for (int i=0; i <= n; i++){
            d[i][0] = i;
        }
        for (int j=0; j <= m; j++){
            d[0][j] = j;
        }

        for (int i=1; i<=n; i++){
            for (int j=1; j <= m ; j++){
                d[i][j] = minimum(d[i-1][j] + 1,                            // On supprime un caractère
                                  d[i][j-1] + 1,                            // On insère un caractère.
                                  d[i-1][j-1] + (x[i-1] == y[j-1] ? 0 : 1));// On remplace un caractère.
            }
        }
        cout << "La distance de Levenshtein est " << d[n][m] << "." << endl;
    }

    // Le reste du code sert à afficher la liste des opérations à effectuer.
    // On choisit de passer du mot x au mot y.
    // On part du bas pour remonter : bottom-up.

    int i=n;
    int j=m;
    string phrase = "Pour passer du mot " + x + " au mot " + y + ", on effectue les transformations suivantes: \n";
    cout << phrase;
    string transformations = "";

    while (i>=1 || j>=1){
        if ((d[i-1][j-1] <= min(d[i][j-1],d[i-1][j])) && (d[i-1][j-1] == d[i][j] || d[i-1][j-1] == (d[i][j]-1))){
            // Cas où on remonte sur la diagonale.
            if (d[i-1][j-1] == d[i][j]){
                transformations =  " On ne fait rien. \n" + transformations;
            }
            else{
                transformations = string(" On remplace ") + x[i-1] + string(" par ") + y[j-1] + string(".\n") +
                        transformations;
            }
            i--;
            j--;
        }
        else if (d[i][j-1] <= d[i-1][j] && (d[i][j-1] == d[i][j] || d[i][j] == d[i][j-1]+1)){
            transformations = string(" On insere ") + y[j-1] + string(".\n") + transformations;
            j--;

        }
        else {
            transformations = string(" On supprime ") + x[i-1] + string(".\n") + transformations;
            i--;
        }

    }
    cout << transformations;
}





void Distance_de_Damerau_Levenshtein(string x, string y){
    const int n = x.length();
    const int m = y.length();
    int d[n+1][m+1];

    if (min(n,m)==0){
        cout << "La distance de Damerau-Levenshtein est " << max(n,m) << endl;
    }
    else{

        // On initialise dans le cas ou une chaîne de caractère serait vide.
        for (int i=0; i <= n; i++){
            d[i][0] = i;
        }
        for (int j=0; j <= m; j++){
            d[0][j] = j;
        }
        for (int i=1; i <= n; i++){
            for (int j=1; j <= m ; j++) {

                d[i][j] = minimum(d[i-1][j] + 1,                            // On supprime un caractère
                                  d[i][j-1] + 1,                            // On insère un caractère.
                                  d[i-1][j-1] + (x[i-1] == y[j-1] ? 0 : 1));// On remplace un caractère.

                if (i>=2 && j>=2 && x[i-1] == y[j-2] && x[i-2] == y[j-1]){  //On échange deux caractères.
                    d[i][j] = min(d[i][j], d[i-2][j-2] + 1);
                }
            }
        }
        cout << "La distance de Damerau-Levenshtein est " << d[n][m] << "." <<endl;
    }

    // Le reste du code sert à afficher la liste des opérations à effectuer.
    // On choisit de passer du mot x au mot y.
    // On part du bas pour remonter : bottom-up.

    int i=n;
    int j=m;
    string phrase = "Pour passer du mot " + x + " au mot " + y + ", on effectue les transformations suivantes: \n";
    cout << phrase;
    string transformations = "";

    while (i>=1 || j>=1){
        if (d[i][j] == d[i-2][j-2]+1 && (x[i-1] == y[j-2] && x[i-2] == y[j-1]) ) {
            transformations = string(" On échange ") + x[i-2] + string(" avec ") + x[i-1] +string(".\n") + transformations;
            i=i-2;
            j=j-2;

        }
        else if ((d[i-1][j-1] <= min(d[i][j-1],d[i-1][j])) && (d[i-1][j-1] == d[i][j] || d[i-1][j-1] == (d[i][j]-1))){
            if (d[i-1][j-1] == d[i][j] && x[i-1]==y[j-1]){
                transformations =  " On ne fait rien.\n" + transformations;
            }
            else{
                transformations = string(" On remplace ") + x[i-1] + string(" par ") + y[j-1] + string(".\n") +
                                  transformations;
            }
            i--;
            j--;
        }
        else if (d[i][j-1] <= d[i-1][j] && (d[i][j-1] == d[i][j] || d[i][j] == d[i][j-1]+1)){
            transformations = string(" On insere ") + y[j-1] + string(".\n") + transformations;
            j--;
        }
        else {
            transformations = string(" On supprime ") + x[i-1] + string(".\n") + transformations;
            i--;
        }

    }
    cout << transformations;

}

int main() {
    Distance_de_Levenshtein("ponts", "joint");
    cout << "\n";
    Distance_de_Damerau_Levenshtein("ponts", "joint");
    cout << "\n";
    Distance_de_Levenshtein("ecoles", "eclose");
    cout << "\n";
    Distance_de_Damerau_Levenshtein("ecoles", "eclose");
    return 0;
    
    // Remarque : J'ai travaillé avec Tom Hayat sur ce TP.
    
}

