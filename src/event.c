#include "event.h"

int getEvent(Info_Jeu* pJeu){
  int nouvelEvent = 0;
  int event = 0;
  while((event = getch()) != ERR ){
    pJeu->event = toupper(event);
    nouvelEvent = 1;
  }

  return nouvelEvent;
}


void action(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  Entitee* pJoueur = pJeu->pJoueur;
  
  if(getEvent(pJeu)){
    switch (pJeu->event){
      case 'Z':
        pJoueur->regard = HAUT;
        
        deplacer(pJeu);
        break;
      case 'S':
        pJoueur->regard = BAS;

        deplacer(pJeu);
        break;
      case 'Q':
        pJoueur->regard = GAUCHE;

        deplacer(pJeu);
        break;
      case 'D':
        pJoueur->regard = DROITE;

        deplacer(pJeu);
        break;
      case 'A':
        pJeu->enJeu = 0;
        break;
    }
    
  }
}



int peutPasser(CaseMap caseMap){
  int traversable = 1;
  switch(caseMap.biome){
    case VOID :
      traversable = 0;
      break;
    case WATER :
      traversable = 0;
      break;
  }
  switch(caseMap.ressource){
    case TREE :
      traversable = 0;
      break;
    case LEAF :
      traversable = 0;
      break;
    case MUR :
      traversable = 0;
      break;
  }
  return  traversable;
}



void deplacer(Info_Jeu* pJeu){
  Entitee* pJoueur = pJeu->pJoueur;
  Regard regard = pJoueur->regard;

  int deplacementX = 0;
  int deplacementY = 0;
  
  switch(regard){
    case HAUT :
      deplacementX = 0;
      deplacementY = -1;
      break;
    case BAS :
      deplacementX = 0;
      deplacementY = 1;
      break;
    case DROITE :
      deplacementX = 1;
      deplacementY = 0;
      break;
    case GAUCHE :
      deplacementX = -1;
      deplacementY = 0;
      break;
  }
  if(peutPasser(pJeu->mapJeu->pDonnees->tab[pJoueur->coordonnees.x + deplacementX][pJoueur->coordonnees.y + deplacementY])){
          pJoueur->coordonnees.x += deplacementX;
          pJoueur->coordonnees.y += deplacementY;
        }
}