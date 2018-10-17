#include<stdio.h>
#include<stdlib.h>

typedef struct caseTerrain
{
  int posX;
  int posY;
  int etat;
  char  contenu;
}caseTerrain;

int main()
{
  FILE* f;
  int taille;
  int i, j;
  printf("bonjour veuillez saisir la taille du terrain ?");
  scanf("%d",&taille);
  //creatTerrain(taille);
  struct caseTerrain terrain[(taille*taille)+1];
  
  for(i=0;i<taille;i++){
    for(j=0;j<taille;j++){
        if (i==0 && j==0)
            terrain[0].etat=taille;
        
      terrain[i+j].posX=i;
      terrain[i+j].posY=j;
      terrain[i+j].etat=0;
        if(i%2==0)
            terrain[i+j].contenu='V';
        else
            terrain[i+j].contenu='B';
    }
  }
 f = fopen("terrainActuel.txt", "w");
 if (f == NULL)
   return 1;
 fwrite(terrain, taille*taille , sizeof(struct caseTerrain), f);
 fclose(f);
 return 0;
}

/* creatTerrain(int t){
 
 struct caseTerrain terrain[taille*taille];
 
}
*/
