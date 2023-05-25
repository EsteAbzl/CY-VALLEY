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

  pFenetre->ecran = ACCUEIL;

  pFenetre->camJeu = constructor_Info_Cam(16*2, 9*2); //la caméra est en 16/9 du coup (48/27)
  pFenetre->camAccueil = constructor_Info_Cam(16*2, 9*2);

  pFenetre->initialTime = 0;
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

  if( !(pJeu->pQ_Radeau = malloc(sizeof(Quete)))){
    printf("Erreur malloc pQ_Radeau");
    exit(7);
  }
  if( !(pJeu->pQ_Survivant = malloc(sizeof(Quete)))){
    printf("Erreur malloc pQ_Survivant");
    exit(7);
  }

  pJeu->listeObj = init_ListeObj();
  sprintf(pJeu->dialogue, "");
  
  pJeu->mapJeu = constructor_Map(70, 60);
  pJeu->mapAccueil = constructor_Map(16*2, 9*2);
  createMapAccueil(pJeu->mapAccueil);
  loadMapPrint(pJeu->mapAccueil);

  pJeu->enJeu = 0;
  pJeu->score = 0;
  
  pJeu->event = 0;

  return pJeu;
}


//
//RESET DES STRUCTURES
//

void res_Info_Jeu(Info_Jeu* pJeu){  
  
  pJeu->pJoueur->initial.x = 10;
  pJeu->pJoueur->initial.y = 10;
  pJeu->pJoueur->coordonnees.x = pJeu->pJoueur->initial.x;
  pJeu->pJoueur->coordonnees.y = pJeu->pJoueur->initial.y;

  pJeu->pJoueur->pvActuelle = 100;

  res_Quete(pJeu->pQ_Radeau);
  res_Quete(pJeu->pQ_Survivant);


  pJeu->listeObj = init_ListeObj();
  sprintf(pJeu->dialogue, "");

  pJeu->pJoueur->T_intervalleDeplacement = 500000; // Temps nécessaire entre chaques déplacement (1s = 1 000 000) 

  pJeu->enJeu = 1;
  pJeu->score = 0;
  
  pJeu->event = 0;
}

void debutJeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  res_Info_Jeu(pJeu);
  pFenetre->ecran = JEU;

  // Début du temps du jeu
  pFenetre->initialTime = getTimeMicros();
  pFenetre->startTime = getTimeMicros();
  
  pJeu->listeObj = init_ListeObj();
  
  generateMap(pJeu->mapJeu->pDonnees);
  loadMapPrint(pJeu->mapJeu);

  
}

void reprendreJeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  res_Info_Jeu(pJeu);
  pFenetre->ecran = JEU;

  pJeu->listeObj = init_ListeObj();
  
  generateMap(pJeu->mapJeu->pDonnees);
  loadMapPrint(pJeu->mapJeu);
}


//
//AUTRES FONCTIONS
//

void init_Curses(Info_Fenetre* pFenetre){
  printf("Locale: %s\n", setlocale(LC_ALL, "en_US.UTF-8"));
  
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
}

void freeGame(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  echo();
  endwin();

  free(pFenetre->camJeu); 
  free_Map(pJeu->mapJeu);
  free(pFenetre->camAccueil); 
  free_Map(pJeu->mapAccueil);
 
  free(pJeu->pJoueur);
  free(pJeu->pQ_Radeau);
  free(pJeu->pQ_Survivant);
  
  free(pFenetre);
  free(pJeu);
}



void affiche_jeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  Info_Cam* pCam = NULL;
  Map* pMap = NULL;
  
  switch(pFenetre->ecran){
    case ACCUEIL:
      pCam = pFenetre->camAccueil;
      pMap = pJeu->mapAccueil;
      break;
    case JEU:
      pCam = pFenetre->camJeu;
      pMap = pJeu->mapJeu;
      break;
  }

  // actualise la partie affichage de la map
  loadCamPrint(pJeu->pJoueur->coordonnees, pMap, pCam);
  
  printCam(pJeu->pJoueur->coordonnees, pMap->pAffichage, pCam);
  
  if(pFenetre->ecran == JEU){
    printStat(pFenetre, pJeu, 15);
    move(pCam->height+2, 2);
    printw("                                                                                \n");
    printw("                                                                                \n");
    printw("                                                                                \n");
    printw("                                                                                \n");

    move(pCam->height+2, 2);
    printw("%s\n", pJeu->pQ_Radeau->dialogue);
    printw("%s", pJeu->pQ_Survivant->dialogue);
  }

  gestionFps(pFenetre);
  refresh();

}

void printStat(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height){
  int colonne = pFenetre->camJeu->width*2 + 2;
  int ligne = 0;

  move(ligne, colonne); 

  ligne++;

  mvprintw(ligne, colonne, "Timer: %.5d", (int)(pFenetre->endTime - pFenetre->initialTime) /1000000);
  ligne += 2;

  mvprintw(ligne, colonne, "Score: %.5d", pJeu->score);
  ligne +=2;

  mvprintw(ligne, colonne, "PV: %d", pJeu->pJoueur->pvActuelle);
  ligne += 2;

  mvprintw(ligne, colonne, "Quête 1 dial: %d", pJeu->pQ_Radeau->e_Dialogue);
  ligne += 1;
  mvprintw(ligne, colonne, "Quête 2 dial: %d", pJeu->pQ_Survivant->e_Dialogue);
  ligne += 1;
  mvprintw(ligne, colonne, "Quête 2 etap: %d", pJeu->pQ_Survivant->etape);
  ligne += 1;
  mvprintw(ligne, colonne, "NB hache: %d", pJeu->listeObj.hache.nb);
  ligne += 1;
  mvprintw(ligne, colonne, "place inv: %d", pJeu->listeObj.baton.nb);
  ligne += 1;


  // encadré
  move(0, colonne - 1);
  printw("╦");
  for(int i = 0; i<16; i++){
    printw("═");
  }
  printw("╗");
  
  for(int i = 1; i<15; i++){
    mvprintw(i, colonne+16, "║");
  }

  move(ligne, colonne - 1);
  printw("╠");
  for(int i = 0; i<16; i++){
    printw("═");
  }
  printw("╝");
  
}

void gestionFps(Info_Fenetre* pFenetre){
  // gestion des fps
  pFenetre->endTime   = getTimeMicros();
  pFenetre->frameTime = pFenetre->endTime - pFenetre->startTime; 
  pFenetre->startTime = pFenetre->endTime;
  // Wait to achieve 60FPS
  
  if(pFenetre->frameTime <= (1000000/pFenetre->fps)){
    usleep((1000000/pFenetre->fps) - pFenetre->frameTime);
  }
}




int main(int argc, char* argv[]){
  
  
  // structures réunissants les informations importantes du programme
  Info_Fenetre* pFenetre = init_Info_Fenetre();
  Info_Jeu* pJeu = init_Info_Jeu();  

  // active les fonctionnalitées de curses
  init_Curses(pFenetre);

  // charge les infos de base avant chages partie (dont la map)
  res_Info_Jeu(pJeu); 

  
  //affiche la map entière
  //printMap(pJeu->mapJeu->pAffichage);


  while(pJeu->enJeu){// boucle du jeu

    action(pFenetre, pJeu);

    affiche_jeu(pFenetre, pJeu);
    //printw("\n*Orientation du joueur: %d", pJeu->pJoueur->regard);

    //test();
    
    //usleep(1000000);

  }


  // DESALLOCATION
  
  freeGame(pFenetre, pJeu);
  
  return 0;
}
