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
void printTerrainTest(caseTerrain* t, int taille, int largeur)
/*Fonction qui affiche un terrain (pour les tests)*/
{
    if ( taille%largeur==0)
        printf("\n");
    
    if ( taille> 0)
    {
        printf("%d-%d(%d:%d) ", t->etat, t->contenu, t->posX, t->posY);
        printTerrainTest(t + 1, taille - 1, largeur);
    }
    else
        printf("\n");
}

void printTerrainJeux(caseTerrain* t, int hauteur, int largeur)
/*Fonction qui affiche un terrain pour la partie*/
{
    int cptLargeur;
    int cptHauteur;
    for(cptHauteur=0;cptHauteur<=hauteur+1; cptHauteur++){
        if(cptHauteur==0){
            printf("   |");
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                printf(" %c |",cptLargeur+65);
            }
        }
        else if(cptHauteur==1){
            printf("----");
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                printf("----");
            }
        }
        else{
            printf(" %d |", cptHauteur-1);
            for(cptLargeur=0;cptLargeur<largeur; cptLargeur++){
                printf(" %d |",(t+(cptHauteur*hauteur+cptLargeur))->etat);
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
void createTerrain(caseTerrain* terrain, int hauteur, int largeur, int nbBombe){
    int i, j;
    int cptBombe =0;
    int taille = hauteur*largeur;
    int* tab = (int*)malloc(sizeof(int)*taille);
    
    initTabBombe(tab,taille, nbBombe);//initialisation d'un tableau avec le bon nombre de bombe
    printTab(tab, taille);//affichage pour les tests
    melangeTabBombe(tab,taille);//on melange le tableau de bombe aléatoirement
    printTab(tab, taille);//affichage pour les tests
    
    /*On prend les elements du tableau de bombe melange pour remplir le terrain*/
    for(i=0;i<hauteur;i++){
        for(j=0;j<largeur;j++){
            (terrain+cptBombe)->posX=i;
            (terrain+cptBombe)->posY=j;
            (terrain+cptBombe)->etat=C_FERMEE;
            (terrain+cptBombe)->contenu= *(tab+cptBombe);
            cptBombe++;
        }
    }
    
    printf("Terrain crée\n");//message pour les tests
    printTerrainTest(terrain,hauteur*largeur,largeur);
}

int sauvegardeTerrainEncours(caseTerrain* terrain,int hauteur, int largeur){
    FILE* f = fopen(FICH_TAB_ENCOURS, "w");
    if (f == NULL)
        return 1;
    fwrite(terrain, 1, sizeof(caseTerrain)*hauteur*largeur, f);
    fclose(f);
    printf("Terrain sauvegardé\n");
    return 0;
    
}

int afficheTerrainPrecedentTest(int hauteur, int largeur){
    int i, j, n = 0;
    
    FILE* f = fopen(FICH_TAB_PRECEDENT, "r");
    if (f == NULL){
        printf("impossible d'ouvrir le terrain");
        return 1;
    }
    printf("Affichage terrain : \n");
    caseTerrain* terrain = (caseTerrain*)malloc(sizeof(caseTerrain)*hauteur*largeur);
    while(fread(terrain + n, 1, sizeof(caseTerrain), f)){
        
        //printf("%d-%d ", terrain[n].etat, terrain[n].contenu);
        n++;
    }
    printTerrainTest(terrain, largeur*hauteur , largeur);
    fclose(f);
    return 0;
    
}

int afficheTerrainEncoursTest(int hauteur, int largeur){
    int i, j, n = 0;
    
    FILE* f = fopen(FICH_TAB_ENCOURS, "r");
    if (f == NULL){
        printf("impossible d'ouvrir le terrain");
        return 1;
    }
    printf("Affichage terrain : \n");
    caseTerrain* terrain = (caseTerrain*)malloc(sizeof(caseTerrain)*hauteur*largeur);
    while(fread(terrain + n, 1, sizeof(caseTerrain), f)){
        
        //printf("%d-%d ", terrain[n].etat, terrain[n].contenu);
        n++;
    }
    printTerrainTest(terrain, largeur*hauteur , largeur);
    printTerrainJeux(terrain, hauteur , largeur);
    fclose(f);
    return 0;
    
}
