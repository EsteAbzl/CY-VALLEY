#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main(void) {
  //system("chcp 65001"); A mettre sur windows
  
  Pos test;
  test.x = 10;
  test.y = 10;
  
  printf("Hello World\n");
  printf("x: %d\ny: %d\n");

  printf("\e[48;2;150;0;0m \e[38;2;100;200;100m 🌳🤙✨👍🥶😅😓❄💪💨💦🧭💭🖥🎮©🍾👩‍❤️‍👩🙂😎😊😖✈🏹🏎💩💀⬛◼◾▪🏴⚫🖤🔲🟦💙🔵🔷🔹🍀🌿🌾🌴🌳🍃🍁🍂🌲🌱⛏ 🛡 ⚔\n");

  
  
  Map* pMap = constructor_Map(70, 60);
  Info_Cam* pCam = constructor_Info_Cam(10, 10);

  generateMap(pMap);
  loadMapPrint(pMap);
    
  printMap(pMap);
  //printCam(test, pMap, pCam);

  
  /*
int a;
scanf("%d", &a);
  for(int i = 0; i<40; i++){
    printCam(test, pMap, pCam);
    test.x++;
    test.y++;
    printf("%d / %d", test.x, test.y);
  }*/


  free(pCam);
  free_Map(pMap);
  
  return 0;
}