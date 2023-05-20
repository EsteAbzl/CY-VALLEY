#include "donnees.h"


unsigned long getTimeMicros(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec*1000000) + (tv.tv_usec/1);
} 


void generateMap(Donnees_Map* pDonnees_Map){
  srand(time(NULL));

  for (int y = 0; y < pDonnees_Map->height; y++) {
    for (int x = 0; x < pDonnees_Map->width; x++) {
      if((x < 10 || pDonnees_Map->width - x < 10) || (y < 10 || pDonnees_Map->height - y < 10)){
        pDonnees_Map->tab[x][y].biome = WATER;
      }
      else if((x < 15 || pDonnees_Map->width - x < 15) || (y < 15 || pDonnees_Map->height - y < 15)){
        pDonnees_Map->tab[x][y].biome = SAND;
        if( !(rand() % 50)){
          pDonnees_Map->tab[x][y].ressource = LEAF;
        }
      }
      else{
        pDonnees_Map->tab[x][y].biome = GRASS;
        if( !(rand() % 20)){
          pDonnees_Map->tab[x][y].ressource = TREE;
        }
      }
      
    }// x
  }// y
}