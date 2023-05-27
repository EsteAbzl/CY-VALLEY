#include "affichage.h"




//
//INIT COULEUR ET BROSSES
//

void setColor(unsigned char id, unsigned char r, unsigned char g, unsigned char b){
  int rr = (1000*r)/255;
  int gg = (1000*g)/255;
  int bb = (1000*b)/255;
  init_color(id, rr, gg, bb);
}

void init_Colors(){
  setColor(COLOR_VOID, 10, 10, 10);
  setColor(COLOR_WATER, 47, 223, 219);
  setColor(BRUSH_DEEP_WATER, 24, 120, 177);
  setColor(COLOR_SAND, 226, 231, 50);
  setColor(COLOR_GRASS, 34, 177, 76);

  setColor(COLOR_BOIS, 128, 64, 0);
  setColor(COLOR_STONE, 180, 180, 180);

  setColor(COLOR_STAT, 205, 163, 75);
  setColor(COLOR_INVENTAIRE_NEUTRE, 125, 196, 100);
  setColor(COLOR_INVENTAIRE_ACTIF, 205, 163, 75);
  setColor(COLOR_D_RADEAU, 231, 205, 148);
  setColor(COLOR_D_PAUL, 142, 180, 234);

  setColor(COLOR_TOUCHE, 140, 99, 57);
  setColor(COLOR_NOUVEAU_JEU, 149, 236, 184);
  setColor(COLOR_REPRENDRE_JEU, 140, 230, 180);
  setColor(COLOR_QUITTER_JEU, 200, 100, 95);
  
  setColor(COLOR_TERMINAL, 96, 176, 185);
}

void init_Brush(){
  init_Colors();
  init_pair(BRUSH_VOID, COLOR_VOID, COLOR_VOID);
  init_pair(BRUSH_WATER, COLOR_WATER, COLOR_WATER);
  init_pair(BRUSH_DEEP_WATER, COLOR_VOID, COLOR_DEEP_WATER);
  init_pair(BRUSH_SAND, COLOR_VOID, COLOR_SAND);
  init_pair(BRUSH_GRASS, COLOR_VOID, COLOR_GRASS);

  init_pair(BRUSH_BOIS, COLOR_BOIS, COLOR_GRASS);
  init_pair(BRUSH_STONE, COLOR_STONE, COLOR_GRASS);

  init_pair(BRUSH_STAT, COLOR_STAT, COLOR_VOID);
  
  init_pair(BRUSH_INVENTAIRE_NEUTRE, COLOR_INVENTAIRE_NEUTRE, COLOR_VOID);
  init_pair(BRUSH_INVENTAIRE_ACTIF, COLOR_INVENTAIRE_ACTIF, COLOR_VOID);
  
  init_pair(BRUSH_D_RADEAU, COLOR_D_RADEAU, COLOR_VOID);
  init_pair(BRUSH_D_PAUL, COLOR_D_PAUL, COLOR_VOID);

  init_pair(BRUSH_TOUCHE, COLOR_STAT, COLOR_TOUCHE);
  init_pair(BRUSH_NOUVEAU_JEU, COLOR_VOID, COLOR_NOUVEAU_JEU);
  init_pair(BRUSH_REPRENDRE_JEU, COLOR_VOID, COLOR_REPRENDRE_JEU);
  init_pair(BRUSH_QUITTER_JEU, COLOR_VOID, COLOR_QUITTER_JEU);
}


//
//RESET DES STRUCTURES
//

void res_Info_Cam(Info_Cam* pCam){
  pCam->width = 0;
  pCam->height = 0;

  pCam->xCam = 0;
  pCam->yCam = 0;
}


//
//CONSTRUCTEURS DES STRUCTURES
//

Info_Cam* constructor_Info_Cam(int width, int height){
  Info_Cam* pCam = NULL;
  if( !(pCam = malloc(sizeof(Info_Cam)))){
    printf("ERREUR: pb avec le malloc de pCam");
  }
  
  res_Info_Cam(pCam);

  pCam->width = width;
  pCam->height = height;

  return pCam;
}


//
//AUTRES FONCTIONS
//

