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
  int pv_Buff;
  int atk_Buff;
  int heal;
  int estEquipe;
}BuffObj;

typedef struct{
  int id_Obj;
  int nb_Max;
  int nb;
  int placeinv;
  BuffObj buffObj;
  
  char nom[30];
}Obj;


void res_BuffObj(BuffObj* pBuffObj);
void res_Obj(Obj* pObj);

#endif