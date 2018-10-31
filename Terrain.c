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

void printTerrainJeux(caseTerrain* t)
/*Fonction qui affiche un terrain pour la partie*/
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
                if( (t+(cptLargeur+cptHauteur*largeur))->etat == C_OUVERTE){
                    if( (t+(cptLargeur+cptHauteur*largeur))->contenu == C_BOMBE)
                        printf(" B |");
                    else
                        printf(" %d |",(t+(cptLargeur+cptHauteur*largeur))->contenu);
                }
                else if( (t+(cptLargeur+cptHauteur*largeur))->etat == C_FLAG )
                    printf(" F |");
                else
                    //printf(" %d |",(t+(cptLargeur+cptHauteur*largeur))->etat);
                    printf(" # |");
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
void createTerrain(caseTerrain* terrain, int nbBombe){
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    int i, j;
    int cptCase =0;
    int taille = hauteur*largeur;
    int* tab = (int*)malloc(sizeof(int)*taille);
    
    initTabBombe(tab,taille, nbBombe);//initialisation d'un tableau avec le bon nombre de bombe
    printTab(tab, taille);//affichage pour les tests
    //melangeTabBombe(tab,taille);//on melange le tableau de bombe aléatoirement
    printTab(tab, taille);//affichage pour les tests
    
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
    printf("Terrain crée\n");//message pour les tests
    printTerrainTest(terrain,hauteur*largeur);
}

int sauvegardeTerrain(caseTerrain* terrain){
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    FILE* f = fopen(FICH_TAB_ENCOURS, "w+");
    if (f == NULL)
        return 1;
    fwrite(terrain, 1, sizeof(caseTerrain)*hauteur*largeur, f);
    fclose(f);
    printf("Terrain sauvegardé\n");
    return 0;
    
}

caseTerrain* getTerrain(int taille, char* fichTab){
    int i, j, n = 0;
    
    FILE* f = fopen(fichTab, "r");
    if (f == NULL){
        printf("impossible d'ouvrir le terrain");
        return NULL;
    }
    printf("Affichage terrain : \n");
    caseTerrain* terrain = (caseTerrain*)malloc(sizeof(caseTerrain)*taille);
    while(fread(terrain + n, 1, sizeof(caseTerrain), f)){
        n++;
    }
    fclose(f);
    return terrain;
}



int afficheTerrainTest(char* fichTab){
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    caseTerrain* terrain = getTerrain(largeur*hauteur,fichTab);
    if(terrain==NULL)
        return 1;
    
    //printTerrainTest(terrain, largeur*hauteur);
    printTerrainJeux(terrain);
    
    return 0;
    
}

caseTerrain* ouverture(int cx, int cy){
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    caseTerrain* nouveauT = getTerrain(largeur*hauteur,FICH_TAB_ENCOURS);
    ouvertureCase(nouveauT, cx-65, cy);
    
    return nouveauT;
    
}

caseTerrain* mettreflague (int cx, int cy){
    int largeur = *largeurTerrain;
    int hauteur = *hauteurTerrain;
    caseTerrain* nouveauT = getTerrain(largeur*hauteur,FICH_TAB_ENCOURS);
    flagCase(nouveauT, cx-65, cy);
    
    return nouveauT;
    
}
