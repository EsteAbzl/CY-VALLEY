#ifndef QUETE_H
#define QUETE_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <ncurses.h>

#include "map.h"
#include "affichage.h"
#include "donnees.h"

typedef struct{
  Entitee npc;
  int etape;
  int e_Dialogue;

  char dialogue[100];

}Quete;

void res_Quete(Quete* pQuete);

void quete_Dialogue(Quete* pQuete);

void quete_Radeau_1(Quete* pQuete, ListeObj* pListe);

void quete_Radeau_2(Quete* pQuete, ListeObj* pListe);

void quete_Radeau_3(Quete* pQuete, ListeObj* pListe);

void quete_Radeau_4(Quete* pQuete, ListeObj* pListe);

void quete_RadeauR(Quete* pQuete, ListeObj* pListe);

void ecran_Fin_Radeau(); // a faire

void paul_Fin(); // à faire

#endif