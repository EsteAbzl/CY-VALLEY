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
  
  pJeu->mapJeu = constructor_Map(100, 100);
  pJeu->mapAccueil = constructor_Map(16*2, 9*2);
  createMapAccueil(pJeu->mapAccueil);
  loadMapPrint(pJeu->mapAccueil);
  pJeu->mapOcean = constructor_Map(16*2, 9*2);
  createMapOcean(pJeu->mapOcean);
  pJeu->mapMort = constructor_Map(16*2, 9*2);
  createMapMort(pJeu->mapMort);
  pJeu->mapPaul = constructor_Map(16*2, 9*2);
  createMapPaul(pJeu->mapPaul);
  

  pJeu->enJeu = 0;
  pJeu->score = 0;
  pJeu->temps = 0;
  
  pJeu->event = 0;

  pJeu->fSauvegarde = NULL;
  if( !(pJeu->fSauvegarde = fopen("data/sauvegarde.txt", "r+"))){
    printf("Erreur ouverture de data/sauvegarde.txt");
    exit(8);
  }
  pJeu->partie_sauv = 0;

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
  pJeu->pJoueur->pvTotal = 100;
  pJeu->pJoueur->vie = 2;

  init_Inventaire(&(pJeu->pJoueur->inventaire), 8);
  
  res_Quete(pJeu->pQ_Radeau);
  res_Quete(pJeu->pQ_Survivant);


  pJeu->listeObj = init_ListeObj();

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
  pFenetre->endTime = getTimeMicros();
  
  pJeu->listeObj = init_ListeObj();

  res_Donnees_Map_tab(pJeu->mapJeu->pDonnees);
  res_Affichage_Map_tab(pJeu->mapJeu->pAffichage);
  
  generateMap(pJeu->mapJeu);
  loadMapPrint(pJeu->mapJeu);

}

void reprendreJeu(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  // charge la derniere partie en cour
  res_Info_Jeu(pJeu);
  if(load_Game(pFenetre, pJeu)){
    pFenetre->ecran = JEU;
    pJeu->listeObj = init_ListeObj();
    loadMapPrint(pJeu->mapJeu);
  }
  

}


//
//AUTRES FONCTIONS
//

void save_Game(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  FILE* fS = pJeu->fSauvegarde;
  fprintf(fS, "1:%d:%d\n", pJeu->mapJeu->height, pJeu->mapJeu->width); // jeu sauvegardé
  for(int y = 0; y<pJeu->mapJeu->height; y++){
    for(int x = 0; x<pJeu->mapJeu->width; x++){
      fprintf(fS, "%d:%d/",pJeu->mapJeu->pDonnees->tab[x][y].biome, pJeu->mapJeu->pDonnees->tab[x][y].ressource);
    }
    fprintf(fS, "\n");
  }

  fprintf(fS, "%d:%d\n",pJeu->pJoueur->coordonnees.x,pJeu->pJoueur->coordonnees.y);
  fprintf(fS, "%d\n",pJeu->pJoueur->pvActuelle);

  fprintf(fS, "%d:%d\n",pJeu->pQ_Survivant->etape,pJeu->pQ_Survivant->e_Dialogue);
  fprintf(fS, "%d:%d\n",pJeu->pQ_Radeau->etape,pJeu->pQ_Radeau->e_Dialogue);
  
  fprintf(fS, "%d\n",pJeu->pJoueur->inventaire.stockagePris);
  for(int i = 0; i < pJeu->pJoueur->inventaire.stockagePris; i++){
    fprintf(fS, "%d/%d/%d/%s\n",pJeu->pJoueur->inventaire.inv[i].id_Obj, pJeu->pJoueur->inventaire.inv[i].nb, pJeu->pJoueur->inventaire.inv[i].nb_Max, pJeu->pJoueur->inventaire.inv[i].symbole);
  }

  fprintf(fS, "%d/%d/%d\n",pJeu->listeObj.coco.nb, pJeu->listeObj.coco.placeinv, pJeu->listeObj.coco.nb_Max);
  fprintf(fS, "%d/%d/%d\n",pJeu->listeObj.baton.nb, pJeu->listeObj.baton.placeinv, pJeu->listeObj.baton.nb_Max);
  fprintf(fS, "%d/%d/%d\n",pJeu->listeObj.feuille.nb, pJeu->listeObj.feuille.placeinv, pJeu->listeObj.feuille.nb_Max);
  fprintf(fS, "%d/%d/%d\n",pJeu->listeObj.caillou.nb, pJeu->listeObj.caillou.placeinv, pJeu->listeObj.caillou.nb_Max);
  fprintf(fS, "%d/%d/%d\n",pJeu->listeObj.corde.nb, pJeu->listeObj.corde.placeinv, pJeu->listeObj.corde.nb_Max);
  fprintf(fS, "%d/%d/%d\n",pJeu->listeObj.voile.nb, pJeu->listeObj.voile.placeinv, pJeu->listeObj.voile.nb_Max);
  fprintf(fS, "%d/%d/%d\n",pJeu->listeObj.hache.nb, pJeu->listeObj.hache.placeinv, pJeu->listeObj.hache.nb_Max);
  fprintf(fS, "%d/%d/%d\n",pJeu->listeObj.pioche.nb, pJeu->listeObj.pioche.placeinv, pJeu->listeObj.pioche.nb_Max);
  


  fclose(pJeu->fSauvegarde);
  pJeu->fSauvegarde = NULL;
  if( !(pJeu->fSauvegarde = fopen("data/sauvegarde.txt", "r+"))){
    printf("Erreur ouverture de data/sauvegarde.txt");
    exit(8);
  }
}

