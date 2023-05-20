#ifndef DONNEES_H
#define DONNEES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"

typedef struct{
  int x;
  int y;
}Pos;

unsigned long getTimeMicros();

void generateMap(Donnees_Map* pDonnees_Map);

#endif