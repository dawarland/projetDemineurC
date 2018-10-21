//
//  Main.c
//  
//
//
//
#include<stdio.h>
#include<stdlib.h>
#include "Demineur.h"

int main(){
    int hauteur, largeur, nbBombe;
    
    printf("Veuillez saisir la hauteur du tableau : ");
    scanf("%d", &hauteur);
    printf("Veuillez saisir la largeur du tableau : ");
    scanf("%d", &largeur);
    printf("Veuillez saisir le nombre de bombe (inferieur à %d x %d ): ", hauteur, largeur);
    scanf("%d", &nbBombe);
    
    caseTerrain* terrain= (caseTerrain*)malloc(sizeof(caseTerrain)*hauteur*largeur);
    
    createTerrain(terrain, hauteur, largeur, nbBombe);
    sauvegardeTerrainEncours(terrain, hauteur, largeur );
    afficheTerrainEncoursTest(hauteur, largeur);
    
    
    
    
    return 0;
}
