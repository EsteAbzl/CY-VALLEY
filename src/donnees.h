#ifndef DONNEES_H
#define DONNEES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "map.h"


typedef struct{
  int x;
  int y;
}Coordonnees;



typedef enum{
  HAUT, DROITE, BAS, GAUCHE
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
  Obj baton;
  Obj caillou;
  Obj hache;
}ListeObj;

typedef struct{
  Obj inv[30];
  int stockagePris;
  int stockageTotal;
}Inventaire;


typedef struct{
  Coordonnees coordonnees;
  Coordonnees initial;
  Regard regard;

  long T_dernierDeplacement;
  long T_intervalleDeplacement; // Temps nécessaire entre chaques déplacement (1s = 1 000 000) 

  int pvActuelle;
  int pvTotal;
  int atk;

  Inventaire inventaire;
}Entitee;



unsigned long getTimeMicros();

void generateMap(Donnees_Map* pDonnees_Map);


//res et ini
void res_Vide(Obj* pObj, int n);

void res_Obj(Obj* pObj);

void init_Inventaire(Inventaire* pInv, int size);

Entitee* init_Entitee();

void res_Entitee(Entitee* pEnt);

void free_Entitee(Entitee* pEnt);

Obj constructor_Obj(Id_Obj O_nom, int nb_Max, char nom[30]);

ListeObj init_ListeObj();

//fonctions

void afficherStats(Entitee* entitee);

void testStats(Entitee* entitee);

void modifpvTT(int dmg_Heal, Entitee* entitee);

void modifpvA(int dmg_Heal, Entitee* entitee);

int ramasser(Obj* pObj, Entitee* pJoueur);

void test();

#endif