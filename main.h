/* main.h : Fichier principal de l'application
    definition de variables globales
    gestion de l'initialisation, du lancement des menus, de l'arret du programme...*/
#ifndef DEF_MAIN
#define DEF_MAIN

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#include "constantes.h"
#include "niveau.h"
#include "menu.h"

//Variables globales :
SDL_Surface *ecran; //Surface de l'ecran
SDL_Surface *imageDeFond; // Image de fond de l'ecran

//Variable contenant les caractéristiques des polices
TTF_Font *police;
TTF_Font *policeMenu;
TTF_Font *policeTxt;
//Variable de score
int score;
int progression;

// Variable permettant d'indiquer au programme que l'on souhaite le quitter
int commandeTerminerProgramme;

/*
   initialise
   description : initialise le programme et l'affichage (generateur aleatoire, progression utilisateur, librairies, generation la fenêtre, etc...)
   parametres : aucun
   valeur de retour : aucun
*/
void initialise();

/*
   quit
   description : gere l'interruption des SDL
*/
void quit();

/*
   menuPrincipal
   description : gere le menu principal de l'application
   valeur de retour : aucun
*/
void menuPrincipal();

/*
   menuSelectionNiveau
   description : gere le menu de selection de niveau
   valeur de retour : aucun
*/
int menuSelectionNiveau();
#endif
