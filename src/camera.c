#include "camera.h"

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

void loadMapPrint(Map* map);

void camera(Pos coordonnee, Map* pMap, Info_Cam* pCam){  
  // coordonnées du coin haut gauche de la caméra
  int xCam = -1;
  int yCam = -1;
  
  printf("x = %d/y = %d\n", coordonnee.x, coordonnee.y);

  // on place la caméra en fonction de la position du joueur par raport aux bords haut et bas de la map
  // on vérifie s'il n'est pas trop proche de l'un ou l'autre)
  if((coordonnee.y - (pCam->height/2)) < 0){
    yCam = 0;
  }
  else if((coordonnee.y + (pCam->height/2) - pMap->height) > 0){
    yCam = pMap->height - (pCam->height);
  }
  else{
    yCam = coordonnee.y - (pCam->height/2);
  }

  // on place la caméra en fonction de la position du joueur par raport aux bords gauche et droit de la map
  // (on vérifie s'il n'est pas trop proche de l'un ou l'autre)
  if((coordonnee.x - (pCam->width/2)) < 0)
    xCam = 0;
  else if((coordonnee.x + (pCam->width/2) - pMap->width) > 0)
    xCam = pMap->width - (pCam->width);
  else
    xCam -= (pCam->width/2);

  printf("xCam = %d/yCam = %d\n", xCam, yCam);
      
  for(int j = 0; j<pCam->height; j++){ // y
    for(int i = 0; i<pCam->width; i++){ // x

      // affichage
      printf("%s%s %s ", pMap->tab[xCam+i][yCam+j].print.back_color, pMap->tab[xCam+i][yCam+j].print.font_color, pMap->tab[xCam+i][yCam+j].print.caractere);
    }
    printf("\n");
  }
}