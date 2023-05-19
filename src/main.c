#include "main.h"

int main(void) {
  //system("chcp 65001"); A mettre sur windows
  
  Pos test;
  test.x = 10; 
  test.y = 10;
   
  
  Map* pMap = constructor_Map(70, 70);
  Info_Cam* pCam = constructor_Info_Cam(16*3, 9*3); //la caméra est en 16/9 du coup (48/27)

  generateMap(pMap);
  loadMapPrint(pMap);

  JOUEUR j1;
  JOUEUR* pJoueur = &j1;
  j1.posJoueur.x = 4;
  j1.posJoueur.y = 4;
  
  printf("(%d,%d)", j1.posJoueur.x, j1.posJoueur.y);
  deplacementJoueur(pJoueur);
  printf("(%d,%d)", j1.posJoueur.x, j1.posJoueur.y);
  
  
  //printMap(pMap);
  
  //printCam(test, pMap, pCam);
  //printf("%d / %d\n", test.x, test.y);


  
  /*  
  int a;
  scanf("%d", &a);
  for(int i = 0; i<40; i++){
    printCam(test, pMap, pCam);
    test.x++;
    test.y++;
    printf("%d / %d", test.x, test.y);
  }*/


  free_Cam(pCam);
  free_Map(pMap);
  
  return 0;
}