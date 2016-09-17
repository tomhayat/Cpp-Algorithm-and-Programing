#include <Imagine/Graphics.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "../quadtree/quadtree.h"

using namespace Imagine;
using namespace std;

#ifndef srcPath
#define srcPath(s) ("." s)
#endif

// The path and name of the town file
string default_image_file = srcPath("/running-horse-square.png");




// ********** Question 3 **********
void encodeImage(byte* image, frame fr, QuadTree<int> * &quad, int side){
    // Cas d'arrêts
    if (fr.tellColor(image)!=2){
        quad = new QuadLeaf<int>(fr.tellColor(image));
        return;
    }
    quad = new QuadNode<int>(0,0,0,0);
    frame f1 = frame(fr.coordx, fr.coordy, fr.step/2, side);
    frame f2 = frame(fr.coordx+fr.step/2, fr.coordy, fr.step/2, side);
    frame f3 = frame(fr.coordx, fr.coordy+fr.step/2, fr.step/2, side);
    frame f4 = frame(fr.coordx+fr.step/2, fr.coordy+fr.step/2, fr.step/2, side);

    encodeImage(image, f1, quad->son(NW), side);
    encodeImage(image, f2, quad->son(NE), side);
    encodeImage(image, f3, quad->son(SW), side);
    encodeImage(image, f4, quad->son(SE), side);
}

// ********** Question 4 **********
void decodeImage(QuadTree<int> * &quad, byte* &image, frame fr, int side){
    if (quad->isLeaf()){
        if (quad->value()==0){
            fr.fillFrameWith(image, WHITE_Pixel);
            return;
        }
        else{
            fr.fillFrameWith(image, BLACK_Pixel);
            return;
        }
    }
    frame frNW = frame(fr.coordx, fr.coordy, fr.step/2, side);
    frame frNE = frame(fr.coordx+fr.step/2, fr.coordy, fr.step/2, side);
    frame frSW = frame(fr.coordx, fr.coordy+fr.step/2, fr.step/2, side);
    frame frSE = frame(fr.coordx+fr.step/2, fr.coordy+fr.step/2, fr.step/2, side);

    decodeImage(quad->son(NW), image, frNW, side);
    decodeImage(quad->son(NE), image, frNE, side);
    decodeImage(quad->son(SW), image, frSW, side);
    decodeImage(quad->son(SE), image, frSE, side);
}

// Compte les Noeuds dans un QuadTree.
void compteNoeuds(int &compteur, QuadTree<int> * &quad){
    if (quad->isLeaf()){
        compteur += 1;
        return;
    }
    compteur += 1;
    compteNoeuds(compteur, quad->son(NW));
    compteNoeuds(compteur, quad->son(NE));
    compteNoeuds(compteur, quad->son(SW));
    compteNoeuds(compteur, quad->son(SE));
}

int Puiss2plusproche(int w, int h){
    int max;
    if(w < h){
        max = h;
    }
    else
        max = w;
    return int(log2(max)) + 1;
}

// ********** Question 5 **********
void EncodeImageRectangle(byte* image, QuadTree<int>* &quad, int w, int h){
    int side = pow(2,Puiss2plusproche(w, h));
    byte* imagecarre = new byte[side*side];
    // Initialisation de l'image carre.
    for (int i=0; i<side*side; i++) {
        imagecarre[i] = WHITE_Pixel;
    }
    // Remplissons avec l'ancienne image.
    for (int i=0; i<h; i++)
        for(int j=0; j<w; j++){
            imagecarre[j + side*i] = image[j + w*i];
        }
    frame fr = frame(0, 0, side, side);
    encodeImage(imagecarre, fr, quad, side);
}





// ********** Question 6 **********
void encodeGreyImage(byte* image, frame fr, QuadTree<int> * &quad, int side){
    // Cas d'arrêts
    if (fr.tellGreyColor(image)!=256){
        quad = new QuadLeaf<int>(fr.tellGreyColor(image));
        return;
    }
    quad = new QuadNode<int>(0,0,0,0);
    frame f1 = frame(fr.coordx, fr.coordy, fr.step/2, side);
    frame f2 = frame(fr.coordx+fr.step/2, fr.coordy, fr.step/2, side);
    frame f3 = frame(fr.coordx, fr.coordy+fr.step/2, fr.step/2, side);
    frame f4 = frame(fr.coordx+fr.step/2, fr.coordy+fr.step/2, fr.step/2, side);
    
    encodeGreyImage(image, f1, quad->son(NW), side);
    encodeGreyImage(image, f2, quad->son(NE), side);
    encodeGreyImage(image, f3, quad->son(SW), side);
    encodeGreyImage(image, f4, quad->son(SE), side);
}

// Fonction qui renvoie True si les quatre feuilles sont d'intensités voisines.
bool thresh(int threshhold, int a, int b, int c, int d){
    int temp1 = max(a, b);
    int temp2 = max(c, temp1);
    int temp3 = max(d, temp2);
    int temp4 = min(a, b);
    int temp5 = min(c, temp4);
    int temp6 = min(d, temp5);
    if (temp3 - temp6 <= threshhold){
        return true;
    }
    else{
        return false;
    }
}
// Retourne la moyenne de quatre nombres.
int moy(int a, int b, int c, int d){
    return int((a+b+c+d)/4);
}



