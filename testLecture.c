#include<stdio.h>
#include<stdlib.h>

struct caseTerrain
{
  int posX;
  int posY;
  int etat;
  char  contenu;
}caseTerrain;

int main(int argv, char** argc)
{
  FILE* f;
  int i, j, n = 0;
  
  f = fopen("terrain.txt", "r");
  if (f == NULL){
    printf("impossible d'ouvrir le terrain");
    return 1;
  }
    //int taille = terrain[0].etat;
    struct caseTerrain terrain[10*10];
    while(fread(terrain + n, 1, sizeof(struct caseTerrain), f)){
        
    printf("%d-%c ", terrain[i+j].etat, terrain[i+j].contenu);
        n++;
	if(n%4==0)
	  printf("\n");
  }
  fclose(f);
  return 0;
}
/* creatTerrain(int t){
 
 struct caseTerrain terrain[taille*taille];
 
}
int main(){
  
  int taille;
  int i;
  printf("bonjour veuillez saisir la taille du terrain ?");
  scanf("%d",&taille);
  creatTerrain(taille);*/
