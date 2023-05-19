#ifndef GAME_H
#define GAME_H  

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

typedef struct{
  int x;
  int y;
}Pos;

unsigned long getTimeMicros();

#endif