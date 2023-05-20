#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <ncurses.h>

#include "map.h"
#include "game.h"
#include "affichage.h"

typedef enum{
  ACCUEIL, JEU, MENU
}Ecran;

typedef struct{
  WINDOW* pWin;

  int fps;
  unsigned long startTime;
  unsigned long endTime;
  unsigned long frameTime;
}Info_Fenetre;


typedef struct{
  Ecran ecran;

  int event;
}Info_Jeu;

typedef struct{
  int width;
  int height;

  Donnees_Map* pDonnees;
  Affichage_Map* pAffichage;
}Map;




//
//RESET DES STRUCTURES
//

void res_Map(Map* pMap);


//
//CONSTRUCTEURS DES STRUCTURES
//

Map* constructor_Map(int width, int height);

void free_Map(Map* pMap);


//
//AUTRES FONCTIONS
//

WINDOW* init_Curses();

#endif 