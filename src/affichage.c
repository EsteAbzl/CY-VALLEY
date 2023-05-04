#include "affichage.h"



void res_Info_Cam(Info_Cam* pCam){
  pCam->width = 0;
  pCam->height = 0;

  pCam->pAffichage = NULL;
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



void loadMapPrint(Map* pMap){
  for(int y = 0; y < pMap->height; y++){
    for(int x = 0; x < pMap->width; x++){
      switch(pMap->tab[x][y].biome){
        case WATER: // eau
          
          sprintf(pMap->tab[x][y].print.back_color, "\e[48;2;%d;%d;%dm", 27, 113, 207);
          sprintf(pMap->tab[x][y].print.font_color, "");
          sprintf(pMap->tab[x][y].print.caractere, "  ");
        break;

        case SAND: // sable
          sprintf(pMap->tab[x][y].print.back_color, "\e[48;2;%d;%d;%dm", 226, 231, 50);
          sprintf(pMap->tab[x][y].print.font_color, "");
        break;
        case GRASS: // sable
          sprintf(pMap->tab[x][y].print.back_color, "\e[48;2;%d;%d;%dm", 34, 177, 76);
          sprintf(pMap->tab[x][y].print.font_color, "");
        break;
      }

      switch(pMap->tab[x][y].ressource){
          case LEAF:
            sprintf(pMap->tab[x][y].print.caractere, "🌾");
          break;
          case TREE:
            sprintf(pMap->tab[x][y].print.caractere, "🌳");
          break;
          default:
            sprintf(pMap->tab[x][y].print.caractere, "  ");
          break;
        }
      
      pMap->tab[x][y].print.isLoaded = 1;
    }
  }
}



void printCam(Pos coordonnee, Map* pMap, Info_Cam* pCam){  
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


  printf("xCam = %d/yCam = %d\n", xCam, yCam);

  printf("\e[f"); //met le curseur au début
  for(int j = 0; j<pCam->height; j++){ // y
    for(int i = 0; i<pCam->width; i++){ // x

      // affichage
      printf("%s%s %s ", pMap->tab[xCam+i][yCam+j].print.back_color, pMap->tab[xCam+i][yCam+j].print.font_color, pMap->tab[xCam+i][yCam+j].print.caractere);
    }
    printf("\n");
  }
}