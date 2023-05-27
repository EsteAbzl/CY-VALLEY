#ifndef DONNEES_H
#define DONNEES_H

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

typedef struct{
  int x;
  int y;
}Coordonnees;



typedef enum{
  HAUT, DROITE, BAS, GAUCHE
}Regard;


typedef enum{
O_VIDE,
//ressources
O_COCO,
O_BATON,
O_FEUILLE,
O_CAILLOU,

//obj quetes
O_CORDE,
O_VOILE,

//outils
O_HACHE,
O_PIOCHE
}Id_Obj;

typedef struct{
  Id_Obj id_Obj;
  int nb_Max;
  int nb;
  int placeinv;
  //BuffObj buffObj;
  
  char nom[30];
  char symbole[10];
}Obj;

typedef struct{
  Obj coco;
  Obj baton;
  Obj feuille;
  Obj caillou;

  Obj corde;
  Obj voile;

  Obj hache;
  Obj pioche;
}ListeObj;



typedef struct{
  Obj inv[30];
  int stockagePris;
  int stockageTotal;
}Inventaire;


typedef struct{
  Coordonnees coordonnees;
  Coordonnees derniereCoordonnees;
  Coordonnees initial;
  Regard regard;

  long T_dernierDeplacement;
  long T_intervalleDeplacement; // Temps nécessaire entre chaques déplacement (1s = 1 000 000) 
  int faim;
  int pvActuelle;
  int pvTotal;
  int atk;
  int vie;

  Inventaire inventaire;
}Entitee;


typedef struct{
  Entitee npc;
  int etape;
  int e_Dialogue;

  char dialogue[200];

}Quete;

// INCLUDE:
#include "map.h"
#include "main.h"
//

unsigned long getTimeMicros();

int percent(int nb, int percent);
int alea(int min, int max);

void generateMap(Map* pMap);

void createBouton(Map* pMap, int coordX, int coordY, int heigh, int width, int h_Affichage, Ressource ressource, Brush brush, char text[30]);
void createMapAccueil(Map* pMap);

void createMapOcean(Map* pMap);
void createMapMort(Map* pMap);
void createMapPaul(Map* pMap);


//res et ini
void res_Obj(Obj* pObj);
void init_Inventaire(Inventaire* pInv, int size);

Entitee* init_Entitee();
void res_Entitee(Entitee* pEnt);

Obj constructor_Obj(Id_Obj O_nom, int nb_Max, char nom[30], char symbole[10]);

ListeObj init_ListeObj();

//fonctions


void modifpvTT(int dmg_Heal, Entitee* entitee);
void modifpvA(int dmg_Heal, Entitee* entitee);

int ramasserObjet(Obj* pObj, Entitee* pJoueur);

void afficherStats(Entitee* entitee);
void testStats(Entitee* entitee);
void test();

#endif