// Fonction qui effectue un seuillage du QuadTree.
void seuilImage(QuadTree<int> * &quad, int threshold){
    if (quad->nbNodes()==1){
        if (thresh(threshold, quad->son(NW)->value(), quad->son(NE)->value(), quad->son(SE)->value(), quad->son(SW)->value())){
            quad = new QuadLeaf<int>(moy(quad->son(NW)->value(), quad->son(NE)->value(), quad->son(SE)->value(), quad->son(SW)->value()));
            return;
        }
    }
    else if(quad->isLeaf()){
        return;
    }
    seuilImage(quad->son(NW), threshold);
    seuilImage(quad->son(NE), threshold);
    seuilImage(quad->son(SW), threshold);
    seuilImage(quad->son(SE), threshold);
    
}

// Decode l'image en niveaux de gris.
void decodeGreyImage(QuadTree<int> * &quad, byte* &image, frame fr, int side){
    if (quad->isLeaf()){
        fr.fillFrameWith(image, byte(quad->value()));
        return;
    }
    frame frNW = frame(fr.coordx, fr.coordy, fr.step/2, side);
    frame frNE = frame(fr.coordx+fr.step/2, fr.coordy, fr.step/2, side);
    frame frSW = frame(fr.coordx, fr.coordy+fr.step/2, fr.step/2, side);
    frame frSE = frame(fr.coordx+fr.step/2, fr.coordy+fr.step/2, fr.step/2, side);
    
    decodeGreyImage(quad->son(NW), image, frNW, side);
    decodeGreyImage(quad->son(NE), image, frNE, side);
    decodeGreyImage(quad->son(SW), image, frSW, side);
    decodeGreyImage(quad->son(SE), image, frSE, side);
}



int main(int argc, char **argv)
{
//     Get image file
    const char *image_file =
	(argc > 1) ? argv[1] : srcPath("/running-horse-square.png");
    // Load image
    byte* image;
    int width, height;
    cout << "Loading image: " << image_file << endl; 
    loadGreyImage(image_file, image, width, height);
    // Print statistics
    cout << "Image size: " << width << "x" << height << endl;
    cout << "Number of pixels: " << width*height << endl;
    // Display image
    Window window = openWindow(width, height);
    putGreyImage(IntPoint2(0,0), image, width, height);
//     Pause
    click();
    
    // ************ Question 3 ************
    QuadTree<int> *root;
    frame f1 = frame(0,0, width, width);
    encodeImage(image, f1, root, width);
    display(root);
    closeWindow(window);

    
    
    // ************ Question 4 ************
    byte* image2 = new byte[width*width];
    frame f2 = frame(0,0, width, width);
    decodeImage(root, image2, f2, width);
    Window window2 = openWindow(width, height);
    putGreyImage(IntPoint2(0,0), image2, width, height);
    click();
    closeWindow(window2);
    int compteur = 0;
    compteNoeuds(compteur, root);
    cout << "Nombre de bits :" << compteur;
    
    
    
    
    // ************ Question 5 ************

    const char *image_file2 =
    (argc > 1) ? argv[1] : srcPath("/running-horse-rect.png");
    // Load image
    byte* imagemodif;
    int width2, height2;

    loadGreyImage(image_file2, imagemodif, width2, height2);


    QuadTree<int> *quad2;
    EncodeImageRectangle(imagemodif, quad2, width2, height2);
    
    int side = pow(2,Puiss2plusproche(width2, height2));
    cout << side << endl;
    frame fraGrand = frame(0,0,side, side);
    byte* image3 = new byte[side*side];
    decodeImage(quad2, image3, fraGrand, side);
    Window window3 = openWindow(side,side);
    putGreyImage(IntPoint2(0,0), image3, side, side);
    click();
    closeWindow(window3);
    int compteur2=0;
    compteNoeuds(compteur2, quad2);
    cout << "Nombre de bits :" << compteur2;
    

 
    // ************ Question 6 ************
    const char *image_file3 =
    (argc > 1) ? argv[1] : srcPath("/lenaTest3.jpg");
    // Load image
    byte* imagelena;
    int width3, height3;
    
    loadGreyImage(image_file3, imagelena, width3, height3);
    Window window4 = openWindow(width3 ,height3);
    putGreyImage(IntPoint2(0,0), imagelena, width3, height3);
    click();

    
    
    QuadTree<int> *root3;
    frame f3 = frame(0,0, height3, height3);
    encodeGreyImage(imagelena, f3, root3, width3);
    closeWindow(window4);
    int seuil = 50;
    
    // Chaque seuillage ne permet que de monter d'un niveau dans le QuadTree.
    // Il faut itérer cette fonction plusieurs fois (au maximum la profondeur du QuadTree).
    // Nous choisirons ici 6 itérations.
    
    for (int i=0; i<8; i++) {
        seuilImage(root3, seuil);
    }
    cout << "fin"<< endl;

    byte* imagetest = new byte[width3*height3];
    frame ftest = frame(0,0, width3, width3);
    cout << "fin";

    decodeGreyImage(root3, imagetest, ftest, width3);
    
    Window window5 = openWindow(width3, height3);
    putGreyImage(IntPoint2(0,0), imagetest, width3, height3);
    click();
    closeWindow(window5);
    
    
    
    int compteur3 = 0;
    compteNoeuds(compteur3, root3);
    cout << "Nombre de bits :" << compteur3;
    
    delete root;
    delete quad2;
    delete root3;

    return 0;
}
