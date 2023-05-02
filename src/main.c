#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "map.h"

int main(void) {
  //system("chcp 65001"); A mettre sur windows
  
  Pos test;
  test.x = 2;
  test.y = 3;
  
  printf("Hello World\n");
  printf("x: %d\ny: %d\n");

  printf("\e[48;2;150;0;0m \e[38;2;100;200;100m 🌳🤙✨👍🥶😅😓❄💪💨💦🧭💭🖥🎮©🍾👩‍❤️‍👩🙂😎😊😖✈🏹🏎💩💀⬛◼◾▪🏴⚫🖤🔲🟦💙🔵🔷🔹🍀🌿🌾🌴🌳🍃🍁🍂🌲🌱⛏ 🛡 ⚔\n");

  
  
  int width = 30;
  int heigth = 15;
  
  Map* pMap = NULL;
  pMap = constructor_Map(width, heigth);


  for(int i = 0; i<10; i++){
    printMap(pMap);
    printf("%d", i);
  }

  free_Map(pMap);
  return 0;
}