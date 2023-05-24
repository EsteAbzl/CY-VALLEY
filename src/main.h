#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <ncurses.h>
#include <unistd.h>

#include "map.h"
#include "affichage.h"
#include "donnees.h"
#include "quete.h"

typedef enum{
  ACCUEIL, JEU
}Ecran;

typedef struct{
  WINDOW* pWin;

  // informe du mode d'affichage (qui est différent si on est en jeu de si on est dans le menu)
  Ecran ecran;
  int refreshMap;

  // camJeu, camAccueil, camMaison..
  Info_Cam* camJeu;
  Info_Cam* camAccueil;

  unsigned long initialTime;
  unsigned long startTime;
  unsigned long endTime;
  unsigned long frameTime;
  int fps;
}Info_Fenetre;


typedef struct{
  Entitee* pJoueur;
  Quete* pQ_Radeau;
  Quete* pQ_Survivant;


  ListeObj listeObj;
  char dialogue[300];

  // quête en cour?

  // mapJeu, mapAcceuil, mapMenu, mapGrotte...

  Map* mapJeu;
  Map* mapAccueil;

  int enJeu;
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
void debutJeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu);

//
//AUTRES FONCTIONS
//

void init_Curses(Info_Fenetre* pFenetre);
void freeGame(Info_Fenetre* pFenetre, Info_Jeu* pJeu);

void affiche_jeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu);
void printStat(Info_Fenetre* pFenetre, Info_Jeu* pJeu);
void gestionFps(Info_Fenetre* pFenetre);

#include "event.h"

#endif 