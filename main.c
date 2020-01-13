#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//Constantes
#define MAXlc 11
#define MAXP 50


//Prototypes
void JEU();

//Prototypes d'initialisation et d'affichage
void initialisationTab(int nMatriceEntier[MAXlc][MAXlc]);
void affichageTab(int nMatriceEntier[MAXlc][MAXlc]);
void Color(int couleurDuTexte,int couleurDeFond);

//Prototypes de début de jeu
void choixPseudo(char c_pseudoj1[MAXP],char c_pseudoj2[MAXP]);
void placementFlotte(int nMatriceEntier[MAXlc][MAXlc]);
int verifB(int taille, int n_x, int n_y, int n_pos, int nMatriceEntier[MAXlc][MAXlc]);
void placementBato (int taille, int n_x, int n_y, int n_pos, int nMatriceEntier[MAXlc][MAXlc]);

//Prototypes de tour
void tirJoueur(int nMatriceEntierTir[MAXlc][MAXlc], int nMatriceEntierAdversaire[MAXlc][MAXlc], int score_J);
void verifBdetruit(int nMatriceEntierAdversaire[MAXlc][MAXlc], int veriftaille, int n_scoreJ, int n_x, int n_y);

//Prototypes score
void scoreEnregistrement (char c_pseudoj1[MAXP],char c_pseudoj2[MAXP],int n_scoreJ1, int n_scoreJ2);
void scoreAffichage();



//Programme principal avec menu
int main()
{
  int accueil;

  printf("\t\t=== Accueil ===\n");
  printf("\t\t===============\n\n");
  printf("\t1. Jouer une partie a deux joueurs\n");
  printf("\t2. Score\n");
  printf("\t3. Quitter\n\n");
  scanf("%d", &accueil);
  printf("\n");

  switch (accueil)
  {
    case 1: // Permet de lancer le jeu
       printf("Vous avez choisi de jouer a deux joueurs ! Que le meilleur gagne !!\n\n");
       JEU();
       break;
    case 2: // Permet d'afficher le score
       printf("Vous avez choisi l'affichage des scores.\n\n");
	   scoreAffichage();
       break;

    case 3: // affiche au revoir si le joueur quitte le jeu
        exit(0);
       break;
  }
  printf("\n\n");
  return 0;
}


//Programme contenant le jeu
void JEU()
{

	int grillej1[MAXlc][MAXlc],grillej2[MAXlc][MAXlc];
	int grilleTirj1[MAXlc][MAXlc],grilleTirj2[MAXlc][MAXlc];
	char c_pseudoj1[MAXP],c_pseudoj2[MAXP];
	int partie = 1;
	int jTour =1;
	int score_J1=0;
	int score_J2=0;

	initialisationTab(grillej1);
	initialisationTab(grillej2);
	initialisationTab(grilleTirj1);
	initialisationTab(grilleTirj2);

	choixPseudo(c_pseudoj1,c_pseudoj2);

	system("cls"); //Permet de clear la console

	printf("%s placez vos bateaux\n",c_pseudoj1);
	printf("Entrer pour continuer\n");
	getchar();

	placementFlotte(grillej1);

	system("cls"); 

	printf("%s à vous de placer vos bateaux\n",c_pseudoj2 );
	printf("Entrer pour continuer\n");
	getchar();

	placementFlotte(grillej2);

	while (partie==1) //Tant que la partie vaut 1 le jeu continue. La partie passe à 0 lorsqu'un joueur obtient 5 à son score
	{
		if (jTour==1)
		{
			system("cls");
		  	printf("%s\n", c_pseudoj1);
		  	printf("Grille de tirs :\n");
		  	affichageTab(grilleTirj1);
		  	printf("\n");
		  	printf("Grille de bateaux :\n");
		  	printf("\n");
		  	affichageTab(grillej1);
		  	printf("\n");
			tirJoueur(grilleTirj1,grillej2,score_J1);
			system("cls");
			affichageTab(grilleTirj1);
			printf("\n");
			printf("1 : pas touche\n");
			printf("2 : touche\n");
			printf("score : %d\n",score_J1 );
			fflush(stdin);
			getchar();
			jTour=2;
			if (score_J1==5)
			{
				partie = 0;
			}
		}
		else
		{
			system("cls");
		  	printf("%s\n", c_pseudoj2);
		  	printf("Grille de tirs :\n");
		  	affichageTab(grilleTirj1);
		  	printf("\n");
		  	printf("Grille de bateaux :\n");
		  	printf("\n");
		  	affichageTab(grillej2);
		  	printf("\n");
			tirJoueur(grilleTirj2,grillej1,score_J2);
			system("cls");
			affichageTab(grilleTirj2);
			printf("1 : pas toucheo\n");
			printf("2 : toucheo\n");
			printf("score : %d\n",score_J2 );
			printf("\n");
			fflush(stdin);
			getchar();
			jTour=1;
			if (score_J2==5)
			{
				partie = 0;
			}
		}

	}

	scoreEnregistrement(c_pseudoj1,c_pseudoj2,score_J1,score_J2);

}



