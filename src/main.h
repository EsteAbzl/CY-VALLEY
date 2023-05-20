#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <ncurses.h>

#include "map.h"
#include "game.h"
#include "affichage.h"
#include "donnees.h"

typedef enum{
  ACCUEIL, JEU, MENU
}Ecran;

typedef struct{
  WINDOW* pWin;

  // informe du mode d'affichage (qui est différent si on est en jeu de si on est dans le menu)
  Ecran ecran;

  // camJeu, camAccueil, camMaison..

  int fps;
  unsigned long startTime;
  unsigned long endTime;
  unsigned long frameTime;
}Info_Fenetre;


typedef struct{
  // Info_joueur
      // pos
      // inventaire

  // liste_Enemis (tableau dynamique)

  // etat du jeu
  // quête en cour?
  // vitesse? 

  // mapJeu, mapAcceuil, mapMenu, mapGrotte...

  int score;

  int event;
}Info_Jeu;

//
//INIT DES STRUCTURES
//

Info_Fenetre* init_Info_Fenetre();
Info_Jeu* init_Info_Jeu();


//
//RESET DES STRUCTURES
//

void res_Info_Jeu(Info_Jeu* pJeu);


//
//AUTRES FONCTIONS
//

void init_Curses(Info_Fenetre* pFenetre);

#endif 