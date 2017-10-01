#include "forme.h"


double distanceFormePoint(Forme* f,int x, int y)
{
    //On retourne la distance euclidienne entre le centre de la forme (position decalee de FORME_SIZE/2) et le point fourni
    return sqrt(pow((f->pos.x+FORME_SIZE/2)-x,2)+pow((f->pos.y+FORME_SIZE/2)-y,2));
}

int rand_a_b(int a,int b)
{
    int nombreGenere = rand()%(b-a)+a;
    //On interdit la valeur 0
    if (nombreGenere==0)
    {
        nombreGenere=rand_a_b(a,b);
    }
    return nombreGenere;
}

void allouerFormes(Forme* formes[], int nbDeFormesSelonNbVies[NB_MAXI_DE_VIES], int typeDeForme)
{
    int i=0;
    int k,j;
    char *image;
    void (*destructionForme)();
    void (*afficherForme)();
    void (*activationForme)();

    switch (typeDeForme)
    {
    case CERCLE: //on effectue des affectations propres au cercle
        image=IMG_CERCLE;
        surfExplosion=SDL_LoadBMP(IMG_CERCLE_EXPLODE);
        SDL_SetColorKey(surfExplosion, SDL_SRCCOLORKEY, SDL_MapRGB(surfExplosion->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
        destructionForme=&destructionCercle; //ici destructionForme va pointer sur une fonction propre au cercle
        afficherForme=&afficherCercle; //afficherForme va dans ce cas pointer vers une fonction du cercle
        activationForme=&activationCercle; //activationForme va ici pointer egalement vers activationCercle
        break;
    case CARRE: //affectation specifiques au carre
        image=IMG_CARRE;
        destructionForme=&destructionCarre;
        afficherForme=&afficherCarre;
        activationForme=&activationCarre;
        break;
    case TRIANGLE: //affectations specifiques au carre
        image=IMG_TRIANGLE;
        destructionForme=&destructionTriangle;
        afficherForme=&afficherTriangle;
        activationForme=&activationTriangle;
        break;
    default:
        fprintf(stderr,"Erreur : Le type de forme fournie n'est pas gere (type de forme : %d)\n",typeDeForme);
        exit(EXIT_FAILURE);
        break;
    }

    //On balaye les valeurs possibles pour le nb de vies
    for (j=1;j<=NB_MAXI_DE_VIES;j++)
    {
        //On balaye les formes ayant "j" vies
        for (k=0;k<nbDeFormesSelonNbVies[j-1];k++)
        {
            formes[i]=malloc(sizeof(Forme));
            formes[i]->pos.x=rand_a_b(0,WIDTH-FORME_SIZE);
            formes[i]->pos.y=rand_a_b(0,HEIGHT-FORME_SIZE);
            formes[i]->dx=rand_a_b(VITESSE_MINI,VITESSE_MAXI);
            formes[i]->dy=-rand_a_b(VITESSE_MINI,VITESSE_MAXI);
            formes[i]->estActive=0;
            formes[i]->tempsActivation=0;
            formes[i]->nbDeVies=j;
            formes[i]->estAffichee=1;
            formes[i]->estExplosion=0;
            formes[i]->tempsExplosion=0;
            formes[i]->surf=SDL_LoadBMP(image);
            formes[i]->typeDeForme=typeDeForme;
            formes[i]->destructionForme=destructionForme;
            formes[i]->afficherForme=afficherForme;
            formes[i]->activationForme=activationForme;
            SDL_SetColorKey(formes[i]->surf, SDL_SRCCOLORKEY, SDL_MapRGB(formes[i]->surf->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
            SDL_SetAlpha(formes[i]->surf, SDL_SRCALPHA, 100+j*38); //affecte la transparence de la forme selon son nb de vies
            i++; //On progresse dans le tableau de formes
        }
    }
}

void deplacerForme(Forme *f)
{
    f->pos.x+=f->dx;
    f->pos.y+=f->dy;

    if (f->pos.x<=0||f->pos.x>=WIDTH-FORME_SIZE)
    {
        if (f->estExplosion==0)
        {
            f->dx*=-1;
        }
        else
        {
            f->estAffichee=0;
        }
    }
    if (f->pos.y<=0||f->pos.y>=HEIGHT-FORME_SIZE)
    {
        if (f->estExplosion==0)
        {
            f->dy*=-1;
        }
        else
        {
            f->estAffichee=0;
        }
    }
}
void afficherMultipleFormes(Forme* formes[], SDL_Surface* ecran, int nbDeFormes)
{
    int i;
    for (i=0;i<nbDeFormes;i++)
    {
        (formes[i]->afficherForme)(formes[i],ecran);
    }
}

void deplacerMultipleFormes(Forme* formes[], int nbDeFormes)
{
    int i;
    for (i=0;i<nbDeFormes;i++)
    {
        deplacerForme(formes[i]);

        if (formes[i]->estActive==1 && formes[i]->estAffichee==1) //Si la forme est active et affichee
        {
            formes[i]->tempsActivation++; //on incremente son temps d'activation
            if (formes[i]->tempsActivation>DUREE_AVANT_DISPARITION/DUREE_MINI_ITERATION) //si son temps d'activation depasse un seuil
            {
                (formes[i]->destructionForme)(formes[i],formes,nbDeFormes); //on detruit la forme
            }
        }
    }
}

/* Active une forme proche des coordonnees x et y */
int activationFormeAuxCoordonnees(Forme* formes[],int nbDeFormes,int x,int y)
{
    int i;
    int retour=0;
    for (i=0;i<nbDeFormes;i++)
    {
        if (distanceFormePoint(formes[i],x,y)<(FORME_SIZE*sqrt(2)/2)&&formes[i]->estActive!=1)
        {
            (formes[i]->activationForme)(formes[i]);
            retour=1;
            break; //on ne peut activer qu'une seule forme
        }

    }
    return retour;
}

/* Libere la memoire allouee lors de la creation des formes passees en argument */
void libererMemoireFormes(Forme* formes[], int nbDeFormes)
{
    int i;
    for (i=0;i<nbDeFormes;i++)
    {
        SDL_FreeSurface(formes[i]->surf); //suppression des surfaces associees aux formes
        free(formes[i]); //suppression de la forme
    }
}

