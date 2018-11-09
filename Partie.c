//
//  Partie.c
//  
//
//
//
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#include "Demineur.h"

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
    scanf("%d",&choix);
    CLEAR_BUFFER;
    return choix;
}

int action()
/* Fonction qui permet à l'utilisateur d'ouvrir, ou flaguer une case */
{
    
    int a;
    
    do{
        printf("Voulez vous ouvrir (1) ou Flaguer/Deflaguer (2) : ");
        scanf("%d", &a);
        printf("Vous avez choisi %d\n",a);
        CLEAR_BUFFER;
    }
    while(a<0 || a>3);
    
    return a;
}

int gagne()
/* Fonction qui test la victoire de l'utilisateur si toute les cases
 * sans bombe sont ouverte et toute les case avec bombe sont flagge
 */
{
    return ( toutOuvert() && toutFlag() );
}



int tour()
/*fonction qui va definir un tour de jeu*/
{
    char caseX;
    int caseY;
    int act;
    int choix;
    
    if(afficheTerrainJeux(FICH_TAB_ENCOURS)) //Affiche le terrain et test si une bombe a été ouverte
    {
        printf("Vous avez perdu !!!\n");
        afficheTerrainPerdu(FICH_TAB_ENCOURS);
        return 1;
    }
    if(gagne()){
        printf("Bravo champion \n");
        return 1;
    }
        
    
    do{
        printf("Undo (1) , Jouer (2) ou Quitter (3) : ");
        scanf("%d", &choix);
        printf("Vous avez choisi %d\n",choix);
        CLEAR_BUFFER;
    }
    while(choix<0 || choix>4);
    
    caseTerrain* nouveauT = (caseTerrain*)malloc(sizeof(caseTerrain) * (*hauteurTerrain)*(*largeurTerrain));
    
    if(choix == 3){
        return 1;
    }
    else if(choix == 1){
        transferTerrain(FICH_TAB_PRECEDENT, FICH_TAB_ENCOURS); //on met l'ancien terrain dans le terrainen cours
    }
    else{
    
        printf("Saisir la colonne :");
        scanf("%c", &caseX);
        caseX = toupper(caseX); //toupper() va forcer la majuscule pour eviter les bugs
        CLEAR_BUFFER;
        printf("Saisir la ligne : ");
        scanf("%d", &caseY);
        CLEAR_BUFFER;
        
        act = action();
        
        switch (act){
                
            case 1: nouveauT = ouverture(caseX, caseY);
                break;
            case 2: nouveauT = mettreflague(caseX, caseY);
                break;
            default:
                break;
        }
        
        transferTerrain(FICH_TAB_ENCOURS, FICH_TAB_PRECEDENT);
        sauvegardeTerrain(nouveauT, FICH_TAB_ENCOURS);
    }
    return 0;
}


void continuerPartie()
/* Pour continuer une partie non termine*/
{
    int hl[3] = {0};
        
    FILE* f = fopen(FICH_HAU_LAR, "r");
    if (f == NULL){
        printf("Impossible de lire le fichier");
    }
        fscanf(f, "%d %d", &hl[0], &hl[1]);
        printf("hauteur = %d, largeur = %d \n", hl[0], hl[1]);
        
        hauteurTerrain = &hl[0];
        largeurTerrain = &hl[1];
        
    fclose(f);
    
    caseTerrain* terrain =  getTerrain( (*hauteurTerrain) * (*largeurTerrain) , FICH_TAB_ENCOURS);
    transferTerrain( FICH_TAB_ENCOURS, FICH_TAB_PRECEDENT);
    
    if (terrain!= NULL){
        do{
            
            if(tour())
                break;
            
        }while (1);
    }
    
}

void nouvellePartie()
/*Fonction qui lance une nouvelle partie*/
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
    sauvegardeHL();//on sauvegarde les dimension du tableau
    
    do{
        printf("Veuillez saisir le nombre de bombe (inferieur à %d ): ", hauteur*largeur-1);
        scanf("%d", &nbBombe);
        CLEAR_BUFFER;
    }
    while(nbBombe<0 || nbBombe>(largeur*hauteur)-1);
    
    caseTerrain* terrain= (caseTerrain*)malloc(sizeof(caseTerrain)*hauteur*largeur);
    
    createTerrain(terrain,nbBombe);//on creer le nouveau terrain
    sauvegardeTerrain(terrain, FICH_TAB_ENCOURS);//on le sauvegarde dans le fichier terrain en cours
    transferTerrain(FICH_TAB_ENCOURS, FICH_TAB_PRECEDENT);// pour eviter les bugs on met le terrain en cours dans le terrain precendent
    
    do{
        if(tour())
            break;
        
    }while (1);
    
    free(terrain);
    remove(FICH_TAB_PRECEDENT);

}

void play()
/*Debut du jeu*/
{
    int choix = menu();
    
    switch(choix){
        case 1: nouvellePartie();
            break;
        case 2 : continuerPartie();
            break;
        default:printf("Au revoir !");
            break;
    }
    
}
