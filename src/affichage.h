#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "map.h"


//
//ENUMS, STRUCTURES
//

typedef struct{
  int width; // largeur
  int height; // hauteur

  FILE* fAffichage;
}Info_Cam;


//
//RESET DES STRUCTURES
//

void res_Info_Cam(Info_Cam* pCam);


//
//CONSTRUCTEURS DES STRUCTURES
//

Info_Cam* constructor_Info_Cam(int width, int height);
void free_Cam(Info_Cam* pCam);

//
//AUTRES FONCTIONS
//

void loadMapPrint(Map* pMap);

void printCam(Pos coordonnee, Map* pMap, Info_Cam* pCam);

#endif