//
//  Demineur.h
//
//  Nous avons decide de regouper toutes les fonctions dans un seul header
//


/* Code pour éviter les erreurs quand on inclue deux fois le fichier */
#ifndef H_DEMINEUR
#define H_DEMINEUR

#define C_VIDE 0
#define C_BOMBE 9

#define C_FLAG 2
#define C_OUVERTE 1
#define C_FERMEE 0

#define FICH_HAU_LAR ".haular.txt"
#define FICH_TAB_ENCOURS "terrain.txt"
#define FICH_TAB_PRECEDENT "terrain_precedent.txt"

#define CLEAR_BUFFER while((clearbuffer = getchar()) != '\n' && clearbuffer != EOF )

char clearbuffer;
int* hauteurTerrain ;//* création de variable global pour pouvoir continuer une partie *//
int* largeurTerrain ;//*                                                               *//

typedef struct caseTerrain //création de la structure dans le header pour quel soit accesible directement par tous
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
void ouvertureCaseVoisine(caseTerrain* terrain, int pX, int pY);
int caseValide(int pX, int pY);
void ajoutNBombe(caseTerrain* terrain, int pX, int pY);
void plus1CasesVoisines(caseTerrain* terrain, int pX, int pY);

//fonction pour Terrain
void initTabBombe(int* t, int n, int nbbombe);
void printTab(int* t, int n);
void printTerrainTest(caseTerrain* t, int taille);
int printTerrainJeux(caseTerrain* t);
void melangeTabBombe(int* t, int n);
void createTerrain(caseTerrain* terrain, int nbBombe);
int sauvegardeTerrain(caseTerrain* terrain, char* fichTab);
int afficheTerrainJeux(char* fichTab);
void initNbBombe(caseTerrain* terrain);
caseTerrain* getTerrain(int taille, char* fichTab);
caseTerrain* ouverture(int cx, int cy);
caseTerrain* mettreflague(int cx, int cy);
int sauvegardeHL();
int getHL();
void transferTerrain(char* fichACopier, char* fichDestination);
void printTerrainPerdu(caseTerrain* t);
int afficheTerrainPerdu(char* fichTab);
int toutOuvert();
int toutFlag();

//fonction pour Partie
void affichageMenu(void);
int menu(void);
int action(void);
void nouvellePartie(void);
void continuerPartie(void);
int tour(void);
void play(void);
int gagne();

#endif /* fin du bloc délimité par H_DEMINEUR */