void loadPrint(CaseMap caseMap, Print* pPrint){
  if(pPrint->isLoaded == 0){
    switch(caseMap.biome){
      case VOID:
        pPrint->brush = BRUSH_GRASS;
      break;
      case WATER: // eau
        
        pPrint->brush = BRUSH_WATER;
      break;
      case DEEP_WATER: // eau
        
        pPrint->brush = BRUSH_DEEP_WATER;
      break;  
      case SAND: // sable
        pPrint->brush = BRUSH_SAND;
      break;
      case GRASS: // herbe
        pPrint->brush = BRUSH_GRASS;
      break;
    }
  
    switch(caseMap.ressource){
      case EMPTY:
        if(!(rand()%100)){
          sprintf(pPrint->caractere, "░░");
        }
        else if(!(rand()%40)){
          sprintf(pPrint->caractere, "⚘ ");
        }
        else{
          sprintf(pPrint->caractere, "  ");
        }
      break;
      case WAVE:
        if(!(rand()%40)){
          sprintf(pPrint->caractere, "🌊");
        }
        else if(!(rand()%30)){
          sprintf(pPrint->caractere, " ≋");
        }
        else{
          sprintf(pPrint->caractere, "  ");
        }
      break;
      
      case TREE:
        sprintf(pPrint->caractere, "🌴");
      break;
      case BATON:
        sprintf(pPrint->caractere, "▂ ");
        pPrint->brush = BRUSH_BOIS;
      break;
      case COCO:
        sprintf(pPrint->caractere, "🥥");
      break;
      case LEAF:
        sprintf(pPrint->caractere, "🍃");
      break;
      case ROCHER:
        sprintf(pPrint->caractere, "⛰ ");
        pPrint->brush = BRUSH_STONE;
      break;
      case CAILLOU:
        sprintf(pPrint->caractere, "☁ ");
        pPrint->brush = BRUSH_STONE;
      break;
      case PNG_PAUL:
        sprintf(pPrint->caractere, "🕺");
      break;
      case PNG_BOAT:
        sprintf(pPrint->caractere, "⛵");
      break;
      case HACHE:
        sprintf(pPrint->caractere, "🪓");
      break;
      case PIOCHE:
        sprintf(pPrint->caractere, "⛏ ");
      break;
    }
    
    pPrint->isLoaded = 1;
  }
  
}

void loadMapPrint(Map* pMap){
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;
  
  for(int y = 0; y < pDonnees_Map->height; y++){
    for(int x = 0; x < pDonnees_Map->width; x++){
      
      loadPrint(pDonnees_Map->tab[x][y], &(pAffichage_Map->tab[x][y]));
    }
  }
}

void loadCamPrint(Coordonnees coordonnee, Map* pMap, Info_Cam* pCam){  
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;
  // coordonnées du coin haut gauche de la caméra
  pCam->xCam = -1;
  pCam->yCam = -1;

  // on place la caméra en fonction de la position du joueur par raport aux bords de la map
  // on vérifie s'il n'est pas trop proche)
  // xCam
  if((coordonnee.x - (pCam->width/2)) < 0) // trop a gauche
    pCam->xCam = 0;
  else if((coordonnee.x + (pCam->width/2) - pAffichage_Map->width) > 0) // trop a droite
    pCam->xCam = pAffichage_Map->width - (pCam->width);
  else
    pCam->xCam = coordonnee.x - (pCam->width/2);

  // yCam
  if((coordonnee.y - (pCam->height/2)) < 0)
    pCam->yCam = 0;
  else if((coordonnee.y + (pCam->height/2) - pAffichage_Map->height) > 0)
    pCam->yCam = pAffichage_Map->height - (pCam->height);
  else
    pCam->yCam = coordonnee.y - (pCam->height/2);

  for(int j = pCam->yCam; j<pCam->yCam + pCam->height; j++){ // y
    for(int i = pCam->xCam; i<pCam->xCam + pCam->width; i++){ // x

      loadPrint(pDonnees_Map->tab[i][j], &(pAffichage_Map->tab[i][j]));
    }
  }
}


