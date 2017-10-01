/* triangle.h : Fonctions specifiques a la gestion des triangles */
#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "SDL_draw.h"
#include "forme.h"

/*
   afficherTriangle
   description : affiche a l'ecran le triangle passe en parametre
   parametres : la forme a afficher (pointeur), la surface correspondant a l'ecran
   valeur de retour : aucune
   effets de bord : aucun
*/
void afficherTriangle(Forme*, SDL_Surface*);

/*
   activationTriangle
   description : active la forme passee en parametre
   parametres : pointeur de forme
   valeur de retour : aucune
   effets de bord : aucun
*/
void activationTriangle(Forme*);


/*
   destructionTriangle
   description : detruit le triangle passe en parametre
   parametres : la forme a detruire (pointeur), le tableau de formes, le nombre de formes
   valeur de retour : aucune
   effets de bord : aucun
*/
void destructionTriangle(Forme*, Forme*[], int);



#endif
