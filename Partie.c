//
//  Partie.c
//  
//
//
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "Demineur.h"

int* hauteurTerrain ;//= (int)malloc(sizeof(int)));
int* largeurTerrain ;//= (int)malloc(sizeof(int)));

void affichageMenu()
/*Fonction qui affiche le menu démarrage*/
{
    printf("______               _                       \n");
    printf("|  _  \\             (_)                      \n");
    printf("| | | |___ _ __ ___  _ _ __   ___ _   _ _ __ \n");
    printf("| | | / _ \\ '_ ` _ \\| | '_ \\ / _ \\ | | | '__|\n");
    printf("| |/ /  __/ | | | | | | | | |  __/ |_| | |   \n");
    printf("|___/ \\___|_| |_| |_|_|_| |_|\\___|\\__,_|_|   \n");
    
    printf("1) Nouvelle partie\n");
    printf("2) Charger dernière partie\n");
    printf("3) Quitter\n");
}

int menu()
/*Fonction gère la saisie faite par l'utilisateur*/
{
    int choix;
    affichageMenu();
    scanf("%d\n",&choix);
    CLEAR_BUFFER;
    return choix;
}

int action(){
    
    int a;
    
    do{
        printf("Voulez vous ouvrir (1) ou Flaguer/Deflaguer (2) : ");
        scanf("%d", &a);
        printf("Vous avez choisi %d",a);
        CLEAR_BUFFER;
    }
    while(a<0 || a>3);
    
    return a;
}

int tour()
/*fonction qui va definir un tour de jeu*/
{
    char caseX;
    int caseY;
    int act;
    
    caseTerrain* nouveauT = (caseTerrain*)malloc(sizeof(caseTerrain) * (*hauteurTerrain)*(*largeurTerrain));
    
    printf("Saisir la colonne :");
    scanf("%c", &caseX);
    CLEAR_BUFFER;
    printf("Saisir la ligne : ");
    scanf("%d", &caseY);
    CLEAR_BUFFER;
    
    act = action();
    
    switch (act){
    
        case 1: nouveauT = ouverture(caseX, caseY, (*hauteurTerrain), (*largeurTerrain));
            break;
        case 2: nouveauT = mettreflague(caseX, caseY, (*hauteurTerrain), (*largeurTerrain));
            break;
        default:
            break;
    }
                                                 
    sauvegardeTerrain(nouveauT, (*hauteurTerrain), (*largeurTerrain));
    return 0;
}

void continuerPartie(){
    
    
}

void nouvellePartie()
/*fonction qui lance une nouvelle partie*/
{
    int hauteur, largeur, nbBombe;
    
    printf("Veuillez saisir la hauteur du tableau : ");
    scanf("%d", &hauteur);
    hauteurTerrain=&hauteur;
    CLEAR_BUFFER;
    printf("Veuillez saisir la largeur du tableau : ");
    scanf("%d", &largeur);
    largeurTerrain=&largeur;
    CLEAR_BUFFER;
    do{
        printf("Veuillez saisir le nombre de bombe (inferieur à %d ): ", hauteur*largeur);
        scanf("%d", &nbBombe);
        CLEAR_BUFFER;
    }
    while(nbBombe<0 || nbBombe>(largeur*hauteur));
    
    caseTerrain* terrain= (caseTerrain*)malloc(sizeof(caseTerrain)*hauteur*largeur);
    
    createTerrain(terrain, hauteur, largeur, nbBombe);
    sauvegardeTerrain(terrain, hauteur, largeur );
    do{
        
        afficheTerrainTest((*hauteurTerrain), (*largeurTerrain), FICH_TAB_ENCOURS);
        if(tour())
            break;
        
    }while (1);

}

void play(){
    
    int choix = menu();
    
    switch(choix){
        case 1: nouvellePartie();
        case 2 : continuerPartie();
        default:printf("Au revoir !");
    }
    
}