void printCam(Coordonnees coordonnee, Affichage_Map* pAffichage_Map, Info_Cam* pCam){  
  int ligne = 0;
  
  // coordonnées du coin haut gauche de la caméra
  int xCam = -1;
  int yCam = -1;

  // on place la caméra en fonction de la position du joueur par raport aux bords de la map
  // on vérifie s'il n'est pas trop proche)
  // xCam
  if((coordonnee.x - (pCam->width/2)) < 0) // trop a gauche
    xCam = 0;
  else if((coordonnee.x + (pCam->width/2) - pAffichage_Map->width) > 0) // trop a droite
    xCam = pAffichage_Map->width - (pCam->width);
  else
    xCam = coordonnee.x - (pCam->width/2);

  // yCam
  if((coordonnee.y - (pCam->height/2)) < 0)
    yCam = 0;
  else if((coordonnee.y + (pCam->height/2) - pAffichage_Map->height) > 0)
    yCam = pAffichage_Map->height - (pCam->height);
  else
    yCam = coordonnee.y - (pCam->height/2);


  move(ligne, 0);
  attron(COLOR_PAIR(COLOR_VOID));

  //affichage du contour haut de l'écran
  printw("╔");
  for(int i = 0; i<pCam->width*2; i++){
    printw("═");
  }
  printw("╗");

  ligne++;

  
  for(int j = yCam; j<yCam + pCam->height; j++){ // y
    mvprintw(ligne, 0, "║");
    for(int i = xCam; i<xCam + pCam->width; i++){ // x

      // affichage d'une case de la mapv
      attron(COLOR_PAIR(pAffichage_Map->tab[i][j].brush));
      printw("%s", pAffichage_Map->tab[i][j].caractere);
      attroff(COLOR_PAIR(pAffichage_Map->tab[i][j].brush));
    }
    
    //affichage des contours gauche et droit de l'écran
    printw("║");
    ligne++;
  }

  move(ligne, 0);
  //affichage du contour bas de l'écran
  printw("╚");
  for(int i = 0; i<pCam->width*2; i++){
    printw("═");
  }
  printw("╝");

  //affichage d'infos sur la position de la caméra

  attron(COLOR_PAIR(pAffichage_Map->tab[coordonnee.x][coordonnee.y].brush));
  mvprintw((coordonnee.y - yCam) + 1, (coordonnee.x - xCam) *2 + 1, "🧍");
  attroff(COLOR_PAIR(pAffichage_Map->tab[coordonnee.x][coordonnee.y].brush));
  
  
  move(pCam->height+5, 0);
  //printw("\n*coin superieur gauche: xCam = %d/yCam = %d", xCam, yCam);
  //printw("\n*joueur: x = %d/y = %d", coordonnee.x, coordonnee.y);
  //printw("\n|joueur dans cam: x = %d/ y = %d", coordonnee.x - xCam, coordonnee.y - yCam);
  
}


void printFin_Radeau(Coordonnees coordonnee, Affichage_Map* pAffichage_Map, Info_Cam* pCam){  
  int ligne = 0;
  
  // coordonnées du coin haut gauche de la caméra
  int xCam = -1;
  int yCam = -1;

  // on place la caméra en fonction de la position du joueur par raport aux bords de la map
  // on vérifie s'il n'est pas trop proche)
  // xCam
  if((coordonnee.x - (pCam->width/2)) < 0) // trop a gauche
    xCam = 0;
  else if((coordonnee.x + (pCam->width/2) - pAffichage_Map->width) > 0) // trop a droite
    xCam = pAffichage_Map->width - (pCam->width);
  else
    xCam = coordonnee.x - (pCam->width/2);

  // yCam
  if((coordonnee.y - (pCam->height/2)) < 0)
    yCam = 0;
  else if((coordonnee.y + (pCam->height/2) - pAffichage_Map->height) > 0)
    yCam = pAffichage_Map->height - (pCam->height);
  else
    yCam = coordonnee.y - (pCam->height/2);


  move(ligne, 0);
  attron(COLOR_PAIR(COLOR_VOID));

  //affichage du contour haut de l'écran
  printw("╔");
  for(int i = 0; i<pCam->width*2; i++){
    printw("═");
  }
  printw("╗");

  ligne++;

  
  for(int j = yCam; j<yCam + pCam->height; j++){ // y
    mvprintw(ligne, 0, "║");
    for(int i = xCam; i<xCam + pCam->width; i++){ // x

      // affichage d'une case de la mapv
      attron(COLOR_PAIR(pAffichage_Map->tab[i][j].brush));
      printw("%s", pAffichage_Map->tab[i][j].caractere);
      attroff(COLOR_PAIR(pAffichage_Map->tab[i][j].brush));
    }
    
    //affichage des contours gauche et droit de l'écran
    printw("║");
    ligne++;
  }

  move(ligne, 0);
  //affichage du contour bas de l'écran
  printw("╚");
  for(int i = 0; i<pCam->width*2; i++){
    printw("═");
  }
  printw("╝");

  //affichage d'infos sur la position de la caméra

  attron(COLOR_PAIR(pAffichage_Map->tab[coordonnee.x][coordonnee.y].brush));
  mvprintw((coordonnee.y - yCam) + 1, (coordonnee.x - xCam) *2 + 1, "⛵");
  attroff(COLOR_PAIR(pAffichage_Map->tab[coordonnee.x][coordonnee.y].brush));
  
  
  move(pCam->height+5, 0);
  printw("\n*coin superieur gauche: xCam = %d/yCam = %d", xCam, yCam);
  printw("\n*joueur: x = %d/y = %d", coordonnee.x, coordonnee.y);
  printw("\n|joueur dans cam: x = %d/ y = %d", coordonnee.x - xCam, coordonnee.y - yCam);
  
}

