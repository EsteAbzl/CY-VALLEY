#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdlib.h>
#include <stdio.h>

#include <ncurses.h>

typedef struct{
  int width; // largeur
  int height; // hauteur

  int xCam;
  int yCam;

  FILE* pAffichage;
}Info_Cam;


#include "map.h"
#include "brush.h"
#include "donnees.h"

//
//INIT COULEUR ET BROSSES
//

// permet de changer des couleurs avec des valeurs entre 0 ett 255
void setColor(unsigned char id, unsigned char r, unsigned char g, unsigned char b);
// initialise toutes les couleurs
void init_Colors();
// initialise toutes les brush
void init_Brush();


//
//RESET DES STRUCTURES
//

void res_Info_Cam(Info_Cam* pCam);


//
//CONSTRUCTEURS DES STRUCTURES
//

Info_Cam* constructor_Info_Cam(int width, int height);


//
//AUTRES FONCTIONS
//
// Charge l'affichage d'une case
void loadPrint(CaseMap caseMap, Print* pPrint);
// Charge l'affichage de toutes les cases de la map
void loadMapPrint(Map* pMap);
// Charge l'affichage des cases présentes sur la caméra
void loadCamPrint(Coordonnees coordonnee, Map* pMap, Info_Cam* pCam);

// affiche une portion de la map relative a la caméra passée en paramètre
void printCam(Coordonnees coordonnee, Affichage_Map* pAffichage_Map, Info_Cam* pCam);
void printFin_Radeau(Coordonnees coordonnee, Affichage_Map* pAffichage_Map, Info_Cam* pCam);

//Affiche le contenu d'une Map en entier
void printMap(Affichage_Map* pAffichage_Map);



#endif