#include "map.h"

void res_Map(Map* caseMap) {
  caseMap->nombre = 'A';
}



Map **createMap(int width, int height) {
  Map **map = NULL;

  if (!(map = calloc(width, width * sizeof(int *)))) {
    printf("ERREUR: pb avec malloc");
  }

  for (int x = 0; x < width; x++) {
    if (!(map[x] = calloc(height, height * sizeof(int)))) {
      printf("ERREUR: pb avec malloc");
    }
  }

  return map;
}

void freeMap(Map **map, int w) {
  for (int x = 0; x < w; x++) {
    free(map[x]);
  }
  free(map);
}



void create_initMap(Map **map, int w, int h) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      res_Map(&(map[x][y]));
    }
  }
}

void printMap(Map **map, int w, int h) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      printf("|%c", map[x][y].nombre);
    }
    printf("\n");
  }
}