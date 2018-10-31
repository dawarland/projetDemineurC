//
//  Demineur.h
//  
//
//
//


/* Code pour éviter les erreurs quand on inclue deux fois le fichier */
#ifndef H_DEMINEUR
#define H_DEMINEUR

#define C_VIDE 0
#define C_BOMBE 1

#define C_FLAG 2
#define C_OUVERTE 1
#define C_FERMEE 0

#define FICH_TAB_ENCOURS "terrain.txt"
#define FICH_TAB_PRECEDENT "terrain_precedent.txt"

#define QUART_HAUT_GAUCHE 0
#define QUART_BAS_GAUCHE 1
#define QUART_BAS_DROITE 2
#define QUART_HAUT_DROITE 3
#define DEMI_HAUT 4
#define DEMI_DROITE 5
#define DEMI_BAS 6
#define DEMI_GAUCHE 7
#define TOTAL 8

#define CLEAR_BUFFER while((clearbuffer = getchar()) != '\n' && clearbuffer != EOF )

char clearbuffer;
int* hauteurTerrain ;//= (int)malloc(sizeof(int)));
int* largeurTerrain ;//= (int)malloc(sizeof(int)));

typedef struct caseTerrain
{
    int posX;
    int posY;
    int etat;
    int contenu;
}caseTerrain;

//fonction pour caseTerrain
void ouvertureCase(caseTerrain* terrain, int pX, int pY);
void flagCase(caseTerrain* terrain, int pX, int pY);
int verifCaseMode(int mode, caseTerrain* terrain, int pX, int pY);
int nbBombeAdjacente(caseTerrain* terrain, int pX, int pY);
int caseValide(int pX, int pY);

//fonction pour Terrain
void initTabBombe(int* t, int n, int nbbombe);
void printTab(int* t, int n);
void printTerrainTest(caseTerrain* t, int taille);
void printTerrainJeux(caseTerrain* t);
void melangeTabBombe(int* t, int n);
void createTerrain(caseTerrain* terrain, int nbBombe);
int sauvegardeTerrain(caseTerrain* terrain);
int afficheTerrainTest(char* fichTab);
caseTerrain* getTerrain(int taille, char* fichTab);
caseTerrain* ouverture(int cx, int cy);
caseTerrain* mettreflague(int cx, int cy);

//fonction pour Partie
void affichageMenu(void);
int menu(void);
int action(void);
void nouvellePartie(void);
void continuerPartie(void);
int tour(void);
void play(void);
#endif /* fin du bloc délimité par H_DEMINEUR */
