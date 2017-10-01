#include "carre.h"

void afficherCarre(Forme *f, SDL_Surface *ecran)
{
    if (f->estAffichee==1)
    {
        SDL_BlitSurface(f->surf, NULL, ecran, &f->pos);
    }
}

void activationCarre(Forme* f)
{
    if (f->estExplosion==0)
    {
        if (f->nbDeVies==1)
        {
            char *image;

            // On rend la forme active
            f->estActive=1;

            //On change l'image de la forme
            image=IMG_CARRE_ACTIF;
            f->surf=SDL_LoadBMP(image);
            SDL_SetColorKey(f->surf, SDL_SRCCOLORKEY, SDL_MapRGB(f->surf->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));

            //On rend la forme immobile
            f->dx=0;
            f->dy=0;
        }
        else
        {
            f->nbDeVies--;
            SDL_SetAlpha(f->surf,SDL_SRCALPHA, 100+38*(f->nbDeVies));
        }
    }
}

void destructionCarre(Forme* f, Forme* formes[], int nbDeFormes)
{
    int i;
    int distance;
    if (f->estExplosion==0)
    {
        // Traitement aleatoire de la trajectoire du carre active
        int choix=rand()%4; //car 4 choix possibles
        switch (choix)
        {
        case 0:
            f->dx=0;
            f->dy=VITESSE_CARRE;
            break;
        case 1:
            f->dx=0;
            f->dy=-VITESSE_CARRE;
            break;
        case 2:
            f->dx=VITESSE_CARRE;
            f->dy=0;
            break;
        case 3:
            f->dx=-VITESSE_CARRE;
            f->dy=0;
            break;
        }
        f->estExplosion=1;
        score++;
    }
    for (i=0;i<nbDeFormes;i++)
    {
        distance=distanceFormePoint(formes[i],f->pos.x+FORME_SIZE/2,f->pos.y+FORME_SIZE/2);
        if (distance<(FORME_SIZE)*sqrt(2) && formes[i]->estAffichee==1 && formes[i]->estActive==0)
        {
            (formes[i]->activationForme)(formes[i]);
            f->estAffichee=0;
            return;
        }
    }
}
