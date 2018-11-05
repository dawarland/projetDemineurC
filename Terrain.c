//
//  Terrain.c
//  
//
//
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "Demineur.h"

void initTabBombe(int* t, int n, int nbbombe)
/*Fonction qui va crée un tableau d'entier en placant le bon nombre de bombe dans un tableau d'entier*/
{
    if (n > 0)
    {
        if(nbbombe>0){
            *t = C_BOMBE;
            initTabBombe(t + 1, n - 1, nbbombe - 1);
        }
        else{
            *t = C_VIDE;
            initTabBombe(t + 1, n - 1, nbbombe);
        }
    }
}

void printTab(int* t, int n)
/*Fonction qui affiche un tableau (pour les tests)*/
{
    if (n > 0)
    {
        printf("%d ", *t);
        printTab(t + 1, n - 1);
    }
    else
        printf("\n");
}
void printTerrainTest(caseTerrain* t, int taille)
/*Fonction qui affiche un terrain (pour les tests)*/
{
    int largeur = *largeurTerrain;
    if ( taille%largeur==0)
        printf("\n");
    
    if ( taille> 0)
    {
        printf("%d-%d(%d:%d) ", t->etat, t->contenu, t->posX, t->posY);
        printTerrainTest(t + 1, taille - 1);
    }
    else
        printf("\n");
}


void initNbBombe(caseTerrain* terrain)
/*fonction qui test chaque case du terrain pour incrementer la valeur des bombe voisine*/
{
    int hauteur = *hauteurTerrain;
    int largeur = *largeurTerrain;
    
    int i, j;
    
    for(i=0;i<hauteur;i++){
        for(j=0;j<largeur;j++){
            ajoutNBombe(terrain, j, i);//ici on ajoute 1 au case voisine si la case i,j est une bombe
        }
    }
}


int printTerrainJeux(caseTerrain* t)
/*Fonction qui affiche un terrain pour la partie et qui renvoie 1 si un bombe est ouvert*/
{
    int bouverte = 0;
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    int cptLargeur;
    int cptHauteur;
    for(cptHauteur=-2;cptHauteur<hauteur; cptHauteur++){
        if(cptHauteur==-2){
            printf("   |");
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                printf(" %c |",cptLargeur+65);
            }
        }
        else if(cptHauteur==-1){
            printf("----");
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                printf("----");
            }
        }
        else{
            printf(" %d |", cptHauteur);
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                if( (t+(cptLargeur+cptHauteur*largeur))->etat == C_OUVERTE){
                    if( (t+(cptLargeur+cptHauteur*largeur))->contenu == C_BOMBE){
                        printf(" B |"); //on affiche un B si la bombe est ouverte
                        bouverte=1; // on incremente 1 pour retourner la condition de fin de parti
                    }
                    else
                        printf(" %d |",(t+(cptLargeur+cptHauteur*largeur))->contenu);
                }
                else if( (t+(cptLargeur+cptHauteur*largeur))->etat == C_FLAG )
                    printf(" F |"); //on affiche un F si il y a un flag
                else
                    printf(" # |");
            }
        }
        printf("\n");
    }
    
    return bouverte;
}

void printTerrainPerdu(caseTerrain* t)
/*Fonction qui affiche un terrain a la fin*/
{
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    int cptLargeur;
    int cptHauteur;
    for(cptHauteur=-2;cptHauteur<hauteur; cptHauteur++){
        if(cptHauteur==-2){
            printf("   |");
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                printf(" %c |",cptLargeur+65);
            }
        }
        else if(cptHauteur==-1){
            printf("----");
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                printf("----");
            }
        }
        else{
            printf(" %d |", cptHauteur);
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                if( (t+(cptLargeur+cptHauteur*largeur))->contenu == C_BOMBE){
                    if( (t+(cptLargeur+cptHauteur*largeur))->etat == C_FLAG )
                        printf("FBF|"); //si on avait trouve une bombe
                    else
                        printf(" B |");
                }
                else if ( (t+(cptLargeur+cptHauteur*largeur))->etat == C_FLAG )
                    printf(" F |");
                else
                    printf(" %d |",(t+(cptLargeur+cptHauteur*largeur))->contenu);
            }
        }
        printf("\n");
    }
}

void melangeTabBombe(int* t, int n)
/*fonction qui melange le tableau de bombe*/
{
    int i, j;
    int temp;
    if( n == 1 )
        return;
    
    for( i=0; i< n-1; i++)
    {
        j = i + rand() % (n-i);
        temp = *(t+i);
        *(t+i) = *(t+j);
        *(t+j) = temp;
    }
}
void createTerrain(caseTerrain* terrain, int nbBombe)
/*Fonctionqui va creer un terrain en y mettant le bon nombre de bombe */
{
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    int i, j;
    int cptCase =0;
    int taille = hauteur*largeur;
    int* tab = (int*)malloc(sizeof(int)*taille);
    
    initTabBombe(tab,taille, nbBombe);//initialisation d'un tableau avec le bon nombre de bombe
    //printTab(tab, taille);//affichage pour les tests
    melangeTabBombe(tab,taille);//on melange le tableau de bombe aléatoirement
    //printTab(tab, taille);//affichage pour les tests
    
    /*On prend les elements du tableau de bombe melange pour remplir le terrain*/
    for(i=0;i<hauteur;i++){
        for(j=0;j<largeur;j++){
            (terrain+cptCase)->posX=j;
            (terrain+cptCase)->posY=i;
            (terrain+cptCase)->etat=C_FERMEE;
            (terrain+cptCase)->contenu= *(tab+cptCase);
            cptCase++;
        }
    }
    
    initNbBombe(terrain);//On incremente le contenu des case voisines d'une bombe
    
    //printf("Terrain crée\n");//message pour les tests
    printTerrainTest(terrain,hauteur*largeur);
}

