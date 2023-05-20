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
  setColor(COLOR_WATER, 27, 113, 207);
  setColor(COLOR_SAND, 226, 231, 50);
  setColor(COLOR_GRASS, 34, 177, 76);
}

void init_Brush(){
  init_Colors();
  init_pair(BRUSH_VOID, COLOR_VOID, COLOR_VOID);
  init_pair(BRUSH_WATER, COLOR_WATER, COLOR_WATER);
  init_pair(BRUSH_SAND, COLOR_VOID, COLOR_SAND);
  init_pair(BRUSH_GRASS, COLOR_VOID, COLOR_GRASS);
}


//
//RESET DES STRUCTURES
//

void res_Info_Cam(Info_Cam* pCam){
  pCam->width = 0;
  pCam->height = 0;

  pCam->pAffichage = NULL;
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
  
  if( !(pCam->pAffichage = fopen("data/affichage.txt", "r"))){
    printf("erreur lors de l'ouverture de 'data/affichage.txt'");
    exit(-30);
  }

  return pCam;
}


//
//AUTRES FONCTIONS
//

void loadMapPrint(Map* pMap){
  Donnees_Map* pDonnees_Map = pMap->pDonnees;
  Affichage_Map* pAffichage_Map = pMap->pAffichage;
  
  for(int y = 0; y < pDonnees_Map->height; y++){
    for(int x = 0; x < pDonnees_Map->width; x++){
      
      switch(pDonnees_Map->tab[x][y].biome){
        case VOID:
          pAffichage_Map->tab[x][y].brush = BRUSH_GRASS;
        break;
        case WATER: // eau
          
          pAffichage_Map->tab[x][y].brush = BRUSH_WATER;
          sprintf(pAffichage_Map->tab[x][y].caractere, "  ");
        break;

        case SAND: // sable
          pAffichage_Map->tab[x][y].brush = BRUSH_SAND;
        break;
        case GRASS: // herbe
          pAffichage_Map->tab[x][y].brush = BRUSH_GRASS;
        break;
      }

      switch(pDonnees_Map->tab[x][y].ressource){
        case EMPTY:
          sprintf(pAffichage_Map->tab[x][y].caractere, "  ");
        break;
        case LEAF:
          sprintf(pAffichage_Map->tab[x][y].caractere, "🌾");
        break;
        case TREE:
          sprintf(pAffichage_Map->tab[x][y].caractere, "🌳");
        break;
        }
      
      pAffichage_Map->tab[x][y].isLoaded = 1;
    }
  }
}


void printCam(Pos coordonnee, Affichage_Map* pAffichage_Map, Info_Cam* pCam){  
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


  move(0, 0);

  //affichage du contour haut de l'écran
  printw("╔");
  for(int i = 0; i<pCam->width*2; i++){
    printw("═");
  }
  printw("╗\n");

  
  for(int j = yCam; j<yCam + pCam->height; j++){ // y
    printw("║");
    for(int i = xCam; i<xCam + pCam->width; i++){ // x

      // affichage d'une case de la mapv
      attron(COLOR_PAIR(pAffichage_Map->tab[i][j].brush));
      printw("%s", pAffichage_Map->tab[i][j].caractere);
      attroff(COLOR_PAIR(pAffichage_Map->tab[i][j].brush));
    }
    
    //affichage des contours gauche et droit de l'écran
    printw("║\n");
  }

  //affichage du contour bas de l'écran
  printw("╚");
  for(int i = 0; i<pCam->width*2; i++){
    printw("═");
  }
  printw("╝\n");

  //affichage d'infos sur la position de la caméra

  attron(COLOR_PAIR(pAffichage_Map->tab[coordonnee.x][coordonnee.y].brush));
  mvprintw((coordonnee.y - yCam) + 1, (coordonnee.x - xCam) *2 + 1, "🧍");
  attroff(COLOR_PAIR(pAffichage_Map->tab[coordonnee.x][coordonnee.y].brush));
  move(pCam->height+2, 0);
  
  printw("\n*coin superieur gauche: xCam = %d/yCam = %d", xCam, yCam);
  printw("\n*joueur: x = %d/y = %d", coordonnee.x, coordonnee.y);
  printw("\n|joueur dans cam: x = %d/ y = %d", coordonnee.x - xCam, coordonnee.y - yCam);
  
  refresh();
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