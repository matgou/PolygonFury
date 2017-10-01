/* carre.h : Fonctions specifiques a la gestion des carres */
#ifndef DEF_CARRE
#define DEF_CARRE

#include "forme.h"

/*
   afficherCarre
   description : affiche a l'ecran le carre passe en parametre
   parametres : la forme a afficher (pointeur), la surface correspondant a l'ecran
   valeur de retour : aucune
   effets de bord : aucun
*/
void afficherCarre(Forme*, SDL_Surface*);

/*
   activationCarre
   description : active la forme passee en parametre
   parametres : pointeur de forme
   valeur de retour : aucune
   effets de bord : aucun
*/
void activationCarre(Forme*);

/*
   destructionCarre
   description : detruit les carres passes en parametres
   parametres : la forme a detruire (pointeur), le tableau de formes, le nombre de formes
   valeur de retour : aucune
   effets de bord : aucun
*/
void destructionCarre(Forme*, Forme*[], int);

#endif
