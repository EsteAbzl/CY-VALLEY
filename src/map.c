#include "map.h"


/*RESET des structures*/

void res_CaseMap(CaseMap* pCaseMap){
  pCaseMap->biome = 1;
  pCaseMap->ressource = 2;
}

void res_Map_tab(Map* pMap){
  for(int x=0; x < pMap->width; x++){
    for(int y=0; y < pMap->height; y++){
      res_CaseMap(&(pMap->tab[x][y]));
    }
  }
}

void res_Map(Map* pMap){
  pMap->width = 0;
  pMap->height = 0;
  pMap->tab = NULL;
}

/*CONSTRUCTEURS des stuctures*/

CaseMap** constructor_Map_tab(int width, int height){
  CaseMap** tab = NULL;

  if( !(tab = calloc(width, width * sizeof(CaseMap *)))) {
    printf("ERREUR: pb avec le malloc de tab");
  }

  for(int x = 0; x < width; x++) {
    if( !(tab[x] = calloc(height, height * sizeof(CaseMap)))) {
      printf("ERREUR: pb avec le malloc de tab[x]");
    }
  }

  return tab;
}

Map* constructor_Map(int width, int height){
  
  Map* pMap = NULL;
  if( !(pMap = malloc(sizeof(Map)))){
    printf("ERREUR: pb avec le malloc de pMap");
  }

  res_Map(pMap);
  
  pMap->width = width;
  pMap->height = height;
  
  pMap->tab = constructor_Map_tab(width, height);
  res_Map_tab(pMap);

  return pMap;
}

void free_Map(Map* pMap){
  for (int x = 0; x < pMap->width; x++) {
    free(pMap->tab[x]);
  }
  free(pMap->tab);
  free(pMap);
}

/*AUTRES fonctions*/

void printMap(Map* pMap){
  for (int y = 0; y < pMap->height; y++) {
    for (int x = 0; x < pMap->width; x++) {
      printf("|%d/%d", pMap->tab[x][y].biome, pMap->tab[x][y].ressource);
    }
    printf("\n");
  }
}

