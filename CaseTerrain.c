#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#include "Demineur.h"

void ouvertureCase(caseTerrain* terrain, int pX, int pY)
/* Fonction qui va ouvrir un case, et si cette case est vide, va ouvrir ses cases voisines*/
{
    if ( (terrain+ (pX+pY*(*largeurTerrain) )) ->etat == C_FERMEE ){
        (terrain+(pX+pY*(*largeurTerrain)) )->etat= C_OUVERTE;
           if ( (terrain+(pX+pY*(*largeurTerrain)) )-> contenu == 0) {
            ouvertureCaseVoisine(terrain, pX, pY);
        }
    }
}
void flagCase(caseTerrain* terrain, int pX, int pY)
/* Fonction qui flag une case*/
{
    if ( (terrain+(pX+pY*(*largeurTerrain)) )->etat == C_FERMEE )
        (terrain+(pX+pY*(*largeurTerrain)) )->etat= C_FLAG;
    else if( (terrain+(pX+pY*(*largeurTerrain)) )->etat == C_FLAG )
         (terrain+(pX+pY*(*largeurTerrain)) )->etat= C_FERMEE;
}
void ouvertureCaseVoisine(caseTerrain* terrain, int pX, int pY)
/* Fonction qui va ouvrir les case voisines valide d'un case passee en parametre*/
{
    if(caseValide(pX,pY+1)){
        ouvertureCase(terrain,pX,pY+1);
    }
    if(caseValide(pX+1,pY+1)){
        ouvertureCase(terrain,pX+1,pY+1);
    }
    if(caseValide(pX+1,pY)){
        ouvertureCase(terrain,pX+1,pY);
    }
    if(caseValide(pX+1,pY-1)){
        ouvertureCase(terrain,pX+1,pY-1);
    }
    if(caseValide(pX,pY-1)){
        ouvertureCase(terrain,pX,pY-1);
    }
    if(caseValide(pX-1,pY-1)){
        ouvertureCase(terrain,pX-1,pY-1);
    }
    if(caseValide(pX-1,pY)){
        ouvertureCase(terrain,pX-1,pY);
    }
    if(caseValide(pX-1,pY+1)){
        ouvertureCase(terrain,pX-1,pY+1);
    }
    
}

void ajoutNBombe(caseTerrain* terrain, int pX, int pY)
/* Fonction qui verifie si la case est une bombe pour gerer ses voisines*/
{
    if ( (terrain+(pX+pY*(*largeurTerrain)) )->contenu == C_BOMBE ){
        plus1CasesVoisines(terrain,pX, pY);
    }
}

void plus1CasesVoisines(caseTerrain* terrain, int pX, int pY)
/* Fonction qui increment le contenu des cases voisines d'un bombe */
{
    if(caseValide(pX,pY+1)){
        if ( (terrain+(pX+(pY+1)*(*largeurTerrain)) )-> contenu != C_BOMBE)
        (terrain+(pX+(pY+1)*(*largeurTerrain) ))->contenu +=1;
    }
    if(caseValide(pX+1,pY+1)){
        if ( (terrain+((pX+1)+(pY+1)*(*largeurTerrain)) )-> contenu != C_BOMBE)
        (terrain+((pX+1)+(pY+1)*(*largeurTerrain)) )->contenu +=1;
    }
    if(caseValide(pX+1,pY)){
        if ( (terrain+((pX+1)+pY*(*largeurTerrain)) )-> contenu != C_BOMBE)
        (terrain+((pX+1)+pY*(*largeurTerrain)) )->contenu +=1;
    }
    if(caseValide(pX+1,pY-1)){
        if ( (terrain+((pX+1)+(pY-1)*(*largeurTerrain)) )-> contenu != C_BOMBE)
        (terrain+((pX+1)+(pY-1)*(*largeurTerrain)) )->contenu +=1;
    }
    if(caseValide(pX,pY-1)){
        if ( (terrain+(pX+(pY-1)*(*largeurTerrain)) )-> contenu != C_BOMBE)
        (terrain+(pX+(pY-1)*(*largeurTerrain)) )->contenu +=1;
    }
    if(caseValide(pX-1,pY-1)){
        if ( (terrain+((pX-1)+(pY-1)*(*largeurTerrain)) )-> contenu != C_BOMBE)
        (terrain+((pX-1)+(pY-1)*(*largeurTerrain)) )->contenu +=1;
    }
    if(caseValide(pX-1,pY)){
        if ( (terrain+((pX-1)+pY*(*largeurTerrain)) )-> contenu != C_BOMBE)
        (terrain+((pX-1)+pY*(*largeurTerrain)) )->contenu +=1;
    }
    if(caseValide(pX-1,pY+1)){
        if ( (terrain+((pX-1)+(pY+1)*(*largeurTerrain)) )-> contenu != C_BOMBE)
            (terrain+((pX-1)+(pY+1)*(*largeurTerrain)) )->contenu +=1;
    }
    
}

int caseValide(int pX, int pY)
/* fonction qui retourne 1 si la case est valide, soit si elle est bien dans le terrain */
{
    return ( pX >= 0 && pX < *largeurTerrain && pY >= 0 && pY < *hauteurTerrain);
}
