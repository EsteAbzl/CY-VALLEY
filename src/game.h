#ifndef GAME_H
#define GAME_H  

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