void printFin_Mort(Coordonnees coordonnee, Affichage_Map* pAffichage_Map, Info_Cam* pCam){  
  int ligne = 0;
  
  // coordonnées du coin haut gauche de la caméra
  int xCam = -1;
  int yCam = -1;

  // on place la caméra en fonction de la position du joueur par raport aux bords de la map
  // on vérifie s'il n'est pas trop proche)
  // xCam
  if((coordonnee.x - (pCam->width/2)) < 0) // trop a gauche
    xCam = 0;
  else if((coordonnee.x + (pCam->width/2) - pAffichage_Map->width) > 0) // trop a droite
    xCam = pAffichage_Map->width - (pCam->width);
  else
    xCam = coordonnee.x - (pCam->width/2);

  // yCam
  if((coordonnee.y - (pCam->height/2)) < 0)
    yCam = 0;
  else if((coordonnee.y + (pCam->height/2) - pAffichage_Map->height) > 0)
    yCam = pAffichage_Map->height - (pCam->height);
  else
    yCam = coordonnee.y - (pCam->height/2);


  move(ligne, 0);
  attron(COLOR_PAIR(COLOR_VOID));

  //affichage du contour haut de l'écran
  printw("╔");
  for(int i = 0; i<pCam->width*2; i++){
    printw("═");
  }
  printw("╗");

  ligne++;

  
  for(int j = yCam; j<yCam + pCam->height; j++){ // y
    mvprintw(ligne, 0, "║");
    for(int i = xCam; i<xCam + pCam->width; i++){ // x

      // affichage d'une case de la mapv
      attron(COLOR_PAIR(pAffichage_Map->tab[i][j].brush));
      printw("%s", pAffichage_Map->tab[i][j].caractere);
      attroff(COLOR_PAIR(pAffichage_Map->tab[i][j].brush));
    }
    
    //affichage des contours gauche et droit de l'écran
    printw("║");
    ligne++;
  }

  move(ligne, 0);
  //affichage du contour bas de l'écran
  printw("╚");
  for(int i = 0; i<pCam->width*2; i++){
    printw("═");
  }
  printw("╝");

  //affichage d'infos sur la position de la caméra

  attron(COLOR_PAIR(pAffichage_Map->tab[coordonnee.x][coordonnee.y].brush));
  mvprintw((coordonnee.y - yCam) + 1, (coordonnee.x - xCam) *2 + 1, "☠");
  attroff(COLOR_PAIR(pAffichage_Map->tab[coordonnee.x][coordonnee.y].brush));
  
  
  move(pCam->height+5, 0);
  printw("\n*coin superieur gauche: xCam = %d/yCam = %d", xCam, yCam);
  printw("\n*joueur: x = %d/y = %d", coordonnee.x, coordonnee.y);
  printw("\n|joueur dans cam: x = %d/ y = %d", coordonnee.x - xCam, coordonnee.y - yCam);
  
}

void printMap(Affichage_Map* pAffichage_Map){
  move(0, 0);
  
  for (int y = 0; y < pAffichage_Map->height; y++) {
    for (int x = 0; x < pAffichage_Map->width; x++) {
      attron(COLOR_PAIR(pAffichage_Map->tab[x][y].brush));
      printw("%s", pAffichage_Map->tab[x][y].caractere);
      attroff(COLOR_PAIR(pAffichage_Map->tab[x][y].brush));
    }// x
    printw("\n");
  }// y

  refresh();
}