int load_Game(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  FILE* fS = pJeu->fSauvegarde;
  if(getc(fS) != '1'){
    printw("il n'y a pas de partie sauvegardée");
    return 0;
  }
  else{
    fscanf(fS, ":%d:%d\n", &pJeu->mapJeu->height, &pJeu->mapJeu->width);
    for(int y = 0; y<pJeu->mapJeu->height; y++){
      for(int x = 0; x<pJeu->mapJeu->width; x++){
        fscanf(fS, "%d:%d/", &pJeu->mapJeu->pDonnees->tab[x][y].biome, &pJeu->mapJeu->pDonnees->tab[x][y].ressource);
      }
      getc(fS);
    }

    fscanf(fS, "%d:%d\n", &pJeu->pJoueur->coordonnees.x, &pJeu->pJoueur->coordonnees.y);
    fscanf(fS, "%d\n", &pJeu->pJoueur->pvActuelle);
  
    fscanf(fS, "%d:%d\n", &pJeu->pQ_Survivant->etape, &pJeu->pQ_Survivant->e_Dialogue);
    fscanf(fS, "%d:%d\n", &pJeu->pQ_Radeau->etape, &pJeu->pQ_Radeau->e_Dialogue);

    fscanf(fS, "%d\n",&pJeu->pJoueur->inventaire.stockagePris);
    for(int i = 0; i < pJeu->pJoueur->inventaire.stockagePris; i++){
      fscanf(fS, "%d/%d/%d/%s\n",&pJeu->pJoueur->inventaire.inv[i].id_Obj, &pJeu->pJoueur->inventaire.inv[i].nb, &pJeu->pJoueur->inventaire.inv[i].nb_Max, pJeu->pJoueur->inventaire.inv[i].symbole);
    }
  
    fscanf(fS, "%d/%d/%d\n",&pJeu->listeObj.coco.nb, &pJeu->listeObj.coco.placeinv, &pJeu->listeObj.coco.nb_Max);
    fscanf(fS, "%d/%d/%d\n",&pJeu->listeObj.baton.nb, &pJeu->listeObj.baton.placeinv, &pJeu->listeObj.baton.nb_Max);
    fscanf(fS, "%d/%d/%d\n",&pJeu->listeObj.feuille.nb, &pJeu->listeObj.feuille.placeinv, &pJeu->listeObj.feuille.nb_Max);
    fscanf(fS, "%d/%d/%d\n",&pJeu->listeObj.caillou.nb, &pJeu->listeObj.caillou.placeinv, &pJeu->listeObj.caillou.nb_Max);
    fscanf(fS, "%d/%d/%d\n",&pJeu->listeObj.corde.nb, &pJeu->listeObj.corde.placeinv, &pJeu->listeObj.corde.nb_Max);
    fscanf(fS, "%d/%d/%d\n",&pJeu->listeObj.voile.nb, &pJeu->listeObj.voile.placeinv, &pJeu->listeObj.voile.nb_Max);
    fscanf(fS, "%d/%d/%d\n",&pJeu->listeObj.hache.nb, &pJeu->listeObj.hache.placeinv, &pJeu->listeObj.hache.nb_Max);
    fscanf(fS, "%d/%d/%d\n",&pJeu->listeObj.pioche.nb, &pJeu->listeObj.pioche.placeinv, &pJeu->listeObj.pioche.nb_Max);

    
    fclose(pJeu->fSauvegarde);
    pJeu->fSauvegarde = NULL;
    if( !(pJeu->fSauvegarde = fopen("data/sauvegarde.txt", "r+"))){
      printf("Erreur ouverture de data/sauvegarde.txt");
      exit(8);
    }
    return 1;
  }
}



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
  free_Map(pJeu->mapOcean);
  free_Map(pJeu->mapMort);
 
  free(pJeu->pJoueur);
  free(pJeu->pQ_Radeau);
  free(pJeu->pQ_Survivant);

  fclose(pJeu->fSauvegarde);
  
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
    case OCEAN:
      pCam = pFenetre->camAccueil;
      pMap = pJeu->mapOcean;
      break;
    case MORT:
      pCam = pFenetre->camAccueil;
      pMap = pJeu->mapMort;
      break;
    case PAUL:
      pCam = pFenetre->camAccueil;
      pMap = pJeu->mapPaul;
      break;
  }

  if(pFenetre->ecran == OCEAN){
    Coordonnees coord;
    coord.x = 16; coord.y = 9;
    printFin_Radeau(coord, pMap->pAffichage, pCam);
  }
  else if(pFenetre->ecran == MORT){
    Coordonnees coord;
    coord.x = 16; coord.y = 9;
    printFin_Mort(coord, pMap->pAffichage, pCam);
  }
  else if(pFenetre->ecran == PAUL){
    Coordonnees coord;
    coord.x = 16; coord.y = 9;
    printFin_Paul(coord, pMap->pAffichage, pCam);
  }  
  else{
    // actualise la partie affichage de la map
    loadCamPrint(pJeu->pJoueur->coordonnees, pMap, pCam);
    printCam(pJeu->pJoueur->coordonnees, pMap->pAffichage, pCam);
    
    
    if(pFenetre->ecran == JEU){
      printStat(pFenetre, pJeu, 7);
      printInv(pFenetre, pJeu, 11);
      printDialogue(pFenetre, pJeu, 6);
      
      if(pJeu->pQ_Survivant->etape == 4){
        attron(COLOR_PAIR(pMap->pAffichage->tab[pJeu->pJoueur->derniereCoordonnees.x][pJeu->pJoueur->derniereCoordonnees.y].brush));
        mvprintw((pJeu->pJoueur->derniereCoordonnees.y - pFenetre->camJeu->yCam) + 1, (pJeu->pJoueur->derniereCoordonnees.x - pFenetre->camJeu->xCam) *2 + 1, "🕺");
        attroff(COLOR_PAIR(pMap->pAffichage->tab[pJeu->pJoueur->derniereCoordonnees.x][pJeu->pJoueur->derniereCoordonnees.y].brush));
      }
    }
  }

  gestionFps(pFenetre);
  refresh();

}

