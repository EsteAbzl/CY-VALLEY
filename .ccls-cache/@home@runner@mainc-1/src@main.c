#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "map.h"

int main(void) {
  Pos test;
  test.x = 2;
  test.y = 3;
  
  printf("Hello World\n");
  printf("x: %d\ny: %d\n");

  printf("\e[43;96m🌳🤙✨👍");
  
  int width = 20;
  int heigth = 30;

  Map map;
  res_Map(&map);

  createMap(&map, width, heigth);


  printMap(map);

  freeMap(map);
  return 0;
}