#include "main.h"

#include "map.h"

int main(void) {
  Pos test;
  test.x = 2;
  test.y = 3;
  
  printf("Hello World\n");
  printf("x: %d\ny: %d\n");

  int width = 20;
  int heigth = 10;

  Map **map = createMap(width, heigth);

  create_initMap(map, width, heigth);
  
  printMap(map, width, heigth);

  freeMap(map, width);
  return 0;
}