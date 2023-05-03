#include "map.h"


/*RESET des structures*/

void res_Print(Print* pPrint){
  sprintf(pPrint->caractere, " ");
  
  sprintf(pPrint->back_color, "\e[48;2;%d;%d;%dm", 100, 200, 100);
  sprintf(pPrint->font_color, "\e[38;2;%d;%d;%dm", 10, 10, 10);
}

void res_CaseMap(CaseMap* pCaseMap){
  pCaseMap->biome = 0;
  pCaseMap->ressource = 0;

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

void loadMapPrint(Map* pMap){
  for(int y = 0; y < pMap->height; y++){
    for(int x = 0; x < pMap->width; x++){
      switch(pMap->tab[x][y].biome){
        case 1: // eau
          
          sprintf(pMap->tab[x][y].print.back_color, "\e[48;2;%d;%d;%dm", 27, 113, 207);
          sprintf(pMap->tab[x][y].print.font_color, "");
          sprintf(pMap->tab[x][y].print.caractere, " ");
        break;

        case 2: // sable
          sprintf(pMap->tab[x][y].print.back_color, "\e[48;2;%d;%d;%dm", 226, 231, 50);
          sprintf(pMap->tab[x][y].print.font_color, "");
          switch(pMap->tab[x][y].ressource){
            case 1:
              sprintf(pMap->tab[x][y].print.caractere, "⚔");
            break;
            default:
              sprintf(pMap->tab[x][y].print.caractere, " ");
            break;
          }
        break;
      }
    }
  }
}

void generateMap(Map* pMap){
  srand(time(NULL));

  for (int y = 0; y < pMap->height; y++) {
    for (int x = 0; x < pMap->width; x++) {
      if((x < 10 || pMap->width - x < 10) || (y < 10 || pMap->height - y < 10)){
        pMap->tab[x][y].biome = 1;
      }
      else{
        pMap->tab[x][y].biome = 2;
        if( !(rand() % 10)){
          pMap->tab[x][y].ressource = 1;
        }
      }
      
    }
  }
}

void printMap(Map* pMap){
  printf("\e[f");
  for (int y = 0; y < pMap->height; y++) {
    for (int x = 0; x < pMap->width; x++) {
      printf("%s%s %s ", pMap->tab[x][y].print.back_color, pMap->tab[x][y].print.font_color, pMap->tab[x][y].print.caractere);
    }
    printf("\n");
  }
  printf("\e[0m ");
}