//Initialise du tableau
void initialisationTab(int nMatriceEntier[MAXlc][MAXlc])
{
	for(int i=0; i<MAXlc; i++)
	{
        for(int j=0; j<MAXlc; j++)
        {

			nMatriceEntier [i] [j] = 0; //initialisation du tableau a nValinit
        }
    }
}

//Affiche du tableau
void affichageTab(int nMatriceEntier[MAXlc][MAXlc])
{
	int lc=0;
  for (int i = 0; i < MAXlc; i++)
  {
    for (int j = 0; j < MAXlc; j++)
    {
      if ((i==0)||(j==0))
      {
      	lc=i+j;
      	Color(0,15);
        printf("| %d  ", lc);
        Color(15,0);
      }
      else
      {
      	if (nMatriceEntier[i][j]!=0)
      	{
      		Color(12,0);
      		printf("| %d  ",nMatriceEntier[i][j]);
      		Color(15,0);
      	}
      	else
      		printf("| %d  ",nMatriceEntier[i][j]);
      }

    }
    printf("\n");
    printf("\n");
  }
}

//Choix des pseudo pour les joueurs
void choixPseudo(char c_pseudoj1[MAXP],char c_pseudoj2[MAXP])
{
	printf("Veuillez entrer le pseudo du joueur 1\n");
	scanf("%s",c_pseudoj1);
	printf("Veuillez entrer le pseudo du joueur 2\n");
	scanf("%s",c_pseudoj2);
}

//Placement de la flotte de bateaux
void placementFlotte(int nMatriceEntier[MAXlc][MAXlc])
{
	int nb_bato = 1;
	int taille =0;
	int n_x,n_y;
	int n_pos;
	while (nb_bato<6)
	{

			affichageTab(nMatriceEntier);
			printf("Veuillez placer le bateau numéro : %d\n",nb_bato);
			switch  (nb_bato)
			{
				case 1 :
				taille=2;
				break;
				case 2 :
				taille=2;
				break;
				case 3 :
				taille=3;
				break;
				case 4 :
				taille=4;
				break;
				case 5 :
				taille=5;
				break;
				default :
				taille=0;
			}
			printf("Vous allez placer le bateau de taille %d \n",taille);
			do
			{
				printf("Veuillez entrer les coordonnees ligne puis colonne\n");
				scanf("%d %d",&n_x,&n_y);
				printf("Entrez 1 si vous voulez que le bateau soit vertical ou 2 pour qu'il soit horizontal\n");
				scanf("%d",&n_pos);
			}while(!verifB(taille,n_x,n_y,n_pos,nMatriceEntier));

			placementBato (taille,n_x,n_y,n_pos,nMatriceEntier);
			nb_bato++;
	}
	printf("Voici le placement de vos bateaux\n");
    affichageTab(nMatriceEntier);
    printf("\n");
    printf("Appuyez sur entree pour continuer\n");
    fflush(stdin);
    getchar();
    fflush(stdin);

}

//Placement des bateaux individuellements
void placementBato (int taille, int n_x, int n_y, int n_pos, int nMatriceEntier[MAXlc][MAXlc])
{

	for (int i = 0; i < taille; i++)
	{
		if (n_pos==2)
		{
			nMatriceEntier[n_x][n_y+i] = taille;
		}
		else
		{
			nMatriceEntier[n_x+i][n_y] = taille;
		}
	}
}