int sauvegardeHL()
/*Fonction qui sauvegarde les dimensions du terrain*/
{
    FILE* f = fopen(FICH_HAU_LAR, "w+");
    if (f == NULL)
        return 1;
    
    fprintf(f, "%d %d", (*hauteurTerrain), (*largeurTerrain));
    
    fclose(f);
    printf("Hauteur Largeur Sauvegardes\n");
    return 0;
}

int getHL()
/*Fonction qui recupere les dimensions du terrain*/
{
    int hl[3] = {0};
    
    FILE* f = fopen(FICH_HAU_LAR, "r");
    if (f == NULL)
        return 1;

    fscanf(f, "%d %d", &hl[0], &hl[1]);
    printf("hauteur = %d, largeur = %d \n", hl[0], hl[1]);
    
    hauteurTerrain = &hl[0];
    largeurTerrain = &hl[1];
    
    fclose(f);
    return 0;
    
}

int sauvegardeTerrain(caseTerrain* terrain, char* fichTab)
/*Fonction qui va ecrire dans un fichier le terrain*/
{
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    FILE* f = fopen(fichTab, "w+");
    if (f == NULL)
        return 1;
    fwrite(terrain, 1, sizeof(caseTerrain)*hauteur*largeur, f);
    fclose(f);
    printf("Terrain sauvegardé\n");
    return 0;
    
}

caseTerrain* getTerrain(int taille, char* fichTab)
/*Fonction qui recupere un terrain depuis un fichier */
{
    int i, j, n = 0;
    
    FILE* f = fopen(fichTab, "r");
    if (f == NULL){
        printf("impossible d'ouvrir le terrain");
        return NULL;
    }
    caseTerrain* terrain = (caseTerrain*)malloc(sizeof(caseTerrain)*taille);
    while(fread(terrain + n, 1, sizeof(caseTerrain), f)){
        n++;
    }
    fclose(f);
    return terrain;
}

void transferTerrain(char* fichACopier, char* fichDestination)
/*permet de mettre le contenu d'un fichier terrain dans un autre*/
{
    sauvegardeTerrain( getTerrain( (*hauteurTerrain)*(*largeurTerrain) , fichACopier) , fichDestination);
}

int afficheTerrainJeux(char* fichTab)
/* Fonction qui affiche un terrain depuis un fichier contenant un terrain
 * Cette fonction retourne 1 si la partie est fini
 * le test est fait a l'affichage pour ne pas parcourir une 2eme fois le tableau
 */
{
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    
    caseTerrain* terrain = getTerrain(largeur*hauteur,fichTab);
    if(terrain==NULL)
        return 2;
    
    return printTerrainJeux(terrain); // on retourne 1 si une bombe est ouverte directement dans l'affichage
    
}

int afficheTerrainPerdu(char* fichTab)// petit plus, pour montrer ou se trouvait les bombes
{
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    
    caseTerrain* terrain = getTerrain(largeur*hauteur,fichTab);
    if(terrain==NULL)
        return 1;
    
    printTerrainPerdu(terrain);
    return 0;
}

caseTerrain* ouverture(int cx, int cy)
/* Fonction qui gere l'ouverture d'une case su tableau */
{
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    caseTerrain* nouveauT = getTerrain(largeur*hauteur,FICH_TAB_ENCOURS);
    ouvertureCase(nouveauT, cx-65, cy);
    
    return nouveauT;
    
}

caseTerrain* mettreflague (int cx, int cy)
/* Fonction qui gere le "flagage" d'une case su tableau */
{
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    caseTerrain* nouveauT = getTerrain(largeur*hauteur,FICH_TAB_ENCOURS);
    flagCase(nouveauT, cx-65, cy);
    
    return nouveauT;
    
}

int toutOuvert()
/* Fonction qui retourne 1 si toutes les cases non bombe sont ouverte */
{
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    int cpt;
    caseTerrain* t = getTerrain(largeur*hauteur,FICH_TAB_ENCOURS);
    
    for(cpt=0; cpt<hauteur*largeur; cpt++){
        if ((t+cpt)->contenu != C_BOMBE && (t+cpt)->etat == C_FERMEE )
            return 0;
    }
    
    return 1;
}

int toutFlag()
/*fonction qui retourne 1 si toutes les cases bombe sont flaggess */ {
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    int cpt;
    caseTerrain* t = getTerrain(largeur*hauteur,FICH_TAB_ENCOURS);
    
    for(cpt=0; cpt<hauteur*largeur; cpt++){
        if ((t+cpt)->contenu == C_BOMBE && (t+cpt)->etat != C_FLAG )
            return 0;
    }
    
    return 1;
}
