#ifndef GAME_H
#define GAME_H  

#include <stdlib.h>
#include <stdio.h>


typedef struct{
  int x;
  int y;
}Pos;
//stats des objet, si nourritures heal cbm de vie, le reste est logique.
typedef struct{
  int pvbuff;
  int atkbuff;
  int heal;
}buffobj;

typedef struct{
  int nbobj;
  char tab[30];
  int nbmax;
  int nbact;
  buffobj stats;
}Obj;

#endif