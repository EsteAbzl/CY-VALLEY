#include "affichage.h"


//
//INIT COULEUR ET BROSSES
//

void put_rgb_color(short id, int r, int g, int b){
  init_color(id, r, g, b);  
  printf("%d, %d, %d:", r*4, g*4, b*4);
  color_content(id, &r, &g, &b);
  printf("%d, %d, %d\n", r*4, g*4, b*4);
  
}

void init_Colors(){
  put_rgb_color(COLOR_VOID, 10, 10, 10);
  put_rgb_color(COLOR_WATER, 27, 113, 207);
  put_rgb_color(COLOR_SAND, 226, 231, 50);
  put_rgb_color(COLOR_GRASS, 34, 177, 76);
}

void init_Brush(){
  init_pair(BRUSH_VOID, COLOR_VOID, COLOR_VOID);
  init_pair(BRUSH_WATER, COLOR_WATER, COLOR_WATER);
  init_pair(BRUSH_SAND, COLOR_VOID, COLOR_SAND);
  init_pair(BRUSH_GRASS, COLOR_VOID, COLOR_GRASS);
}


//
//RESET DES STRUCTURES
//

void res_Print(Print* pPrint){
  sprintf(pPrint->caractere, "  ");
  
  pPrint->brush = BRUSH_VOID;
 
  pPrint->isLoaded = 0;
}

void res_Affichage_Map_tab(Affichage_Map* pAffichage_Map){
  for(int x=0; x < pAffichage_Map->width; x++){
    for(int y=0; y < pAffichage_Map->height; y++){
      res_Print(&(pAffichage_Map->tab[x][y]));
    }
  }
}

void res_Affichage_Map(Affichage_Map* pAffichage_Map){
  pAffichage_Map->width = 0;
  pAffichage_Map->height = 0;
  pAffichage_Map->tab = NULL;
}


void res_Info_Cam(Info_Cam* pCam){
  pCam->width = 0;
  pCam->height = 0;

  pCam->pAffichage = NULL;
}


//
//CONSTRUCTEURS DES STRUCTURES
//

Print** constructor_Affichage_Map_tab(int width, int height){
  Print** tab = NULL;

  if( !(tab = calloc(width, width * sizeof(Print *)))) {
    printf("ERREUR: pb avec le malloc de tab");
  }

  for(int x = 0; x < width; x++) {
    if( !(tab[x] = calloc(height, height * sizeof(Print)))) {
      printf("ERREUR: pb avec le malloc de tab[x]");
    }
  }

  return tab;
}

Affichage_Map* constructor_Affichage_Map(int width, int height){
  
  Affichage_Map* pAffichage_Map = NULL;
  if( !(pAffichage_Map = malloc(sizeof(Affichage_Map)))){
    printf("ERREUR: pb avec le malloc de pMap");
  }

  res_Affichage_Map(pAffichage_Map);
  
  pAffichage_Map->width = width;
  pAffichage_Map->height = height;
  
  pAffichage_Map->tab = constructor_Affichage_Map_tab(width, height);
  res_Affichage_Map_tab(pAffichage_Map);

  return pAffichage_Map;
}


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


void free_Affichage_Map(Affichage_Map* pAffichage_Map){
  for (int x = 0; x < pAffichage_Map->width; x++) {
    free(pAffichage_Map->tab[x]);
  }
  free(pAffichage_Map->tab);
  free(pAffichage_Map);
}


//
//AUTRES FONCTIONS
//

void loadMapPrint(Donnees_Map* pDonnees_Map, Affichage_Map* pAffichage_Map){
  for(int y = 0; y < pDonnees_Map->height; y++){
    for(int x = 0; x < pDonnees_Map->width; x++){
      
      switch(pDonnees_Map->tab[x][y].biome){
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
          case LEAF:
            sprintf(pAffichage_Map->tab[x][y].caractere, "🌾");
          break;
          case TREE:
            sprintf(pAffichage_Map->tab[x][y].caractere, "🌳");
          break;
          default:
            sprintf(pAffichage_Map->tab[x][y].caractere, "  ");
          break;
        }
      
      pAffichage_Map->tab[x][y].isLoaded = 1;
    }
  }
}


/*
void printCam(Pos coordonnee, Affichage_Map* pAffichage_Map, Info_Cam* pCam){  
  // coordonnées du coin haut gauche de la caméra
  int xCam = -1;
  int yCam = -1;
  
  printf("x = %d/y = %d\n", coordonnee.x, coordonnee.y);

  // on place la caméra en fonction de la position du joueur par raport aux bords de la map
  // on vérifie s'il n'est pas trop proche)
  // xCam
  if((coordonnee.x - (pCam->width/2)) < 0) // trop a gauche
    xCam = 0;
  else if((coordonnee.x + (pCam->width/2) - pMap->width) > 0) // trop a droite
    xCam = pMap->width - (pCam->width);
  else
    xCam = coordonnee.x - (pCam->width/2);

  // yCam
  if((coordonnee.y - (pCam->height/2)) < 0)
    yCam = 0;
  else if((coordonnee.y + (pCam->height/2) - pMap->height) > 0)
    yCam = pMap->height - (pCam->height);
  else
    yCam = coordonnee.y - (pCam->height/2);


  printf("\e[f"); //met le curseur au début
  printf("\e[0m");

  //affichage du contour haut de l'écran
  printf("╔");
  for(int i = 0; i<pCam->width*2; i++){
    printf("═");
  }
  printf("╗\n");

  
  for(int j = 0; j<pCam->height; j++){ // y
    printf("║");
    for(int i = 0; i<pCam->width; i++){ // x

      // affichage d'une case de la mapv
      printf("%s%s%s", pMap->tab[xCam+i][yCam+j].print.back_color, pMap->tab[xCam+i][yCam+j].print.font_color, pMap->tab[xCam+i][yCam+j].print.caractere);
    }
    
    //affichage des contours gauche et droit de l'écran
    printf("\e[0m");
    printf("║\n");
  }

  //affichage du contour bas de l'écran
  printf("╚");
  for(int i = 0; i<pCam->width*2; i++){
    printf("═");
  }
  printf("╝\n");

  //affichage d'infos sur la position de la caméra
  printf("xCam = %d/yCam = %d\n", xCam, yCam);
}*/

void printMap(Affichage_Map* pAffichage_Map){
  move(0, 0);
  
  for (int y = 0; y < pAffichage_Map->height; y++) {
    for (int x = 0; x < pAffichage_Map->width; x++) {
      attron(COLOR_PAIR(pAffichage_Map->tab[x][y].brush));
      printw("%d,%s", pAffichage_Map->tab[x][y].brush, pAffichage_Map->tab[x][y].caractere);
      attroff(COLOR_PAIR(pAffichage_Map->tab[x][y].brush));
    }// x
    printw("\n");
  }// y
}