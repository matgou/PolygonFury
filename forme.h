/* forme.h : Fonctions communes aux differents types de formes : affichage, deplacement... */
#include "cercle.h"
#include "carre.h"
#include "triangle.h"

#ifndef DEF_FORME
#define DEF_FORME

#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include "main.h"

SDL_Surface *surfExplosion;

typedef struct
{
    //Type de forme : cercle, carre, triangle...
    int typeDeForme;

    //Position de la forme
    SDL_Rect pos;

    //Position de la forme affectee (pour tracer le trait sur les triangles)
    SDL_Rect posFormeSuivante;

    //Variables de vitesse
    double dx;
    double dy;

    //Etat de la forme
    int estActive;
    //Duree d'activation de la forme
    int tempsActivation;

    //Etat d'affichage de la forme
    int estAffichee;

    //Etat en explosion
    int estExplosion;
    int tempsExplosion;

    //Surface associée a la forme
    SDL_Surface *surf;

    //Gestion du nombre de vies de la forme
    int nbDeVies;

    //Fonctions liees a la forme
    void (*destructionForme)();
    void (*afficherForme)();
    void (*activationForme)();

}Forme;

/*
   distanceFormePoint
   description : calcule la distance entre le "centre" d'une forme et un point
   parametres : la forme consideree, les coordonnees du point considere
   valeur de retour : la distance (type double)
   effets de bord : aucun
*/
double distanceFormePoint(Forme* ,int , int);

/*
   rand_a_b
   description : génère de nombres aléatoires sur le segment [a,b[
   parametres : les bornes du segment a et b
   valeur de retour : un nombre entier aléatoire compris entre a et b
   effets de bord : aucun
*/
int rand_a_b(int,int);

/*
   allouerFormes
   description : alloue un tableau de formes en memoire
   parametres : le tableau de formes, un tableau contenant le nombre de formes selon leur nombre de vies, le type de forme a creer
   valeur de retour : aucune
   effets de bord : alloue de la memoire
*/
void allouerFormes(Forme*[], int*, int);

/*
   deplacerForme
   description : gère le deplacement d'une forme selon dx et dy
   parametres : la forme a deplacer (pointeur)
   valeur de retour : aucune
   effets de bord : aucun
*/
void deplacerForme(Forme*);

/*
   afficherMultipleFormes
   description : affiche a l'ecran un ensemble de formes
   parametres : un tableau de formes (pointeur) a afficher, une surface correspondant a l'ecran, le nombre total de formes a afficher
   valeur de retour : aucune
*/
void afficherMultipleFormes(Forme*[], SDL_Surface*, int);

/*
   deplacerMultipleFormes
   description : gere le deplacement d'un ensemble de formes
   parametres : un tableau de formes (pointeur) a deplacer, le nombre total de formes a deplacer
   valeur de retour : aucune
*/
void deplacerMultipleFormes(Forme*[], int);

/*
   activationFormeAuxCoordonnees
   description : active la forme se trouvant proche des coordonnees x et y.
   parametres : un tableau de formes (pointeur), le nombre total de formes, les coordonnees x et y
   valeur de retour : 0 si aucune forme trouvee aux coordonnées, 1 sinon
*/
int activationFormeAuxCoordonnees(Forme*[],int,int,int);

/*
   libererMemoireFormes
   description : libere la memoire allouee lors de la creation des formes passees en argument
   parametres : un tableau de formes (pointeur), le nombre total de formes, les coordonnees x et y
   valeur de retour : aucune
   effet de bord : libere de la memoire
*/
void libererMemoireFormes(Forme*[], int);

#endif
