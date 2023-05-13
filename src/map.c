#include "map.h"

//
//RESET DES STRUCTURES
//

void res_Print(Print* pPrint){
  sprintf(pPrint->caractere, "  ");
  
  sprintf(pPrint->back_color, "\e[48;2;%d;%d;%dm", 100, 200, 100);
  sprintf(pPrint->font_color, "\e[38;2;%d;%d;%dm", 10, 10, 10);

  pPrint->isLoaded = 0;
}

void res_CaseMap(CaseMap* pCaseMap){
  pCaseMap->biome = VOID;
  pCaseMap->ressource = EMPTY;

  res_Print(&(pCaseMap->print));
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


//
//CONSTRUCTEURS DES STRUCTURES
//

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


//
//AUTRES FONCTIONS
//

void generateMap(Map* pMap){
  srand(time(NULL));

  for (int y = 0; y < pMap->height; y++) {
    for (int x = 0; x < pMap->width; x++) {
      if((x < 10 || pMap->width - x < 10) || (y < 10 || pMap->height - y < 10)){
        pMap->tab[x][y].biome = WATER;
      }
      else if((x < 15 || pMap->width - x < 15) || (y < 15 || pMap->height - y < 15)){
        pMap->tab[x][y].biome = SAND;
        if( !(rand() % 50)){
          pMap->tab[x][y].ressource = LEAF;
        }
      }
      else{
        pMap->tab[x][y].biome = GRASS;
        if( !(rand() % 20)){
          pMap->tab[x][y].ressource = TREE;
        }
        
      }
      
    }
  }
}

void printMap(Map* pMap){
  printf("\e[f");
  for (int y = 0; y < pMap->height; y++) {
    for (int x = 0; x < pMap->width; x++) {
      printf("%s%s%s", pMap->tab[x][y].print.back_color, pMap->tab[x][y].print.font_color, pMap->tab[x][y].print.caractere);
    }
    printf("\e[0m\n");
  }
}

