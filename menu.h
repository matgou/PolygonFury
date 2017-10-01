/* menu.h : Fonctions specifiques a la gestion des menus : affichage,
 selection d'un niveau, chargement des elements du menu... */
#ifndef DEF_MENU
#define DEF_MENU

#include <string.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include "SDL_draw.h"
#include "main.h"

/*
   chargementElementsMenu
   description : charge les differents elements du menu : images, textes...
   parametres : la forme a afficher (pointeur), la surface correspondant a l'ecran
   valeur de retour : aucune
   effets de bord : alloue de la memoire
*/
void chargementElementsMenu();

/*
   afficherTexteStyleMenu
   description : affichage d'un texte de style menu aux coordonnees positionX et positionY
   parametres : le texte a afficher, les coordonnées auxquelles l'afficher
   valeur de retour : aucune
   effets de bord : alloue de la memoire
*/
void afficherTexteStyleMenu(char*,int,int);

/*
   afficheFondMenu
   description : affichage l'animation de fond du menu
   effets de bord : alloue de la memoire
*/
void afficheFondMenu();

/*
   afficheMenuPrincipal
   description : affichage du menu principal de l'application et gestion du choix de l'utilisateur
   valeur de retour : un entier correspondant au choix de l'utilisateur : NEW_GAME, CONTINUE, QUIT
*/
int afficheMenuPrincipal();

/*
   retournerSurfaceDuNiveau
   description : retourne la surface a afficher en fonction d'un code representant le niveau
   parametres : un entier correspondant a un code de niveau : easy:1 -> 1, easy:2 ->2,...,insane:10 -> 40
   valeur de retour : une surface correspondant au niveau choisi
*/
SDL_Surface* retournerSurfaceDuNiveau(int);

/*
   selectionNiveau
   description : affiche le menu de selection de niveau et retourne le nom du niveau selectionne par l'utilisateur (par un clic)
   valeur de retour : une chaine de caracteres correspondant au niveau selectionne
*/
char* selectionNiveau();

/*
   selectionNiveauAuxCoordonnees
   description : retourne le nom du niveau selectionne par l'utilisateur (par un clic)
   parametres : coordonnees du clic de l'utilisateur
   valeur de retour : une chaine de caracteres correspondant au niveau selectionne
*/
char* selectionNiveauAuxCoordonnees(int,int);
/*
   afficheInstructions
   description : Affiche les instructions du jeu
   parametres : 
   valeur de retour : un entier 5 pour indiquer au programme un retour au menu principal 
 */
int afficheInstructions();
#endif
