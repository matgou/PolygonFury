#include "cercle.h"

void afficherCercle(Forme *f, SDL_Surface *ecran)
{
    if (f->estAffichee==1)
    {
        SDL_BlitSurface(f->surf, NULL, ecran, &f->pos);
    }
    else
    {
        if (f->estExplosion==1 && f->tempsExplosion<DUREE_EXPLOSION/DUREE_MINI_ITERATION)
        {
            SDL_Rect pos;
            pos.x=f->pos.x+(-EXPLODE_SIZE+FORME_SIZE)/2;
            pos.y=f->pos.y+(-EXPLODE_SIZE+FORME_SIZE)/2;
            SDL_BlitSurface(surfExplosion, NULL, ecran, &pos);
            f->tempsExplosion++;
        }
    }
}

void activationCercle(Forme* f)
{
    if (f->estExplosion==0)
    {
        if (f->nbDeVies==1)
        {
            char *image;

            // On rend la forme active
            f->estActive=1;

            //On change l'image de la forme
            image=IMG_CERCLE_ACTIF;
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

void destructionCercle(Forme* f, Forme* formes[], int nbDeFormes)
{
    if (f->estExplosion==0)
    {
        int i;
        double distance;
        // Affichage de l'explosion
        f->estAffichee=0;
        f->estExplosion=1;
        for (i=0;i<nbDeFormes;i++)
        {
            distance=distanceFormePoint(formes[i],f->pos.x+FORME_SIZE/2,f->pos.y+FORME_SIZE/2);
            if (distance<(EXPLODE_SIZE)/2+FORME_SIZE/2)
            {
                (formes[i]->activationForme)(formes[i]);
            }
        }
        score++;
    }
}


