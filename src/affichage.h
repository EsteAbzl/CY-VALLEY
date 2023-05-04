#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "map.h"

typedef struct{
  int width; // largeur
  int height; // hauteur

  FILE* pAffichage;
}Info_Cam;


void res_Info_Cam(Info_Cam* pCam);

Info_Cam* constructor_Info_Cam(int width, int height);


void loadMapPrint(Map* pMap);

void printCam(Pos coordonnee, Map* pMap, Info_Cam* pCam);

#endif