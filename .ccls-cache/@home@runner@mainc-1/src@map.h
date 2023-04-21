#include <stdio.h>
#include <stdlib.h>



typedef struct Casemap{
  int biome;
  int ressource;
  
}CaseMap;

typedef struct Map{
  int width;
  int height;
  CaseMap **tab;

}Map;




void res_CaseMap(CaseMap* pCaseMap);

void init(Map* pMap);

void res_Map(Map* pMap);

// Retourne un pointeur sur un tableau a deux dimention de type Map.
// Le tableau se lit: map[x][y]
void createMap(Map* pMap, int width, int height);

// Libère la mémoire prise par une map passée en paramètre.
// IMPORTANT DE LE FAIRE POUR TOUTES LES MAPS
void freeMap(Map map);



void printMap(Map map);

