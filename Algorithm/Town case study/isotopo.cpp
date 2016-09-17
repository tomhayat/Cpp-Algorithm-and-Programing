#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <map>
#include <set>
#include "point2d.h"
#include "town.h"

using namespace std;


#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes.txt";

/*
 * Study French isotoponyms
 */
int main()
{
    //
    // Read town file
    //
    // Create an empty list of towns
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
	cout << "Error while reading file" << endl;
	return 2;
    }
    if (nb_towns == 0) {
	cout << "No town found" << endl;
	return 1;
    }
    // Say how many towns have been read
    cout << "File read in: "
	 << ((float)(time2-time1)/CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
	 << towns.size() /* same as nb_towns */ << endl;
    cout << "First town in file: " << towns[0] << endl;
    
    //**** Question 1 ****
    map<string, int> M;
    for(int i=0; i<towns.size(); i++){
        M[towns[i].name()]++;
    }
    map<int, int> Histo; // (nombre de repetitions x, nombre de villes ayant x villes de même nom)
    for(map<string,int>::iterator it=M.begin(); it!=M.end(); ++it){
        Histo[it->second]++;
    }
    //**** Affichage de l'histogramme ****
    cout << "n occurences du nom de ville : Nombre de villes" << endl;
    for(map<int,int>::iterator it=Histo.begin(); it!=Histo.end(); ++it){
        cout << it->first << " : " << it->second << endl;
    }
    //********************
    
    
    //**** Question 2 ****
    map<Point2D, int> Point;
    for(int i=0; i<towns.size(); i++){
        Point[towns[i].point()]++;
    }
    map<int, int> Histo2; // (nombre de repetitions x, nombre de villes ayant x villes de mêmes coordonnées)
    for(map<Point2D,int>::iterator it=Point.begin(); it!=Point.end(); ++it){
        Histo2[it->second]++;
    }
    //**** Affichage de l'histogramme****
    cout << "n occurences des coordonnées de villes : Nombre de villes" << endl;
    for(map<int,int>::iterator it=Histo2.begin(); it!=Histo2.end(); ++it){
        cout << it->first << " : " << it->second << endl;
    }
    //********************
    
    
    //**** Question 3 ****
    set<Town> N;
    set<Town> C;
    for(int i=0; i<towns.size(); i++){
        if (M[towns[i].name()]>1){
            N.insert(towns[i]);
        }
        if (Point[towns[i].point()]>1){
            C.insert(towns[i]);
        }
    }
    
    vector<Town> Intersection;
    Intersection.reserve(towns.size());
    vector<Town>::iterator it;
    // Intersection des villes qui ont au moins une ville de même nom et une ville de mêmes coordonnées.
    it = set_intersection(N.begin(), N.end(), C.begin(), C.end(), Intersection.begin());
    cout << "N inter C : " <<(it-Intersection.begin()) << endl;
    //********************
    

    //**** Question 4 ****
    clock_t time3 = clock();
    map<string,set <Point2D> > meme_Nom;
    map<Point2D,set <string> > meme_Coord;
    for(int i = 0;i<towns.size();i++){
        meme_Nom[towns[i].name()].insert(towns[i].point());
        meme_Coord[towns[i].point()].insert(towns[i].name());
    }

    int compteur = 0;
    int res = 0;
    set<string>::iterator iter;
    set<string>::iterator iter2;
    vector<Point2D> inter2;
    inter2.reserve(20);
    set<Point2D> A;
    set<Point2D> B;
    vector<Point2D>::iterator inter3;
    for(map<Point2D, set<string> >::iterator it5=meme_Coord.begin(); it5!=meme_Coord.end(); ++it5){
        set <string> vec = it5->second;
        if(vec.size()>1){
            for(iter=vec.begin(); iter!=vec.end(); iter++){
                for(iter2=iter; iter2!=vec.end(); iter2++){ //Couples de villes dont les coords sont "proches".
                    if(iter2!=iter){
                        A = meme_Nom[*iter];
                        B = meme_Nom[*iter2];
                        inter3 = set_intersection(A.begin(), A.end(), B.begin(), B.end(), inter2.begin());
                        res = res + (inter3-inter2.begin()-1)*2;
                        // L'intersection contient iter->name() donc on soustrait 1 à la difference.
                        // La multiplication par 2 vient de la symetrie du probleme.
                        inter2.resize(20);
                    }
                    compteur +=1;
                    
                }
            }
        }
    }
    clock_t time4 = clock();
    cout << "La reponse est " << res << endl;
    cout << "Nombre d'iterations = " << compteur << endl;
    cout << "Obtenu en : " << ((float)(time4-time3)/CLOCKS_PER_SEC) << endl;

    return 0;
}