//Verification du placement pour les bateaux
int verifB(int taille, int n_x, int n_y, int n_pos, int nMatriceEntier[MAXlc][MAXlc])
{
	if (n_pos==1)
	{
		for (int i = 0; i < taille; i++)
		{
			if (nMatriceEntier[n_x+i][n_y] != 0)
			{
				return 0;
			}
			if (n_x <= MAXlc - taille)
			{
				return 1;
			}
			else
				return 0;
		}
	}
	else
	{
		for (int i = 0; i < taille; i++)
		{
			if (nMatriceEntier[n_x][n_y+i] != 0)
			{
				return 0;
			}
			if (n_y <= MAXlc - taille)
			{
				return 1;
			}
			else
				return 0;
		}
	}
}

//Gère le tir d'un joueur, vérifie si un bateau est touche ou non
void tirJoueur(int nMatriceEntierTir[MAXlc][MAXlc], int nMatriceEntierAdversaire[MAXlc][MAXlc], int score_J)
{
	int n_x,n_y;
	int veriftaille;
	int score_temp=score_J;
	printf("Veuillez entrer les coordonnees ligne puis colonne du tir\n");
	scanf("%d %d",&n_x,&n_y);

	if (nMatriceEntierAdversaire[n_x][n_y] ==0)
	{
		nMatriceEntierTir[n_x][n_y] = 1;
		printf("Vous n'avez rien touche\n");
	}
	else
	{
		nMatriceEntierTir[n_x][n_y] = 2;
		veriftaille=nMatriceEntierAdversaire[n_x][n_y];
		printf("Vous avez touche un bateau\n");
		verifBdetruit(nMatriceEntierAdversaire,veriftaille,score_J, n_x,n_y);
		if (score_J!=score_temp)
		{
			printf("Vous avez coule un bateau de taille %d\n",veriftaille);
		}

	}

}

//Vérifie si un bateau a été touché suffisament pour couler
void verifBdetruit(int nMatriceEntierAdversaire[MAXlc][MAXlc], int veriftaille, int n_scoreJ, int n_x, int n_y)
{
	int n_compte=0;
	switch (veriftaille)
	{
		case 2:
		if ((nMatriceEntierAdversaire[n_x-1][n_y]==veriftaille)||(nMatriceEntierAdversaire[n_x][n_y-1]==veriftaille)||(nMatriceEntierAdversaire[n_x+1][n_y]==veriftaille)||(nMatriceEntierAdversaire[n_x][n_y+2]==veriftaille))
			n_scoreJ=n_scoreJ+1;
		break;
		default:
		for (int i = 1; i < MAXlc; i++)
		{
			for (int j = 1; j < MAXlc; j++)
			{
				if (nMatriceEntierAdversaire[MAXlc][MAXlc]==veriftaille)
				{
					n_compte=n_compte+1;
				}
			}
		}
		if (n_compte==veriftaille)
		{
			n_scoreJ=n_scoreJ+1;
		}
	}

}

//Permet de chager la couleur lors de l'affichage
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

//Enregistrer les scores dans un fichier binaire
void scoreEnregistrement (char c_pseudoj1[MAXP],char c_pseudoj2[MAXP],int n_scoreJ1, int n_scoreJ2)
{
	FILE* ScoreFile;
    if ((ScoreFile = fopen("Score.bin","ab"))==NULL)
    printf("ERREUR OUVERTURE\n");
    else
    {
    	fwrite(c_pseudoj1,sizeof(char)*MAXP,1,ScoreFile);
    	fwrite(n_scoreJ1,sizeof(int),1,ScoreFile);
    	fwrite(c_pseudoj2,sizeof(char)*MAXP,1,ScoreFile);
    	fwrite(n_scoreJ2,sizeof(int),1,ScoreFile);
    }

    fclose(ScoreFile);
}

//Permet d'afficher les scores depuis un fichier binaire
void scoreAffichage()
{
	FILE* ScoreFile;

    if ((ScoreFile = fopen("Score.bin","rb"))==NULL)
    printf("ERREUR OUVERTURE\n");
    else
    {
    	while(!feof(ScoreFile))
    		putchar(fgetc(ScoreFile));
    }
    fclose (ScoreFile);
}