void printStat(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height){
  int colonne = pFenetre->camJeu->width*2 + 2;
  int ligne = 0;
  
  move(ligne, colonne); 

  for(int i = 1; i < height; i++){
    mvprintw(ligne + i, colonne + 1, "                 ");
  }
  
  attron(COLOR_PAIR(BRUSH_STAT));
  ligne++;

  mvprintw(ligne, colonne + 1, "Timer: %05ld", pJeu->temps);
  ligne += 2;

  mvprintw(ligne, colonne + 1, "Score: %05d", pJeu->score);
  ligne +=2;

  mvprintw(ligne, colonne + 1, "PV: %03d VIE: %d", pJeu->pJoueur->pvActuelle, pJeu->pJoueur->vie);
  ligne += 2;


  attroff(COLOR_PAIR(BRUSH_STAT));


  // encadré
  move(0, colonne - 1);
  printw("╦");
  for(int i = 0; i<16; i++){
    printw("═");
  }
  printw("╗");
  
  for(int i = 1; i<height; i++){
    mvprintw(i, colonne+16, "║");
  }

  move(ligne, colonne - 1);
  printw("╠");
  for(int i = 0; i<16; i++){
    printw("═");
  }
  printw("╣");
  
}


void printInv(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height){
  int colonne = pFenetre->camJeu->width*2 + 2;
  int ligne = 8;
  
  move(ligne + 1, colonne + 1); 

  for(int i = 1; i < height; i++){
    mvprintw(ligne + i, colonne + 1, "                 ");
  }

  attron(COLOR_PAIR(COLOR_INVENTAIRE_NEUTRE));
  mvprintw(ligne, colonne + 1," INVENTAIRE:");
  for(int i = 0; i < pJeu->pJoueur->inventaire.stockagePris; i++){
    mvprintw(ligne + i + 2, colonne + 1, "%s : %d/%d", pJeu->pJoueur->inventaire.inv[i].symbole, pJeu->pJoueur->inventaire.inv[i].nb, pJeu->pJoueur->inventaire.inv[i].nb_Max);
  }
  attroff(COLOR_PAIR(COLOR_INVENTAIRE_NEUTRE));
  

  // encadré
  
  for(int i = 0; i<height; i++){
    mvprintw(ligne + i, colonne+16, "║");
  }

  move(ligne + height, colonne - 1);
  printw("╩");
  for(int i = 0; i<16; i++){
    printw("═");
  }
  printw("╣");
}


