#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <ncurses.h>
#include <unistd.h>

#include "map.h"
#include "donnees.h"
#include "affichage.h"
#include "brush.h"

typedef enum{
  ACCUEIL, JEU, OCEAN, MORT, PAUL
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

  // quête en cour?

  // mapJeu, mapAcceuil, mapMenu, mapGrotte...

  Map* mapJeu;
  Map* mapAccueil;
  Map* mapOcean;
  Map* mapMort;
  Map* mapPaul;

  int enJeu;
  int score;
  long temps;

  int event;

  FILE* fSauvegarde;
  int partie_sauv;
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

void save_Game(Info_Fenetre* pFenetre, Info_Jeu* pJeu);
int load_Game(Info_Fenetre* pFenetre, Info_Jeu* pJeu);

void init_Curses(Info_Fenetre* pFenetre);
void freeGame(Info_Fenetre* pFenetre, Info_Jeu* pJeu);

void affiche_jeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu);

void printStat(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height);
void printInv(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height);
void printDialogue(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height);

void gestionFps(Info_Fenetre* pFenetre);
#include "event.h"

#endif 