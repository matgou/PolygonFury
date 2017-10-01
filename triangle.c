#include "triangle.h"

void afficherTriangle(Forme *f, SDL_Surface *ecran)
{
    if (f->estAffichee==1)
    {
        SDL_BlitSurface(f->surf, NULL, ecran, &f->pos);
    }
    else
    {
        if (f->estExplosion==1 && f->tempsExplosion<DUREE_EXPLOSION/DUREE_MINI_ITERATION)
        {
            SDL_BlitSurface(f->surf, NULL, ecran, &f->pos);
            if (f->posFormeSuivante.x!=0 && f->posFormeSuivante.y!=0)
            {
                Draw_Line(ecran, f->pos.x+FORME_SIZE/2,f->pos.y+FORME_SIZE/2
                          , f->posFormeSuivante.x+FORME_SIZE/2, f->posFormeSuivante.y+FORME_SIZE/2,0xb6b6b6);
            }
            f->tempsExplosion++;
        }
    }
}

void activationTriangle(Forme* f)
{
    if (f->estExplosion==0)
    {
        if (f->nbDeVies==1)
        {
            char *image;

            // On rend la forme active
            f->estActive=1;

            //On change l'image de la forme
            image=IMG_TRIANGLE_ACTIF;
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

void destructionTriangle(Forme* f, Forme* formes[], int nbDeFormes)
{
    if (f->estExplosion==0)
    {
        int i;
        int j=0;

        // Affichage de l'explosion
        f->estExplosion=1;
        f->estAffichee=0;
        // Creation d'un tableau temporaire pour stocker les formes non actives
        Forme** formesActives;
        formesActives=(Forme**)malloc(nbDeFormes*sizeof(Forme*));
        for (i=0;i<nbDeFormes;i++)
        {
            if (formes[i]->estActive==0)
            {
                formesActives[j]=formes[i];
                j++;
            }
        }
        if (j!=0) //s'il reste des formes inactives
        {
            int numeroAleatoire;
            if (j==1)
            {
                numeroAleatoire=0; //s'il n'en reste qu'une, la selectionner
            }
            else
            {
                numeroAleatoire=rand_a_b(1,j)-1; //sinon, tirage aleatoire (respectant les preconditions de rand_a_b)
            }
            (formesActives[numeroAleatoire]->activationForme)(formesActives[numeroAleatoire]); //active la forme choisie
            f->posFormeSuivante.x=formesActives[numeroAleatoire]->pos.x;
            f->posFormeSuivante.y=formesActives[numeroAleatoire]->pos.y;
        }
        score++;
    }
}


