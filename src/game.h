#ifndef GAME_H
#define GAME_H  

#include <stdlib.h>
#include <stdio.h>


typedef struct{
  int x;
  int y;
}Pos;

typedef struct{
  int nbobj;
  char tab[30];
  int nbmax;
  int nbact;
}Obj;

#endif