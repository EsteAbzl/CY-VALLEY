#include "main.h"

int main(void) {
  setlocale(LC_ALL, "");

  WINDOW* pWin = NULL;
  if( !(pWin = initscr())){
    printf("Erreur lors de initscr() !");
    exit(1);
  }

  start_color();
  init_Brush();
  /*
  //init_color(1, 200, 100, 100);
  init_color(2, 100, 200, 100);
  
short r, g, b;
  color_content(1, &r, &g, &b);
printw("%d\n1: %d, %d, %d", COLORS, r, g, b);
  init_pair(0, 1, 2);*/
  /*int i;
  printw("\n");
  for(i = 0; i < 250; i++){
    //init_color(1, 2, i*4, i*4);
    init_pair(i, 2, 1);
    attron(COLOR_PAIR(i));
    printw("XX");
    if(!(i%15)) printw("\n");
    refresh();
    
  }
  
    
  
  printw("Le terminal actuel comporte %d lignes et %d colonnes\n", LINES, COLS);
  printw(" 😂 ❤♥💘💝💝");*/
  
  
  Pos test;
  test.x = 10; 
  test.y = 10; 
  
  
  Donnees_Map* pInfoMap = constructor_Donnees_Map(70, 60);
  Affichage_Map* pAffiMap = constructor_Affichage_Map(70, 60);
  Info_Cam* pCam = constructor_Info_Cam(16*2, 9*2); //la caméra est en 16/9 du coup (48/27)
   
  generateMap(pInfoMap);
  loadMapPrint(pInfoMap, pAffiMap); 
  
  //printMap(pMap);
  //printCam(test, pAffiMap, pCam);
  //printf("%d / %d", test.x, test.y);

  printMap(pAffiMap);
  
  
  int a; 
  getch();
  for(int i = 0; i<50; i++){
    printCam(test, pAffiMap, pCam);
    test.x++;
    test.y++;
    refresh();
  }

  refresh();
  getch();
  endwin();


  free(pCam); 
  free_Donnees_Map(pInfoMap);
  free_Affichage_Map(pAffiMap);
  
  return 0;
}