#include "map.h"



void res_CaseMap(CaseMap* pCaseMap){
  pCaseMap->biome = 1;
  pCaseMap->ressource = 2;
}

void init(Map* pMap){
  for(int x=0; x < pMap->width; x++ ){
    for(int y=0; y < pMap->height;y++){
      res_CaseMap(&(pMap->tab[x][y]));
    }
  }
}

void res_Map(Map* pMap){
  pMap->width = 0;
  pMap->height = 0;
  pMap->tab = NULL;
}




void createMap(Map* pMap, int width, int height){
  pMap->width = width;
  pMap->height = height;
  
  if (!(pMap->tab = calloc(width, width * sizeof(CaseMap *)))) {
    printf("ERREUR: pb avec malloc");
  }

  for (int x = 0; x < width; x++) {
    if (!(pMap->tab[x] = calloc(height, height * sizeof(CaseMap)))) {
      printf("ERREUR: pb avec malloc");
    }
  }

  init(pMap);

}

void freeMap(Map map){
  for (int x = 0; x < map.width; x++) {
    free(map.tab[x]);
  }
  free(map.tab);
}



void printMap(Map map){
  for (int y = 0; y < map.height; y++) {
    for (int x = 0; x < map.width; x++) {
      printf("|%d/%d", map.tab[x][y].biome, map.tab[x][y].ressource);
    }
    printf("\n");
  }
}

