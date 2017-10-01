
/*
Constantes.h

Définit les constantes de tout le programme
*/

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define WIDTH 640
#define HEIGHT 480
#define IMG_BITRATE 32

//Constantes de temps
#define DUREE_MINI_ITERATION 40
#define DUREE_MINI_INTER_CLIC 500
#define DUREE_AVANT_DISPARITION 1000
#define DUREE_EXPLOSION 250
#define DUREE_AVANT_FIN_DU_JEU 1500

//Constantes pour les formes
#define CERCLE 1
#define CARRE 2
#define TRIANGLE 3

//Emplacement des images
#define IMG_CERCLE "img/redCircle.bmp"
#define IMG_CERCLE_ACTIF "img/activeCircle.bmp"
#define IMG_CERCLE_EXPLODE "img/explodeCircle.bmp"
#define IMG_CERCLE_GRISE "img/shadowCircle.bmp"
#define IMG_CERCLE_DORE "img/goldCircle.bmp"
#define IMG_CERCLE_NOIR "img/blackCircle.bmp"
#define IMG_CARRE "img/greenSquare.bmp"
#define IMG_CARRE_ACTIF "img/activeSquare.bmp"
#define IMG_CARRE_GRISE "img/shadowSquare.bmp"
#define IMG_CARRE_DORE "img/goldSquare.bmp"
#define IMG_CARRE_NOIR "img/blackSquare.bmp"
#define IMG_TRIANGLE "img/blueTriangle.bmp"
#define IMG_TRIANGLE_ACTIF "img/activeTriangle.bmp"
#define IMG_TRIANGLE_GRISE "img/shadowTriangle.bmp"
#define IMG_TRIANGLE_DORE "img/goldTriangle.bmp"
#define IMG_TRIANGLE_NOIR "img/blackTriangle.bmp"
#define IMG_FOND "img/imageDeFond.bmp"

//Caractéristiques des images
#define FORME_SIZE 24
#define EXPLODE_SIZE 72
#define TRANSPARENCE_RED_RATE 255
#define TRANSPARENCE_GREEN_RATE 0
#define TRANSPARENCE_BLUE_RATE 255

//Constantes de vitesse pour les formes
#define VITESSE_MINI -2
#define VITESSE_MAXI 2
#define VITESSE_CARRE 4

//Parametres de police
//Emplacement des fichiers de police
#define POLICE "police.ttf"
#define POLICE_MENU "police_eva.ttf"

#define TAILLE_POLICE 20
#define TAILLE_POLICE_MENU 20
#define TAILLE_POLICE_TXT 30

#define COULEUR_TEXTE {0,0,0,0}
#define COULEUR_TEXTE_MENU {255,255,255,0}

//Drapeaux pour le retour de la fonction afficherResultat
#define NEXT_LEVEL 1
#define REPLAY 2
#define LEVEL_SELECT 3

//Flags pour le menu principal
#define NEW_GAME 1
#define CONTINUE 2
#define QUIT 3
#define INSTRUCTION 4
#define MENU_PRINCIPAL 5

//Autres constantes : nombre de clics, nombre maximal de vies d'une forme
#define NB_DE_CLICS 5
#define NB_MAXI_DE_VIES 4
#endif
