#include "menu.h"

// Declarations des formes grisees -> niveaux non disponibles
static SDL_Surface *carreGrise;
static SDL_Surface *cercleGrise;
static SDL_Surface *triangleGrise;

// Declarations des formes dorees -> niveaux deja completes par l'utilisateur
static SDL_Surface *carreDore;
static SDL_Surface *cercleDore;
static SDL_Surface *triangleDore;

//Declaration de formes noires -> niveau courant
static SDL_Surface *carreNoir;
static SDL_Surface *cercleNoir;
static SDL_Surface *triangleNoir;

static SDL_Surface *masqueDeFond;

static double hauteurLigne=HEIGHT/16; //on a divise en 16 parties la fenetre
static double largeurColonne=WIDTH/27; //on a divise en 20 parties la largeur

static int nbDeCerclesFondMenu[NB_MAXI_DE_VIES]={1,1};
static int nbDeCarresFondMenu[NB_MAXI_DE_VIES]={2,1};
static int nbDeTrianglesFondMenu[NB_MAXI_DE_VIES]={2,3,1};
static int nbDeFormesFondMenu;

static Forme** listeFormesFondMenu;
static Forme** listeCerclesFondMenu;
static Forme** listeCarresFondMenu;
static Forme** listeTrianglesFondMenu;

static SDL_Surface *texteNiveau[4];
static SDL_Surface *titreMenuSelection;
static SDL_Surface *retourMenuPpal;
static SDL_Surface *texteMenuPpal[6];
static SDL_Surface *texteMenuInst[10];


SDL_Surface* retournerSurfaceDuNiveau(int codeNiveau)
{
    int indiceForme=codeNiveau%3;
    if (codeNiveau==progression+1)
    {
        switch (indiceForme)
        {
        case 0:
            return cercleNoir;
            break;
        case 1:
            return carreNoir;
            break;
        case 2:
            return triangleNoir;
            break;
        }
    }
    switch (indiceForme)
    {
    case 0:
        if (progression>=codeNiveau)
        {
            return cercleDore;
        }
        return cercleGrise;

        break;
    case 1:
        if (progression>=codeNiveau)
        {
            return carreDore;
        }
        return carreGrise;
        break;
    case 2:
        if (progression>=codeNiveau)
        {
            return triangleDore;
        }
        return triangleGrise;
        break;
    }
    return NULL;
}



