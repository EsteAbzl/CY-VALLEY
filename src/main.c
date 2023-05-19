#include "main.h"

WINDOW* init_Curses(){
  setlocale(LC_ALL, "");
  
  WINDOW* pWin = NULL;
  if( !(pWin = initscr())){
    printf("Erreur lors de initscr() !");
    exit(1);
  }

  // Paramétrage de la récupération des touches
  //noecho();
  curs_set(0);
  if(nodelay(pWin, TRUE) == ERR){
    printf("erreur lors de l'activation de halfdelay");
    endwin();
    exit(4);
  }

    
  // Création des couleurs
  start_color();
  init_Brush();

  return pWin;
}

int main(void) {

  
  WINDOW* pWin = init_Curses();

  unsigned long startTime = 0;
  unsigned long endTime   = 0;
  unsigned long frameTime = 0;

  startTime = getTimeMicros();
  
  
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

  //printMap(pAffiMap);
  
  
  int a, b, e; 
  
  int i = 0;
  getch();
  while(i<40){// future boucle de jeu
    while((e = getch()) != ERR ){
      a = e;
      b = 1;
    }
    if(b){
      b = 0;
      if(a == 'a'){  
        test.x++;
        test.y++;
        i++;
        printw("\n%d", i);
      }
    }
    printCam(test, pAffiMap, pCam);
    refresh();
  
    endTime   = getTimeMicros();
    frameTime = endTime - startTime; 
    startTime = endTime;
    // Wait to achieve 60FPS
    
    if(frameTime <= (1000000/2)){
      usleep((1000000/2)-frameTime);
    }
  }

  
  echo();
  endwin();

  free(pCam); 
  free_Donnees_Map(pInfoMap);
  free_Affichage_Map(pAffiMap);
  
  return 0;
}