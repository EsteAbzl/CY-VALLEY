#include "main.h"


//
//INIT DES STRUCTURES
//

Info_Fenetre* init_Info_Fenetre(){

  Info_Fenetre* pFenetre = NULL;
  if( !(pFenetre = malloc(sizeof(Info_Fenetre)))){
    printf("Erreur malloc Info_Fenetre");
    exit(5);
  }
  
  pFenetre->pWin = NULL;

  pFenetre->ecran = JEU;
  
  pFenetre->startTime = 0;
  pFenetre->endTime = 0;
  pFenetre->frameTime = 0;
  
  pFenetre->fps = 2;

  return pFenetre;
}

Info_Jeu* init_Info_Jeu(){

  Info_Jeu* pJeu = NULL;
  if( !(pJeu = malloc(sizeof(Info_Jeu)))){
    printf("Erreur malloc Info_Jeu");
    exit(6);
  }
  
  pJeu->score = 0;
  
  pJeu->event = 0;

  return pJeu;
}


//
//RESET DES STRUCTURES
//

void res_Info_Jeu(Info_Jeu* pJeu){  
  pJeu->score = 0;
  
  pJeu->event = 0;
}


//
//AUTRES FONCTIONS
//

void init_Curses(Info_Fenetre* pFenetre){
  setlocale(LC_ALL, "");
  
  if( !(pFenetre->pWin = initscr())){
    printf("Erreur lors de initscr() !");
    exit(1);
  }

  // Paramétrage de la récupération des touches
  noecho();
  curs_set(0);
  if(nodelay(pFenetre->pWin, TRUE) == ERR){
    printf("erreur lors de l'activation de nodelay");
    endwin();
    exit(4);
  }

    
  // Création des couleurs
  start_color();
  init_Brush();

  // début du temps du jeu
  pFenetre->startTime = getTimeMicros();
}


int main(int argc, char* argv[]){

  Info_Fenetre* pFenetre = init_Info_Fenetre();

  Info_Jeu* pJeu = init_Info_Jeu();  
  
  init_Curses(pFenetre);

  
  
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


  // DESALLOCATION
  
  echo();
  endwin();

  free(pCam); 
  free_Map(pMap);

  free(pFenetre);
  free(pJeu);
  
  return 0;
}