void printDialogue(Info_Fenetre* pFenetre, Info_Jeu* pJeu, int height){
  int colonne = 0;
  int ligne = pFenetre->camJeu->height + 1;
  
  move(ligne + 1, colonne + 1); 

  for(int i = 0; i < 5; i++){
    printw("                                                                                \n");
  }

  move(ligne + 1, colonne + 1);
  attron(COLOR_PAIR(BRUSH_D_RADEAU));
  printw("%s\n", pJeu->pQ_Radeau->dialogue);
  attroff(COLOR_PAIR(BRUSH_D_RADEAU));
  
  move(ligne + 3, colonne + 1);
  attron(COLOR_PAIR(BRUSH_D_PAUL));
  printw("%s", pJeu->pQ_Survivant->dialogue);
  attroff(COLOR_PAIR(BRUSH_D_PAUL));


  // encadré
  move(ligne, 0);
  printw("╠");
  for(int i = 1; i<height; i++){
    mvprintw(ligne + i, colonne, "║");
    mvprintw(ligne + i, colonne + 82, "║");
  }

  move(ligne + height, 0);
  printw("╚");
  for(int i = 0; i<81; i++){
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

    if(pFenetre->ecran == JEU){  
      pJeu->temps = (pFenetre->endTime - pFenetre->initialTime) / 1000000;
      faim(pJeu->pJoueur, pJeu->temps);
      
      death(pJeu, pFenetre);
      
      limiteScore(pJeu, pFenetre);

      if(pJeu->pQ_Radeau->etape == 4){
        fin(pJeu, pFenetre, 1);
      }
    }
    
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
