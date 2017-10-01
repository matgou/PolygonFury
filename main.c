#include "main.h"

int main ()
{
    initialise();
    //On lance le premier menu
    menuPrincipal();
    //Arrêt de la SDL
    quit();
    return EXIT_SUCCESS;
}

void initialise()
{

    //Initialisation du générateur aleatoire : les deplacements sont "totalement" aleatoires
    srand(time(NULL));

    //Chargement de la progression de l'utilisateur
    progression=chargerProgression();

    //Initialisation de la variable permettant l'arret du programme
    commandeTerminerProgramme=0;

    //On charge la SDL et on teste les erreurs
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //On charge la bibliothèque de polices
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    //On configure le mode video
    ecran=SDL_SetVideoMode(WIDTH,HEIGHT,IMG_BITRATE,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (ecran==NULL)
    {
        fprintf(stderr,"Impossible de charger le mode vidéo : %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //On change la couleur de fond
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    //Titre de la Fenêtre
    SDL_WM_SetCaption("Polygon Fury", NULL);

    // Chargement de l'image de fond
    imageDeFond=SDL_LoadBMP(IMG_FOND);

    //Initialisation de la police
    police=TTF_OpenFont(POLICE, TAILLE_POLICE);
    policeMenu=TTF_OpenFont(POLICE_MENU, TAILLE_POLICE_MENU);
    policeTxt=TTF_OpenFont(POLICE, TAILLE_POLICE_TXT);
}

void menuPrincipal()
{
    int choix=0;
    while (!commandeTerminerProgramme)
    {
        if (choix==CONTINUE)
        {
            choix=menuSelectionNiveau();
        }
        else if (choix==NEW_GAME)
        {
            //ON reinitialise le fichier de niveaux
            progression=0;
            sauvegarderProgression();
            choix=CONTINUE;//on va vers le menu de niveau
        }
        else if (choix==QUIT)
        {
            commandeTerminerProgramme=1;
        }
	else if (choix==INSTRUCTION)
        {
	  choix=afficheInstructions();
	} 
        else
        {
            choix=afficheMenuPrincipal();

        }
    }
}

int menuSelectionNiveau()
{
    int choix=0;
    char* nomDuNiveau;
    Niveau* niveauChoisi;
    while (!commandeTerminerProgramme)
    {
        if (choix==NEXT_LEVEL)
        {
            nomDuNiveau=niveauChoisi->nomNiveauSuivant;
        }
        else
        {
            if (choix==REPLAY)
            {
                nomDuNiveau=niveauChoisi->nom;
            }
            else
            {
                nomDuNiveau=selectionNiveau();
            }
        }

        if (nomDuNiveau==NULL)  //Une erreur s'est produite lors de la selection du niveau
        {
            return -1;
        }
       
        niveauChoisi=chargerNiveau(nomDuNiveau);
        if (niveauChoisi==NULL)
        {
            fprintf(stderr,"Erreur de chargement du niveau\n");
            exit(EXIT_FAILURE);
        }
	
        //On lance le niveau
        lancerNiveau(NB_DE_CLICS,niveauChoisi);


        if(score>=niveauChoisi->scoreMini && progression+1==niveauChoisi->codeNiveau){

            progression++;
            sauvegarderProgression();
        }
        choix=afficherResultatNiveau(niveauChoisi);
        score=0;
    }
    return 0;
}

void quit()
{
    TTF_CloseFont(police);
    TTF_CloseFont(policeMenu);
    TTF_Quit();
    SDL_Quit();
}
