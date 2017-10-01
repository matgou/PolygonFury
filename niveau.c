#include "niveau.h"

int sommeDuTableau(int tableau[],int indiceDepart,int indiceFin)
{
    int i;
    int retour=0;
    for (i=indiceDepart;i<=indiceFin;i++)
    {
        retour+=tableau[i];
    }
    return retour;
}


void lancerNiveau(int nbDeClics, Niveau *niv)
{
    Forme **listeFormes;
    Forme **listeCercles;
    Forme **listeCarres;
    Forme **listeTriangles;

    int nbDeCercles=sommeDuTableau(niv->nbDeCercles,0,NB_MAXI_DE_VIES-1);
    int nbDeCarres=sommeDuTableau(niv->nbDeCarres,0,NB_MAXI_DE_VIES-1);
    int nbDeTriangles=sommeDuTableau(niv->nbDeTriangles,0,NB_MAXI_DE_VIES-1);

    int i;
    score=0;
    int continuer=1;

    int tempsPrecedent=0;
    int tempsActuel=0;
    int tempsPrecedentClic=0;
    int tempsFin=0;

    SDL_Rect positionFont;
    positionFont.x=0;
    positionFont.y=0;

    int auMoinsUneActive; //retourne 1 si au moins une des formes est encore active

    SDL_Event event;//Variable d'evènements

    //Generation des formes
    int nbDeFormes=nbDeCercles+nbDeCarres+nbDeTriangles;
    niv->nbDeFormes=nbDeFormes;
    listeFormes=(Forme**)malloc(nbDeFormes*(sizeof(Forme*)));
    for (i=0;i<nbDeFormes;i++)
    {
        listeFormes[i]=(Forme*)malloc(sizeof(Forme));
    }
    listeCercles=listeFormes;
    listeCarres=&listeFormes[nbDeCercles];
    listeTriangles=&listeFormes[nbDeCercles+nbDeCarres];

    allouerFormes(listeCercles,niv->nbDeCercles,CERCLE);
    allouerFormes(listeCarres,niv->nbDeCarres,CARRE);
    allouerFormes(listeTriangles,niv->nbDeTriangles,TRIANGLE);

    //Generation des textes (pour ne pas les recalculer à chaque fois ;) )
    SDL_Color couleur=COULEUR_TEXTE;
    SDL_Surface *scoreTxt=TTF_RenderText_Blended(police, "Score : ", couleur);
    SDL_Surface *clicTxt=TTF_RenderText_Blended(police, "Nombre de clics restants : ", couleur);
    SDL_Surface *retour=TTF_RenderText_Blended(police, "RETOUR", couleur);
    SDL_Surface *objAtteint=TTF_RenderText_Blended(police, "\\o/", couleur);
    SDL_Surface *nomNiveau=TTF_RenderText_Blended(police, niv->nom, couleur);
    char objectif[20]="Objectif : ";
    int scoreMin=niv->scoreMini;
    char toto[20];
    sprintf(toto,"%d",scoreMin);
    strcat(objectif,toto);
    SDL_Surface *objectifSurf=TTF_RenderText_Blended(police, objectif, couleur);
    SDL_Surface textes[]={*nomNiveau, *scoreTxt, *clicTxt,*retour,*objectifSurf,*objAtteint};


    //Boucle principale
    while (continuer)
    {
        SDL_PollEvent(&event); //recuperation des evenements
        tempsActuel = SDL_GetTicks(); //recuperation du temps

        //On verifie que 30ms se sont ecoulees depuis le dernier rafraichissement d'ecran
        if (tempsActuel - tempsPrecedent > DUREE_MINI_ITERATION)
        {
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,255));
            SDL_BlitSurface(imageDeFond,NULL,ecran,&positionFont);
            deplacerMultipleFormes(listeFormes,nbDeFormes);
            afficherMultipleFormes(listeFormes,ecran,nbDeFormes);
            afficheTxtNiveau(textes,nbDeClics,niv->scoreMini,nbDeFormes);
            SDL_Flip(ecran);
            tempsPrecedent=tempsActuel;
            for (i=0;i<nbDeFormes;i++)
            {
                if (listeFormes[i]->estActive==1 && listeFormes[i]->estAffichee==1)
                {
                    auMoinsUneActive=1;
                    break;
                }
            }
            // Si l'utilisateur n'a plus de clic
            if (auMoinsUneActive==0 && nbDeClics<=0 && tempsFin==0)
            {
                tempsFin=DUREE_AVANT_FIN_DU_JEU+tempsActuel;
            }
            auMoinsUneActive=0;

            // Si l'utilisateur a gagne : corespond a toute les forme detruite :
            if (score>=nbDeFormes && tempsFin==0)
            {
                tempsFin=DUREE_AVANT_FIN_DU_JEU+tempsActuel;
            }

            // Si la fin du jeu est déclaree par tempsFin on attend
            // et on termine le jeu
            if (tempsActuel>=tempsFin && tempsFin!=0)
            {
                continuer=0;
            }
        }

        //On gère les évènements
        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (tempsActuel-tempsPrecedentClic>DUREE_MINI_INTER_CLIC && nbDeClics>0)
            {
                //On active la forme sur laquelle l'utilisateur a clique (si elle existe)
                if (activationFormeAuxCoordonnees(listeFormes,nbDeFormes,event.button.x,event.button.y)==1)
                {
                    tempsPrecedentClic=tempsActuel;
                    nbDeClics--;
                }
            }
            //Si on clique sur retour, on revient au menu
            if (event.button.x>WIDTH-retour->w && event.button.y<retour->h)
            {
                continuer=0;
            }
            break;
        case SDL_QUIT:
            continuer=0;
            commandeTerminerProgramme=1;
        }
    }
    libererMemoireFormes(listeFormes,nbDeFormes);
    SDL_FreeSurface(nomNiveau);
    SDL_FreeSurface(scoreTxt);
    SDL_FreeSurface(clicTxt);
    SDL_FreeSurface(retour);
    SDL_FreeSurface(objectifSurf);
    SDL_FreeSurface(objAtteint);
    printf("Votre score est de %d",score);
    if (nbDeClics>0)
    {
        printf("\nVous aviez encore droit a %d clics",nbDeClics);
    }
    printf("\n");
}

