#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int x;
  int y;
}POSITION;

typedef struct{
  /*char nom[100];
  int PV;
  int ATK;
  int DEF;*/
  POSITION posJoueur;
}JOUEUR;

void deplacementJoueur(JOUEUR* pJoueur);
