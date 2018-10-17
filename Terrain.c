//
//  Terrain.c
//  
//
//  Created by Williams ARLAND on 17/10/2018.
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "Terrain.h"
#include "CaseTerrain.h"

#define FICH_TAB_ENCOURS "terrain.txt"
#define FICH_TAB_PRECEDENT "terrain_precedent.txt"

typedef struct caseTerrain
{
    int posX;
    int posY;
    int etat;
    int  contenu;
}caseTerrain;

void initTabBombe(int* t, int n, int nbbombe)
{
    if (n > 0)
    {
        if(nbbombe>1){
            *t =1;
            initTabBombe(t + 1, n - 1, nbbombe - 1);
        }
        else
            *t = 0;
        initTabBombe(t + 1, n - 1, nbbombe);
    }
}

void melangeTabBombe(int* t, int n)
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
void CreateTerrain(caseTerrain* terrain, int hauteur, int largeur, int nbBombe){
    int i, j;
    int cptBombe =0;
    int taille = hauteur*largeur;
    int* tab = (int*)malloc(sizeof(int)*taille);
    
    initTabBombe(tab,taille, nbBombe);
    melangeTabBombe(tab,taille);
    
    for(i=0;i<largeur;i++){
        for(j=0;j<hauteur;j++){
            terrain[i+j].posX=i;
            terrain[i+j].posY=j;
            terrain[i+j].etat=0;
            terrain[i+j].contenu= *(tab+cptBombe);
            cptBombe++;
        }
    }
    printf("Terrain crée\n");
}

int SauvegardeTerrainEncours(caseTerrain* terrain,int hauteur, int largeur){
    FILE* f = fopen(FICH_TAB_ENCOURS, "w");
    if (f == NULL)
        return 1;
    fwrite(terrain, hauteur*largeur , sizeof(struct caseTerrain), f);
    fclose(f);
    printf("Terrain sauvegardé\n");
    return 0;
    
}

int AfficheTerrainEncours(int hauteur, int largeur){
    FILE* f = fopen(FICH_TAB_ENCOURS, "w");
    int i, j, n = 0;
    
    f = fopen("terrain.txt", "r");
    if (f == NULL){
        printf("impossible d'ouvrir le terrain");
        return 1;
    }
    printf("Affichage terraine : \n");
    caseTerrain terrain[hauteur*largeur];
    while(fread(terrain + n, 0, sizeof(caseTerrain), f)){
        
        printf("%d-%c ", terrain[i+j].etat, terrain[i+j].contenu);
        n++;
        if(n%largeur==0)
            printf("\n");
    }
    fclose(f);
    return 0;
    
}

int main(){
    int hauteur, largeur, nbBombe;
    printf("Veuillez saisir la hauteur du tableau : ");
    scanf("%d", &hauteur);
    printf("Veuillez saisir la largeur du tableau : ");
    scanf("%d", &largeur);
    printf("Veuillez saisir le nombre de bombe (inferieur à %d): ", hauteur*largeur-1);
    scanf("%d", &nbBombe);
    
    caseTerrain terrain[hauteur*largeur];
    
    CreateTerrain(terrain, hauteur, largeur, nbBombe);
    
    SauvegardeTerrainEncours(terrain, hauteur, largeur );
    
    AfficheTerrainEncours(hauteur, largeur);
    
    return 0;
}