Niveau* chargerNiveau(char* nomNiveau)
{
    FILE* fichier=NULL;
    const int nbCaracteresParLigne=62;
    char *ligneLue=(char*)malloc(nbCaracteresParLigne*sizeof(char));
    char *nomNiveauLu=(char*)malloc(11*sizeof(char));
    char *chaineNbDeCercles=(char*)malloc(4*sizeof(char));
    char *chaineNbDeCarres=(char*)malloc(4*sizeof(char));
    char *chaineNbDeTriangles=(char*)malloc(4*sizeof(char));
    char *chaineScoreMini=(char*)malloc(4*sizeof(char));

    int j=0;
    int i=0;
    int codeNiveau=0;

    fichier = fopen("niveaux.csv","r");

    //si erreur d'ouverture
    if (fichier==NULL)
    {
        return NULL;
    }

    if (ligneLue==NULL || nomNiveauLu==NULL || chaineNbDeCarres==NULL || chaineNbDeCercles==NULL || chaineNbDeTriangles==NULL || chaineScoreMini==NULL)
    {
        printf("Erreur d'allocation memoire");
        return NULL;
    }

    while (fgets(ligneLue,nbCaracteresParLigne+2,fichier)!=NULL)
    {
        codeNiveau++;
        j=0;
        for (i=0;i<10;i++)
        {
            if (ligneLue[i]!=' ')
            {
                nomNiveauLu[j]=ligneLue[i];
                j++;
            }

        }
        nomNiveauLu[j]='\0';
        if (strcmp(nomNiveauLu,nomNiveau)==0) //si la ligne correspond au niveau souhaite, on le charge
        {
            printf("Chargement du niveau : %s\n",nomNiveauLu);
            Niveau *niv=(Niveau*)malloc(sizeof(Niveau));
            niv->nom=nomNiveau;

            for (j=0;j<NB_MAXI_DE_VIES;j++) //j correspond a la colonne selon le nb de vies accordees
            {
                for (i=0;i<3;i++)
                {
                    chaineNbDeCercles[i]=ligneLue[11+i+4*j];
                }
                chaineNbDeCercles[4]='\0';
                niv->nbDeCercles[j]=atoi(chaineNbDeCercles);
            }

            for (j=0;j<NB_MAXI_DE_VIES;j++)
            {
                for (i=0;i<3;i++)
                {
                    chaineNbDeCarres[i]=ligneLue[27+i+4*j];
                }
                chaineNbDeCarres[4]='\0';
                niv->nbDeCarres[j]=atoi(chaineNbDeCarres);
            }

            for (j=0;j<NB_MAXI_DE_VIES;j++)
            {
                for (i=0;i<3;i++)
                {
                    chaineNbDeTriangles[i]=ligneLue[43+i+4*j];
                }
                chaineNbDeTriangles[4]='\0';
                niv->nbDeTriangles[j]=atoi(chaineNbDeTriangles);
            }
            for (i=0;i<3;i++)
            {
                chaineScoreMini[i]=ligneLue[59+i];
            }
            chaineScoreMini[4]='\0';
            niv->scoreMini=atoi(chaineScoreMini);

            //Recuperation du nom du niveau suivant
            fgets(ligneLue,nbCaracteresParLigne+2,fichier);
            j=0;
            for (i=0;i<10;i++)
            {
                if (ligneLue[i]!=' ')
                {
                    nomNiveauLu[j]=ligneLue[i];
                    j++;
                }

            }
            nomNiveauLu[j]='\0';
            niv->nomNiveauSuivant=nomNiveauLu;
            niv->codeNiveau=codeNiveau;
            return niv;
        }
    }

    // Liberation de la memoire
    free(ligneLue);
    free(nomNiveauLu);
    free(chaineNbDeCercles);
    free(chaineNbDeCarres);
    free(chaineNbDeTriangles);
    free(chaineScoreMini);

    return NULL;
}

