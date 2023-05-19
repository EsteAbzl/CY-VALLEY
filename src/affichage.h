#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "map.h"

typedef enum{
  COLOR_VOID,
  COLOR_WATER,
  COLOR_SAND, 
  COLOR_GRASS
}Color;

typedef enum{
  BRUSH_VOID,
  BRUSH_WATER,
  BRUSH_SAND,
  BRUSH_GRASS
}Brush;


typedef struct{
  char caractere[10]; // permet d'afficher des caractère utf-8: sprintf(caractere, "🌳");
  Brush brush; // 'Pinceau' qui contient la couleur de fond et de caractère

  int isLoaded;
}Print;

//Structure qui réunis permet l'affichage d'une map.
typedef struct{
  int width;
  int height;

  Print **tab;

}Affichage_Map;



typedef struct{
  int width; // largeur
  int height; // hauteur

  FILE* pAffichage;
}Info_Cam;


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

void res_Print(Print* pPrint);
void res_Affichage_Map_tab(Affichage_Map* pAffichage_Map);
void res_Affichage_Map(Affichage_Map* pAffichage_Map);

void res_Info_Cam(Info_Cam* pCam);


//
//CONSTRUCTEURS DES STRUCTURES
//

Print** constructor_Affichage_Map_tab(int width, int height);

//Retourne un pointeur sur un objet de type Map.
Affichage_Map* constructor_Affichage_Map(int width, int height);
Info_Cam* constructor_Info_Cam(int width, int height);


void free_Affichage_Map(Affichage_Map* pAffichage_Map);

//
//AUTRES FONCTIONS
//

void loadMapPrint(Donnees_Map* pDonnees_Map, Affichage_Map* pAffichage_Map);

void printCam(Pos coordonnee, Affichage_Map* pAffichage_Map, Info_Cam* pCam);

//Affiche le contenu du tableau d'une Map en entier
void printMap(Affichage_Map* pAffichage_Map);

#endif