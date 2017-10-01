/* niveau.h : Fonctions relatives a la gestion des niveaux
   affichages, chargements du niveau et de la progression, sauvegarde de la progression...*/

#ifndef DEF_NIVEAU
#define DEF_NIVEAU
#include "forme.h"
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <stdio.h>
#include "main.h"

//Structure d'un niveau
typedef struct{

    //Nom du niveau
    char* nom;

    //Nom du niveau suivant
    char* nomNiveauSuivant;

    //Nombre de formes a gerer
    int nbDeCercles[NB_MAXI_DE_VIES];
    int nbDeCarres[NB_MAXI_DE_VIES];
    int nbDeTriangles[NB_MAXI_DE_VIES];
    int scoreMini;
    int nbDeFormes;
    int codeNiveau;


}Niveau;

/*
   lancerNiveau
   description : lance le niveau, gere les affichages, l'allocation des formes...
   parametres : le nombre de clics autorises pour le niveau, le niveau a lancer
   effet de bord : alloue, puis libere de l'espace memoire
*/
void lancerNiveau(int,Niveau*);

/*
   chargerNiveau
   description : charge le niveau passe en parametre
   parametres : le nombre de clics autoris�s pour le niveau, le niveau a lancer
*/
Niveau* chargerNiveau(char*);

/*
   sommeDuTableau
   description : somme les elements d'un tableau d'entiers entre l'indice indiceDepart, et l'indice indiceFin
   parametres : le tableau, les indices de depart et de fin
   valeur de retour : la somme des elements
*/
int sommeDuTableau(int tableau[],int indiceDepart,int indiceFin);

/*
   afficherResultatNiveau
   description : affiche le resultat effectue au niveau passe en parametre
   parametres : pointeur vers le niveau en question
   valeur de retour : le score effectue
*/
int afficherResultatNiveau(Niveau *niv);

/*
   sauvegarderProgression
   description : sauvegarde la progression de l'utilisateur dans un fichier
   effet de bord : creation d'un fichier
*/
void sauvegarderProgression();

/*
   chargerProgression
   description : chargement de la progression de l'utilisateur
   valeur de retour : renvoie un entier correspondant au codeNiveau atteint par l'utilisateur (code de 1 a 40)
        1 : correspond au niveau easy1, 2 a easy2.... et 40 a insane10
*/
int chargerProgression();

/*
   afficheTxtNiveau
   description : affichage des textes durant un niveau
   parametres : tableau de surfaces correspondant aux textes a afficher, nb de clics autorises, objectif (entier), nb total de formes
*/
void afficheTxtNiveau(SDL_Surface[],int,int,int);

#endif