void sauvegarderProgression()
{

    FILE* fichier=NULL;

    fichier = fopen("progression.txt","w");

    //si erreur d'ouverture
    if (fichier==NULL)
    {
        return;
    }

    fprintf(fichier,"%.3d",progression);
    fclose(fichier);

}

int chargerProgression()
{
    FILE *fichier=NULL;
    int nbCaracteresParLigne=3;
    char *ligneLue=(char*)malloc(nbCaracteresParLigne*sizeof(char));
    fichier=fopen("progression.txt","r");

    //si erreur d'ouverture
    if (fichier==NULL)
    {
        return 0; //pas de progression -> retour au niveau 1
    }
    if (fgets(ligneLue,nbCaracteresParLigne+2,fichier)==NULL)
    {
        return 0;
    }
    return atoi(ligneLue);
}

int afficherResultatNiveau(Niveau *niv)
{
    int continuer=1;
    SDL_Event event;//Variable d'evènements

    char texte[]="Score :";
    char texteScore[8]="";
    sprintf(texteScore,"%d/%d",score,niv->nbDeFormes);


    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,155,155,155));
    afficherTexteStyleMenu(texte,200,100);
    afficherTexteStyleMenu(texteScore,220,150);
    afficherTexteStyleMenu(niv->nom,0,0);
    afficherTexteStyleMenu("Level Select",320,0);
    afficherTexteStyleMenu("Replay",470,400);
    afficherTexteStyleMenu("Next",520,450);


    if (score>=niv->scoreMini)
    {
        afficherTexteStyleMenu("Level passed",180,200);
    }
    else
    {
        afficherTexteStyleMenu("Level failed",180,200);
    }

    SDL_Flip(ecran);
    while (continuer)
    {
        SDL_PollEvent(&event); //recuperation des evenements
        //On gère les évènements
        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.x>320 && event.button.y<50)
            {
                return LEVEL_SELECT;
            }
            if (event.button.x>470 && event.button.y>400 && event.button.y<450)
            {
                return REPLAY;
            }
            if (event.button.x>520 && event.button.y>450 && score>=niv->scoreMini)
            {
                return NEXT_LEVEL;
            }
            break;
        case SDL_QUIT:
            continuer=0;
            commandeTerminerProgramme=1;
        }
    }
    return REPLAY;
}

void afficheTxtNiveau(SDL_Surface textes[],int nbDeClics,int objectif,int total)
{
    //Syntaxe : SDL_Surface[] textes={nomNiveau,scoreTxt,ClicTxt,retour,objectif,objAtteint};
    SDL_Color couleur = COULEUR_TEXTE;
    SDL_Rect position;

    //Affichage du nom du niveau
    position.x=0;
    position.y=0;
    SDL_BlitSurface(textes, NULL, ecran, &position);

    //Affichage du nombre de clics restants
    char clics[50];
    sprintf(clics,"%d",nbDeClics);
    SDL_Surface *nbClics=TTF_RenderText_Blended(police,clics,couleur);
    position.y=HEIGHT-textes[2].h;
    SDL_BlitSurface(&textes[2], NULL, ecran, &position);
    position.x+=textes[2].w;
    SDL_BlitSurface(nbClics, NULL, ecran, &position);

    //On affiche l'objectif
    position.x=0;
    position.y-=textes[4].h;
    SDL_BlitSurface(&textes[4], NULL, ecran, &position);
    //On détermine si l'objectif est atteint
    if (score>=objectif)
    {
        position.x+=textes[4].w;
        SDL_BlitSurface(&textes[5],NULL, ecran, &position);//On dit que c'est bon ;)
    }

    //Affichage du bouton retour
    position.x=WIDTH-textes[3].w;
    position.y=0;
    SDL_BlitSurface(&textes[3], NULL, ecran, &position);

    //Affichage du score
    char scoreStr[50];
    sprintf(scoreStr, "%d/%d", score,total);
    SDL_Surface *scoreSurf=TTF_RenderText_Blended(police, scoreStr, couleur);
    position.y=HEIGHT-scoreSurf->h;
    position.x=WIDTH-scoreSurf->w;
    SDL_BlitSurface(scoreSurf, NULL, ecran, &position);
    position.x=WIDTH-textes[1].w;
    position.y-=textes[1].h;
    SDL_BlitSurface(&textes[1], NULL, ecran, &position);


    //Liberation des surfaces
    SDL_FreeSurface(scoreSurf);
    SDL_FreeSurface(nbClics);
}
