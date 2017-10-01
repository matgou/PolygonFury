/* cercle.h : Fonctions specifiques a la gestion des cercles */
#ifndef DEF_CERCLE
#define DEF_CERCLE

#include "forme.h"

/*
   afficherCercle
   description : affiche a l'ecran le cercle passe en parametre
   parametres : la forme a afficher (pointeur), la surface correspondant a l'ecran
   valeur de retour : aucune
   effets de bord : aucun
*/
void afficherCercle(Forme*, SDL_Surface*);

/*
   activationCercle
   description : active la forme passee en parametre
   parametres : pointeur de forme
   valeur de retour : aucune
   effets de bord : aucun
*/
void activationCercle(Forme*);

/*
   destructionCercle
   description : detruit le cercle passe en parametre
   parametres : la forme a detruire (pointeur), le tableau de formes, le nombre de formes
   valeur de retour : aucune
   effets de bord : aucun
*/
void destructionCercle(Forme*, Forme*[], int);

#endif
