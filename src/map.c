#include "affichage.h"


//
//RESET DES STRUCTURES
//

// DONNEES
void res_CaseMap(CaseMap* pCaseMap){
  pCaseMap->biome = VOID;
  pCaseMap->ressource = EMPTY;

}

void res_Donnees_Map_tab(Donnees_Map* pDonnees_Map){
  for(int x=0; x < pDonnees_Map->width; x++){
    for(int y=0; y < pDonnees_Map->height; y++){
      res_CaseMap(&(pDonnees_Map->tab[x][y]));
    }
  }
}

void res_Donnees_Map(Donnees_Map* pDonnees_Map){
  pDonnees_Map->width = 0;
  pDonnees_Map->height = 0;
  pDonnees_Map->tab = NULL;
}

// AFFICHAGE
void res_Print(Print* pPrint){
  sprintf(pPrint->caractere, "  ");
  
  pPrint->brush = BRUSH_VOID;
 
  pPrint->isLoaded = 0;
}

void res_Affichage_Map_tab(Affichage_Map* pAffichage_Map){
  for(int x=0; x < pAffichage_Map->width; x++){
    for(int y=0; y < pAffichage_Map->height; y++){
      res_Print(&(pAffichage_Map->tab[x][y]));
    }
  }
}

void res_Affichage_Map(Affichage_Map* pAffichage_Map){
  pAffichage_Map->width = 0;
  pAffichage_Map->height = 0;
  pAffichage_Map->tab = NULL;
}

// MAP
void res_Map(Map* pMap){
  pMap->width = 0;
  pMap->height = 0;

  pMap->pDonnees = NULL;
  pMap->pAffichage = NULL;
}


//
//CONSTRUCTEURS DES STRUCTURES
//

//  Retourne un pointeur sur un tableau a deux dimention du type souhaité.
// DONNEES
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

// AFFICHAGE
Print** constructor_Affichage_Map_tab(int width, int height){
  Print** tab = NULL;

  if( !(tab = calloc(width, width * sizeof(Print *)))) {
    printf("ERREUR: pb avec le malloc de tab");
  }

  for(int x = 0; x < width; x++) {
    if( !(tab[x] = calloc(height, height * sizeof(Print)))) {
      printf("ERREUR: pb avec le malloc de tab[x]");
    }
  }

  return tab;
}


//  Retourne un pointeur sur un objet de type souhaité.
// DONNEES
Donnees_Map* constructor_Donnees_Map(int width, int height){
  
  Donnees_Map* pDonnees_Map = NULL;
  if( !(pDonnees_Map = malloc(sizeof(Donnees_Map)))){
    printf("ERREUR: pb avec le malloc de pDonnees_Map");
  }

  res_Donnees_Map(pDonnees_Map);
  
  pDonnees_Map->width = width;
  pDonnees_Map->height = height;
  
  pDonnees_Map->tab = constructor_Donnees_Map_tab(width, height);
  res_Donnees_Map_tab(pDonnees_Map);

  return pDonnees_Map;
}

// AFFICHAGE
Affichage_Map* constructor_Affichage_Map(int width, int height){
  
  Affichage_Map* pAffichage_Map = NULL;
  if( !(pAffichage_Map = malloc(sizeof(Affichage_Map)))){
    printf("ERREUR: pb avec le malloc de pAffichage_Map");
  }
  
  pAffichage_Map->width = width;
  pAffichage_Map->height = height;
  
  pAffichage_Map->tab = constructor_Affichage_Map_tab(width, height);
  res_Affichage_Map_tab(pAffichage_Map);

  return pAffichage_Map;
}

// MAP
Map* constructor_Map(int width, int height){
  Map* pMap = NULL;
  if( !(pMap = malloc(sizeof(Map)))){
    printf("ERREUR: pb avec le malloc de pMap");
  }

  res_Map(pMap);
  
  pMap->width = width;
  pMap->height = height;
  
  pMap->pDonnees = constructor_Donnees_Map(width, height);
  pMap->pAffichage = constructor_Affichage_Map(width, height);

  return pMap;
}


//
//  DESALLOCATION
//

// DONNEES
void free_Donnees_Map(Donnees_Map* pDonnees_Map){
  for (int x = 0; x < pDonnees_Map->width; x++) {
    free(pDonnees_Map->tab[x]);
  }
  free(pDonnees_Map->tab);
  free(pDonnees_Map);
}

// AFFICHAGE
void free_Affichage_Map(Affichage_Map* pAffichage_Map){
  for (int x = 0; x < pAffichage_Map->width; x++) {
    free(pAffichage_Map->tab[x]);
  }
  free(pAffichage_Map->tab);
  free(pAffichage_Map);
}

// MAP
void free_Map(Map* pMap){
  free_Donnees_Map(pMap->pDonnees);
  free_Affichage_Map(pMap->pAffichage);
  free(pMap);
}
