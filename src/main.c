#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main(void) {
  //system("chcp 65001"); A mettre sur windows
  
  Pos test;
  test.x = 2;
  test.y = 2;
  
  printf("Hello World\n");
  printf("x: %d\ny: %d\n");

  printf("\e[48;2;150;0;0m \e[38;2;100;200;100m 🌳🤙✨👍🥶😅😓❄💪💨💦🧭💭🖥🎮©🍾👩‍❤️‍👩🙂😎😊😖✈🏹🏎💩💀⬛◼◾▪🏴⚫🖤🔲🟦💙🔵🔷🔹🍀🌿🌾🌴🌳🍃🍁🍂🌲🌱⛏ 🛡 ⚔\n");

  
  
  Map* pMap = constructor_Map(70, 70);
  Info_Cam* pCam = constructor_Info_Cam(25, 15);

  generateMap(pMap);
  loadMapPrint(pMap);
  
  printMap(pMap);
  //camera(test, pMap, pCam);
  

/*
  for(int i = 0; i<10; i++){
    printMap(pMap);
    printf("%d", i);
  }*/

  free(pCam);
  free_Map(pMap);
  
  return 0;
}