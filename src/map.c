#include "affichage.h"


//
//RESET DES STRUCTURES
//
 
void res_CaseMap(CaseMap* pCaseMap){
  pCaseMap->biome = VOID;
  pCaseMap->ressource = EMPTY;

}

void res_Map_tab(Donnees_Map* pDonnees_Map){
  for(int x=0; x < pDonnees_Map->width; x++){
    for(int y=0; y < pDonnees_Map->height; y++){
      res_CaseMap(&(pDonnees_Map->tab[x][y]));
    }
  }
}

void res_Map(Donnees_Map* pDonnees_Map){
  pDonnees_Map->width = 0;
  pDonnees_Map->height = 0;
  pDonnees_Map->tab = NULL;
}


//
//CONSTRUCTEURS DES STRUCTURES
//

CaseMap** constructor_Donnees_Map_tab(int width, int height){
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

Donnees_Map* constructor_Donnees_Map(int width, int height){
  
  Donnees_Map* pDonnees_Map = NULL;
  if( !(pDonnees_Map = malloc(sizeof(Donnees_Map)))){
    printf("ERREUR: pb avec le malloc de pMap");
  }

  res_Map(pDonnees_Map);
  
  pDonnees_Map->width = width;
  pDonnees_Map->height = height;
  
  pDonnees_Map->tab = constructor_Donnees_Map_tab(width, height);
  res_Map_tab(pDonnees_Map);

  return pDonnees_Map;
}

void free_Donnees_Map(Donnees_Map* pDonnees_Map){
  for (int x = 0; x < pDonnees_Map->width; x++) {
    free(pDonnees_Map->tab[x]);
  }
  free(pDonnees_Map->tab);
  free(pDonnees_Map);
}


//
//AUTRES FONCTIONS
//

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
