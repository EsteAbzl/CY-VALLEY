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

  pFenetre->camJeu = constructor_Info_Cam(16*2, 9*2); //la caméra est en 16/9 du coup (48/27)
  
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

  pJeu->pJoueur = init_Entitee();
  // ! \\ déplacement en fonction d'une donnée de temps: toutes les 0.5 seconde

  
  pJeu->mapJeu = constructor_Map(70, 60);;

  pJeu->enJeu = 0;
  pJeu->score = 0;
  
  pJeu->event = 0;

  return pJeu;
}


//
//RESET DES STRUCTURES
//

void res_Info_Jeu(Info_Jeu* pJeu){  
  generateMap(pJeu->mapJeu->pDonnees);
  loadMapPrint(pJeu->mapJeu);

  pJeu->pJoueur->coordonnees.x = 10;
  pJeu->pJoueur->coordonnees.y = 10;

  pJeu->enJeu = 1;
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

  // structures réunissants les informations importantes du programme
  Info_Fenetre* pFenetre = init_Info_Fenetre();
  Info_Jeu* pJeu = init_Info_Jeu();  

  // active les fonctionnalitées de curses
  init_Curses(pFenetre);


  // charge les infos de base avant chages partie (dont la map)
  res_Info_Jeu(pJeu); 
  
   
  //printMap(pMap);
  //printCam(test, pAffiMap, pCam);
  //printf("%d / %d", test.x, test.y);

  //printMap(pAffiMap);
  
  

  while(pJeu->enJeu){// boucle du jeu

    action(pFenetre, pJeu);
    
    printCam(pJeu->pJoueur->coordonnees, pJeu->mapJeu->pAffichage, pFenetre->camJeu);
    printw("\n*Orientation du joueur: %d", pJeu->pJoueur->regard);
    
    refresh();


    // gestion des fps
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

  free(pFenetre->camJeu); 
  free_Map(pJeu->mapJeu);
  
  free(pJeu->pJoueur);
  
  free(pFenetre);
  free(pJeu);
  
  return 0;
}