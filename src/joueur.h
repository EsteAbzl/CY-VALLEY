#ifndef JOUEUR_H
#define JOUEUR_H

#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "game.h"
#include "affichage.h"

typedef struct{
  Obj inv[30];
  int stockagePris;
  int stockageTotal;
}Inventaire;

typedef struct{
  Pos pJoueur;
  int pvActuelle;
  int pvTotal;
  int atk;
  Inventaire inventaire;
}Entitee;

void mort(Entitee* mort);

void iniEntitee(Entitee* pEnt);

void modifatk(int buff, Entitee* entitee);

void modifpvTT(int dmg_Heal, Entitee* entitee);

void modifpvA(int dmg_Heal, Entitee* entitee);

void iniInventaire(Inventaire* pInv, int size);

void mainInventaire(Inventaire* pInv, Entitee entitee);

void afficherStats(Entitee* entitee);

void testStats(Entitee* entitee);
  

#endif