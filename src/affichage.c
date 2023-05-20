#include "affichage.h"


//
//RESET DES STRUCTURES
//

void res_Info_Cam(Info_Cam* pCam){
  pCam->width = 0;
  pCam->height = 0;

  pCam->fAffichage = NULL;
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
  
  if( !(pCam->fAffichage = fopen("data/affichage.txt", "r"))){
    printf("erreur lors de l'ouverture de 'data/affichage.txt'");
    exit(-30);
  }

  return pCam;
}

void free_Cam(Info_Cam* pCam){
  free(pCam->fAffichage);
  free(pCam);
}


//
//AUTRES FONCTIONS
//
