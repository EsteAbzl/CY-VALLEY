#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int nombre;
}Map;

void res_Map(Map* caseMap);

// Retourne un pointeur sur un tableau a deux dimention de type Map.
// Le tableau se lit: map[x][y]
Map** createMap(int width, int height);

// Libère la mémoire prise par une map passée en paramètre.
// IMPORTANT DE LE FAIRE POUR TOUTES LES MAPS
void freeMap(Map** map, int w);


void create_initMap(Map **map, int w, int h);

void printMap(Map **map, int w, int h);