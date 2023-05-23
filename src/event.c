#include "event.h"
#include "donnees.h"

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
      /*case 'E':
          interagir */        
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
    case ROCHER :
      traversable = 0;
      break;
  }
  return  traversable;
}



void deplacer(Info_Jeu* pJeu){
  Entitee* pJoueur = pJeu->pJoueur;
  Regard regard = pJoueur->regard;

  int regardX = 0;
  int regardY = 0;
  
  switch(regard){
    case HAUT :
      regardX = 0;
      regardY = -1;
      break;
    case BAS :
      regardX = 0;
      regardY = 1;
      break;
    case DROITE :
      regardX = 1;
      regardY = 0;
      break;
    case GAUCHE :
      regardX = -1;
      regardY = 0;
      break;
  }

  if(getTimeMicros() - pJoueur->T_dernierDeplacement >= pJoueur->T_intervalleDeplacement){
    if(peutPasser(pJeu->mapJeu->pDonnees->tab[pJoueur->coordonnees.x + regardX][pJoueur->coordonnees.y + regardY])){
      pJoueur->coordonnees.x += regardX;
      pJoueur->coordonnees.y += regardY;

      pJoueur->T_dernierDeplacement = getTimeMicros();
    }
  }
    
  
}


void interagir(Info_Jeu* pJeu){
  Entitee* pJoueur = pJeu->pJoueur;
  Regard regard = pJoueur->regard;
  ListeObj listeObj = pJeu->listeObj;
  Ressource ressource = 0;

  int regardX = 0;
  int regardY = 0;
  
  switch(regard){
    case HAUT :
      regardX = 0;
      regardY = -1;
      break;
    case BAS :
      regardX = 0;
      regardY = 1;
      break;
    case DROITE :
      regardX = 1;
      regardY = 0;
      break;
    case GAUCHE :
      regardX = -1;
      regardY = 0;
      break;
  }

  //ressource = pJeu->mapJeu->pDonnees->tab[pJoueur->coordonnees.x + regardX][pJoueur->coordonnees.y + regardY].ressource;

  if(peutRamasser(pJeu->mapJeu->pDonnees->tab[pJoueur->coordonnees.x + regardX][pJoueur->coordonnees.y + regardY])){
    ramasser(Obj *pObj, pJoueur)
    ressource = EMPTY;
  }
  else if(peutCasser(pJeu->mapJeu->pDonnees->tab[pJoueur->coordonnees.x + regardX][pJoueur->coordonnees.y + regardY])){
    switch(ressource){
      case TREE :
        ressource = BATON;
        break;
      case LEAF :
        ressource = ????;
        break;
      case ROCHER :
        ressource = CAILLOU;
        break;
    }
  }
    
}








void death(Entitee* pEntitee, Info_Jeu* pJeu){
  if(pEntitee->pvActuelle <= 0){
      pEntitee->coordonnees.x = pEntitee->initial.x;
      pEntitee->coordonnees.y = pEntitee->initial.y;
      pJeu->score = 0;
  }
  printw("tu es mort................miskin");
}







int peutRamasser(CaseMap caseMap){
  int ramassable = 0;
  switch(caseMap.ressource){
    case HACHE :
      ramassable = 1;
      break;
    case BATON :
      ramassable = 1;
      break;
    case CAILLOU :
      ramassable = 1;
      break;
  }
  return  ramassable;
}


int peutCasser(CaseMap caseMap){
  int cassable = 0;
  switch(caseMap.ressource){
    case TREE :
      cassable = 1;
      break;
    case ROCHER :
      cassable = 1;
      break;
    case LEAF :
      cassable = 1;
      break;
  }
  return  cassable;
}