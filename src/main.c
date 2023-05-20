#include "main.h"

void res_Info_Fenetre(Info_Fenetre* pFenetre){
  pFenetre->pWin = NULL;
  
  pFenetre->startTime = 0;
  pFenetre->endTime = 0;
  pFenetre->frameTime = 0;
  
  pFenetre->fps = 2;
}

void res_Info_Jeu(Info_Jeu* pJeu){
  pJeu->ecran = JEU;

  pJeu->event = 0;
}


void res_Map(Map* pMap){
  pMap->width = 0;
  pMap->height = 0;

  pMap->pDonnees = NULL;
  pMap->pAffichage = NULL;
}


//
//CONSTRUCTEURS DES STRUCTURES
//

Map* constructor_Map(int width, int height){
  Map* pMap = NULL;
  if( !(pMap = malloc(sizeof(Map)))){
    printf("ERREUR: pb avec le malloc de pMap");
  }

  res_Map(pMap);
  
  pMap->width = width;
  pMap->height = height;
  
  pMap->pDonnees = constructor_Donnees_Map(width, height);
  pMap->pAffichage = constructor_Affichage_Map(width, height);

  return pMap;
}

void free_Map(Map* pMap){
  free_Donnees_Map(pMap->pDonnees);
  free_Affichage_Map(pMap->pAffichage);
  free(pMap);
}


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
    printf("erreur lors de l'activation de nodelay");
    endwin();
    exit(4);
  }

    
  // Création des couleurs
  start_color();
  init_Brush();

  return pWin;
}

int main(void) {

  Info_Fenetre* pFenetre = NULL;
  if( !(pFenetre = malloc(sizeof(Info_Fenetre)))){
    printf("Erreur malloc Info_Fenetre");
    exit(5);
  }
  res_Info_Fenetre(pFenetre);

  Info_Jeu* pJeu = NULL;
  if( !(pJeu = malloc(sizeof(Info_Jeu)))){
    printf("Erreur malloc Info_Jeu");
    exit(6);
  }
  res_Info_Jeu(pJeu);
  
  
  pFenetre->pWin = init_Curses();

  pFenetre->startTime = getTimeMicros();
  
  
  Pos test;
  test.x = 10; 
  test.y = 10; 
  
  
  Map* pMap = constructor_Map(70, 60);
  Info_Cam* pCam = constructor_Info_Cam(16*2, 9*2); //la caméra est en 16/9 du coup (48/27)
   
  generateMap(pMap->pDonnees);
  loadMapPrint(pMap); 
  
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
    printCam(test, pMap->pAffichage, pCam);
    refresh();
  
    pFenetre->endTime   = getTimeMicros();
    pFenetre->frameTime = pFenetre->endTime - pFenetre->startTime; 
    pFenetre->startTime = pFenetre->endTime;
    // Wait to achieve 60FPS
    
    if(pFenetre->frameTime <= (1000000/pFenetre->fps)){
      usleep((1000000/pFenetre->fps) - pFenetre->frameTime);
    }
  }

  
  echo();
  endwin();

  free(pCam); 
  free_Map(pMap);

  free(pFenetre);
  
  return 0;
}