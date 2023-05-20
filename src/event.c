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
        pJoueur->coordonnees.y--;
        /*
        if(pJoueur->caseJoueur.ressource == OBSTACLE){
          pJoueur->posJoueur.y = pJoueur->posJoueur.y + 1;
        }
        a = 0;*/
        pJoueur->regard = HAUT;
        break;
      case 'S':
        pJoueur->coordonnees.y++;
        /*
        if(pJoueur->caseJoueur.ressource == OBSTACLE){
          pJoueur->posJoueur.y = pJoueur->posJoueur.y - 1;
        }
        a = 0;*/
        pJoueur->regard = BAS;
        break;
      case 'Q':
        pJoueur->coordonnees.x--;
        /*
        if(pJoueur->caseJoueur.ressource == OBSTACLE){
          pJoueur->posJoueur.y = pJoueur->posJoueur.x + 1;
        }
        a = 0;*/
        pJoueur->regard = GAUCHE;
        break;
      case 'D':
        pJoueur->coordonnees.x++;
        /*
        if(pJoueur->caseJoueur.ressource == OBSTACLE){
          pJoueur->posJoueur.y = pJoueur->posJoueur.x - 1;
        }
        a = 0;*/
        pJoueur->regard = DROITE;
        break;
      case 'A':
        pJeu->enJeu = 0;
        break;
    }
    
  }
}