void chargementElementsMenu()
{
    int i;
// Declarations des images

    // Chargement des images
    carreGrise=SDL_LoadBMP(IMG_CARRE_GRISE);
    cercleGrise=SDL_LoadBMP(IMG_CERCLE_GRISE);
    triangleGrise=SDL_LoadBMP(IMG_TRIANGLE_GRISE);
    carreDore=SDL_LoadBMP(IMG_CARRE_DORE);
    cercleDore=SDL_LoadBMP(IMG_CERCLE_DORE);
    triangleDore=SDL_LoadBMP(IMG_TRIANGLE_DORE);
    cercleNoir=SDL_LoadBMP(IMG_CERCLE_NOIR);
    carreNoir=SDL_LoadBMP(IMG_CARRE_NOIR);
    triangleNoir=SDL_LoadBMP(IMG_TRIANGLE_NOIR);

    //Gestion des transparences
    SDL_SetColorKey(cercleGrise, SDL_SRCCOLORKEY, SDL_MapRGB(cercleGrise->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
    SDL_SetColorKey(carreGrise, SDL_SRCCOLORKEY, SDL_MapRGB(carreGrise->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
    SDL_SetColorKey(triangleGrise, SDL_SRCCOLORKEY, SDL_MapRGB(triangleGrise->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
    SDL_SetColorKey(cercleDore, SDL_SRCCOLORKEY, SDL_MapRGB(cercleDore->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
    SDL_SetColorKey(carreDore, SDL_SRCCOLORKEY, SDL_MapRGB(carreDore->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
    SDL_SetColorKey(triangleDore, SDL_SRCCOLORKEY, SDL_MapRGB(triangleDore->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
    SDL_SetColorKey(cercleNoir, SDL_SRCCOLORKEY, SDL_MapRGB(cercleNoir->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
    SDL_SetColorKey(carreNoir, SDL_SRCCOLORKEY, SDL_MapRGB(carreNoir->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));
    SDL_SetColorKey(triangleNoir, SDL_SRCCOLORKEY, SDL_MapRGB(triangleNoir->format, TRANSPARENCE_RED_RATE, TRANSPARENCE_GREEN_RATE, TRANSPARENCE_BLUE_RATE));

    int nbDeCercles=sommeDuTableau(nbDeCerclesFondMenu,0,3);
    int nbDeCarres=sommeDuTableau(nbDeCarresFondMenu,0,3);
    int nbDeTriangles=sommeDuTableau(nbDeTrianglesFondMenu,0,3);

    nbDeFormesFondMenu=nbDeCercles+nbDeCarres+nbDeTriangles;
    listeFormesFondMenu=(Forme**)malloc(nbDeFormesFondMenu*(sizeof(Forme*)));

    for (i=0;i<nbDeFormesFondMenu;i++)
    {
        listeFormesFondMenu[i]=(Forme*)malloc(sizeof(Forme));
    }
    listeCerclesFondMenu=listeFormesFondMenu;
    listeCarresFondMenu=&listeFormesFondMenu[nbDeCercles];
    listeTrianglesFondMenu=&listeFormesFondMenu[nbDeCercles+nbDeCarres];

    allouerFormes(listeCerclesFondMenu,nbDeCerclesFondMenu,CERCLE);
    allouerFormes(listeCarresFondMenu,nbDeCarresFondMenu,CARRE);
    allouerFormes(listeTrianglesFondMenu,nbDeTrianglesFondMenu,TRIANGLE);

    masqueDeFond=SDL_CreateRGBSurface(SDL_HWSURFACE,WIDTH,HEIGHT,8,0,0,0,0);
    SDL_FillRect(masqueDeFond,NULL,SDL_MapRGB(ecran->format,155,155,155));
    SDL_SetAlpha(masqueDeFond,SDL_SRCALPHA,128);
    SDL_Color couleur = COULEUR_TEXTE_MENU;
    texteNiveau[0]=TTF_RenderText_Blended(policeMenu,"EASY",couleur);
    texteNiveau[1]=TTF_RenderText_Blended(policeMenu,"MEDIUM",couleur);
    texteNiveau[2]=TTF_RenderText_Blended(policeMenu,"HARD",couleur);
    texteNiveau[3]=TTF_RenderText_Blended(policeMenu,"INSANE",couleur);
    texteMenuPpal[0]=TTF_RenderText_Blended(policeMenu,"POLYGON FURY",couleur);
    texteMenuPpal[1]=TTF_RenderText_Blended(policeMenu,"NEW GAME",couleur);
    texteMenuPpal[2]=TTF_RenderText_Blended(policeMenu,"CONTINUE",couleur);
    texteMenuPpal[3]=TTF_RenderText_Blended(policeMenu,"QUIT",couleur);
    texteMenuPpal[4]=TTF_RenderText_Blended(policeMenu,"Instructions",couleur);
    texteMenuInst[0]=TTF_RenderText_Blended(policeMenu,"Back",couleur);
    texteMenuInst[1]=TTF_RenderText_Blended(policeMenu,"Instruction",couleur);
    texteMenuInst[2]=TTF_RenderText_Blended(policeTxt,"Destroy all the polygons on each level, by starting ",couleur);
    texteMenuInst[3]=TTF_RenderText_Blended(policeTxt,"a chain reaction.",couleur);
    texteMenuInst[4]=TTF_RenderText_Blended(policeTxt,"Click on any polygon to start the reaction. Circles ",couleur);
    texteMenuInst[5]=TTF_RenderText_Blended(policeTxt,"are best.",couleur);
    texteMenuInst[6]=TTF_RenderText_Blended(policeTxt,"The more you destroy, the better your score. ",couleur);
    texteMenuInst[7]=TTF_RenderText_Blended(policeTxt,"Reach the target scores for medals.",couleur);
    texteMenuInst[8]=TTF_RenderText_Blended(policeTxt,"Circles explode and trigger other polygons",couleur);
    texteMenuInst[9]=TTF_RenderText_Blended(policeTxt,"Squares ram and trigger polygons",couleur);
    texteMenuInst[10]=TTF_RenderText_Blended(policeTxt,"Triangles fire a laser and trigger other polygons",couleur);
    titreMenuSelection=TTF_RenderText_Blended(policeMenu,"Choose a level",couleur);
    retourMenuPpal=TTF_RenderText_Blended(policeMenu,"MENU",couleur);

}

char* selectionNiveau()
{
    char* nomNiveauRetourne=NULL;

    int i;
    int continuer=1;
    SDL_Event event;//Variable d'evènements
    int tempsActuel=0;
    int tempsPrecedent=0;
    while (continuer)
    {
        int k=0;

        SDL_PollEvent(&event); //recuperation des evenements
        tempsActuel = SDL_GetTicks(); //recuperation du temps

        //On verifie que 30ms se sont ecoulees depuis le dernier rafraichissement d'ecran
        if (tempsActuel - tempsPrecedent > DUREE_MINI_ITERATION)
        {
            afficheFondMenu();

            SDL_Rect positionCourante;
            positionCourante.x=3*largeurColonne; //on se place sur la troisieme "colonne" de la fenetre
            positionCourante.y=2*hauteurLigne;

            SDL_BlitSurface(titreMenuSelection,NULL,ecran,&positionCourante);

            positionCourante.x=22*largeurColonne;
            positionCourante.y=15*hauteurLigne;
            SDL_BlitSurface(retourMenuPpal,NULL,ecran,&positionCourante);

            tempsPrecedent=tempsActuel;
            positionCourante.x=3*largeurColonne; //on se place sur la troisieme "colonne" de la fenetre
            positionCourante.y=5*hauteurLigne; //et sur la cinquieme "ligne"

            for (i=1;i<=40;i++)
            {
                SDL_BlitSurface(retournerSurfaceDuNiveau(i),NULL,ecran,&positionCourante); //on blitte la forme
                positionCourante.x+=2*largeurColonne; //on deplace le marqueur de positionCourante vers la droite
                if (positionCourante.x>21*largeurColonne) //si on a depasse la largeur autorisee
                {
                    positionCourante.x=3*largeurColonne; //on effectue un "retour a la ligne" suivante
                    positionCourante.y-=hauteurLigne;
                    SDL_BlitSurface(texteNiveau[k],NULL,ecran,&positionCourante); //Blit du texte
                    positionCourante.y+=3*hauteurLigne;
                    k++;
                }
            }

            SDL_Flip(ecran);
        }
        //On gère les évènements
        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:
            nomNiveauRetourne=selectionNiveauAuxCoordonnees(event.button.x,event.button.y);
            if (nomNiveauRetourne!=NULL)
            {
                return nomNiveauRetourne;
            }
            if (event.button.x>WIDTH-retourMenuPpal->w && event.button.y>HEIGHT-retourMenuPpal->h)
            {
                return NULL;
            }
            break;
        case SDL_QUIT:
            continuer=0;
            commandeTerminerProgramme=1;
            break;
        }
    }

    return NULL;
}

int afficheMenuPrincipal()
{
    int continuer=1;
    SDL_Event event;//Variable d'evènements
    int tempsActuel=0;
    int tempsPrecedent=0;
    SDL_Rect position;

    chargementElementsMenu();
    int interligne=(HEIGHT-texteMenuPpal[3]->h)/4;

    while (continuer)
    {
        SDL_PollEvent(&event); //recuperation des evenements
        tempsActuel = SDL_GetTicks(); //recuperation du temps
        //On verifie que 30ms se sont ecoulees depuis le dernier rafraichissement d'ecran
        if (tempsActuel - tempsPrecedent > DUREE_MINI_ITERATION)
        {
            afficheFondMenu();
            //Affichage de Quit
            position.x=WIDTH-texteMenuPpal[3]->w;

            position.y=HEIGHT-texteMenuPpal[3]->h;
            SDL_BlitSurface(texteMenuPpal[3],NULL,ecran,&position);

            //Affichage du reste
            position.x=0;
            position.y=0;
            SDL_BlitSurface(texteMenuPpal[0],NULL,ecran,&position);
            position.x=WIDTH/4;
            position.y+=interligne;
            SDL_BlitSurface(texteMenuPpal[1],NULL,ecran,&position);
	    position.y+=interligne;
	    SDL_BlitSurface(texteMenuPpal[4],NULL,ecran,&position);
            position.y+=interligne;
            SDL_BlitSurface(texteMenuPpal[2],NULL,ecran,&position);
            SDL_Flip(ecran);

            tempsPrecedent=tempsActuel;
        }

        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:

            if(event.button.x>position.x && event.button.x<position.x+texteMenuPpal[2]->w && event.button.y>position.y && event.button.y<position.y+texteMenuPpal[2]->w){
                return CONTINUE;
            }else if(event.button.x>position.x && event.button.x<position.x+texteMenuPpal[1]->w && event.button.y>(position.y-interligne*2) && event.button.y<(position.y-interligne*2)+texteMenuPpal[1]->h){
                return NEW_GAME;
            }else if(event.button.x>WIDTH-texteMenuPpal[3]->w && event.button.y>HEIGHT-texteMenuPpal[3]->h){
                return QUIT;
            }else if(event.button.x>position.x && event.button.x<position.x+texteMenuPpal[4]->w && event.button.y>=(position.y-interligne) && event.button.y<=(position.y-interligne+texteMenuPpal[4]->h))
	      {

	      	      return INSTRUCTION;
	      }

        break;

        case SDL_QUIT:
            continuer=0;
            commandeTerminerProgramme=1;
            break;
        }

    }
    return 0;
}

char* selectionNiveauAuxCoordonnees(int x,int y)
{
    int numeroLigne=y/hauteurLigne;
    int numeroColonne=x/largeurColonne;
    int indicePrefixe;
    char *prefixeNomNiveau=(char*)malloc(sizeof(char)*10);

    switch (numeroLigne) //on verifie qu'on se trouve sur une des lignes autorisees
    {
    case 5:
        strcpy(prefixeNomNiveau,"easy:");
        indicePrefixe=0;
        break;
    case 7:
        strcpy(prefixeNomNiveau,"medium:");
        indicePrefixe=1;
        break;
    case 9:
        strcpy(prefixeNomNiveau,"hard:");
        indicePrefixe=2;
        break;
    case 11:
        strcpy(prefixeNomNiveau,"insane:");
        indicePrefixe=3;
        break;
    default:
        return NULL;
    }

    int codeNiveau=((numeroColonne-3)/2)+1; //Calcul du numero de niveau

    if (codeNiveau<=0 || codeNiveau>10 || codeNiveau+indicePrefixe*10>progression+1)
    {
        return NULL; //interdiction de selectionner ce niveau
    }
    else   //si le numero est valide
    {
        char suffixeNomNiveau[2]="";
        sprintf(suffixeNomNiveau,"%d",codeNiveau);
        char *retourNomNiveau=(char*)malloc(sizeof(char)*10);
        strcpy(retourNomNiveau,strcat(prefixeNomNiveau,suffixeNomNiveau));
        return retourNomNiveau; //on retourne le nom du niveau correspondant
    }
}

void afficheFondMenu()
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

    deplacerMultipleFormes(listeFormesFondMenu,nbDeFormesFondMenu);
    afficherMultipleFormes(listeFormesFondMenu,ecran,nbDeFormesFondMenu);

    SDL_Rect positionFond;
    positionFond.x=0;
    positionFond.y=0;
    SDL_BlitSurface(masqueDeFond,NULL,ecran,&positionFond);
}

int afficheInstructions(){
   chargementElementsMenu();
    int interligne=(HEIGHT)/16;
    int continuer;
    SDL_Event event;
    SDL_Rect position;
    int tempsActuel=0;
    int tempsPrecedent=0;
    int i;
    while (continuer)
    {
        SDL_PollEvent(&event); //recuperation des evenements
        tempsActuel = SDL_GetTicks(); //recuperation du temps
        //On verifie que 30ms se sont ecoulees depuis le dernier rafraichissement d'ecran
        if (tempsActuel - tempsPrecedent > DUREE_MINI_ITERATION)
        {
            afficheFondMenu();
            //Affichage de Back
	    position.x=WIDTH-texteMenuInst[0]->w;
	    position.y=0;
            SDL_BlitSurface(texteMenuInst[0],NULL,ecran,&position);
	    //Affichage de Instruction
	    position.x=0;
	    position.y=0;
	    SDL_BlitSurface(texteMenuInst[1],NULL,ecran,&position);
	    position.y+=interligne*3;
	    //Affichage du texte
	    for(i=2;i<=10;i++){
	      SDL_BlitSurface(texteMenuInst[i],NULL,ecran,&position);
	      position.y+=interligne;
	    }
	    SDL_Flip(ecran);
	    tempsPrecedent=tempsActuel;

	}
	switch(event.type)
	{
	case SDL_MOUSEBUTTONUP:
	  if(event.button.x>WIDTH-texteMenuInst[0]->w && event.button.y<texteMenuInst[0]->h){
	    return MENU_PRINCIPAL;
          }
	  break;
	case SDL_QUIT:
            continuer=0;
            commandeTerminerProgramme=1;
            break;
       }
    }
  return MENU_PRINCIPAL;
}

void afficherTexteStyleMenu(char *texte,int positionX, int positionY)
{
    SDL_Color couleur=COULEUR_TEXTE_MENU;
    SDL_Rect position;
    SDL_Surface *surfaceTexte;

    position.x=positionX;
    position.y=positionY;
    surfaceTexte=TTF_RenderText_Blended(policeMenu,texte,couleur);
    SDL_BlitSurface(surfaceTexte,NULL,ecran,&position);
}
