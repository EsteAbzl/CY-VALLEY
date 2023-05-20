#ifndef DONNEES_H
#define DONNEES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"


typedef struct{
  int x;
  int y;
}Coordonnees;



typedef enum{
  DROITE, GAUCHE, BAS, HAUT
}Regard;


typedef enum{
O_VIDE,
O_BATON,
O_CAILLOU,
O_HACHEP
}Id_Obj;

typedef struct{
  Id_Obj id_Obj;
  int nb_Max;
  int nb;
  int placeinv;
  //BuffObj buffObj;
  
  char nom[30];
}Obj;

typedef struct{
  Obj inv[30];
  int stockagePris;
  int stockageTotal;
}Inventaire;


typedef struct{
  Coordonnees coordonnees;
  Regard regard;

  int pvActuelle;
  int pvTotal;
  int atk;

  Inventaire inventaire;
}Entitee;



unsigned long getTimeMicros();

void generateMap(Donnees_Map* pDonnees_Map);



void res_Obj(Obj* pObj);

void init_Inventaire(Inventaire* pInv, int size);

Entitee* init_Entitee();

void res_Entitee(Entitee* pEnt);

void free_Entitee(Entitee* pEnt);



void afficherStats(Entitee* entitee);

void testStats(Entitee* entitee);

void modifpvTT(int dmg_Heal, Entitee* entitee);

void modifpvA(int dmg_Heal, Entitee* entitee);

#endif