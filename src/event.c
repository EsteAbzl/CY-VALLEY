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
  int score = pJeu->score;
  if(getEvent(pJeu)){
    switch (pJeu->event){
      case 'Z':
        pJoueur->regard = HAUT;
        
        deplacer(pFenetre, pJeu);
        score = score + 5;
        break;
      case 'S':
        pJoueur->regard = BAS;

        deplacer(pFenetre, pJeu);
        score = score + 5;
        break;
      case 'Q':
        pJoueur->regard = GAUCHE;

        deplacer(pFenetre, pJeu);
        score = score + 5;
        break;
      case 'D':
        pJoueur->regard = DROITE;

        deplacer(pFenetre, pJeu);
        score = score + 5;
        break;
      case 'A':
        clear();
        pFenetre->ecran = ACCUEIL;
        pJoueur->coordonnees.x = 10;
        pJoueur->coordonnees.y = 10;
        break;
      case 'E':
        interagir(pFenetre, pJeu);
        break;
      case ' ':
        pJeu->enJeu = 0;
        break;
      /*case 'I' :
          inventaire
          break; */
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
    case ROCHER :
      traversable = 0;
      break;
    case PNG_BOAT :
      traversable = 0;
      break;
    case PNG_PAUL :
      traversable = 0;
      break;
  }
  return  traversable;
}



void deplacer(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  Entitee* pJoueur = pJeu->pJoueur;
  Regard regard = pJoueur->regard;
  Map* pMapUtilise = NULL;

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

  switch(pFenetre->ecran){
    case ACCUEIL:
      pMapUtilise = pJeu->mapAccueil;
      break;
    case JEU:
      pMapUtilise = pJeu->mapJeu;
      break;
  }

  if((pJoueur->coordonnees.x + regardX >= 0 && pJoueur->coordonnees.x + regardX < pMapUtilise->width)
    && (pJoueur->coordonnees.y + regardY >= 0 && pJoueur->coordonnees.y + regardY < pMapUtilise->height)){
    
    if(getTimeMicros() - pJoueur->T_dernierDeplacement >= pJoueur->T_intervalleDeplacement){
      
      if(peutPasser(pMapUtilise->pDonnees->tab[pJoueur->coordonnees.x + regardX][pJoueur->coordonnees.y + regardY])){
        pJoueur->derniereCoordonnees.x = pJoueur->coordonnees.x;
        pJoueur->derniereCoordonnees.y = pJoueur->coordonnees.y;
        
        pJoueur->coordonnees.x += regardX;
        pJoueur->coordonnees.y += regardY;
  
        pJoueur->T_dernierDeplacement = getTimeMicros();
      }
    }
    printw("\n                ");
  }
  else{
    printw("\nHORS DE LA MAP");
  }
}



void interagir(Info_Fenetre* pFenetre, Info_Jeu* pJeu){
  Entitee* pJoueur = pJeu->pJoueur;
  Regard regard = pJoueur->regard;
  CaseMap* pCaseMap = NULL;
  int* pIsLoaded = NULL;

  Map* pMap = NULL;
  switch(pFenetre->ecran){
    case ACCUEIL:
      pMap = pJeu->mapAccueil;
      break;
    case JEU:
      pMap = pJeu->mapJeu;
      break;
  }

  
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

  pCaseMap = &pMap->pDonnees->tab[pJoueur->coordonnees.x + regardX][pJoueur->coordonnees.y + regardY];
  pIsLoaded = &pMap->pAffichage->tab[pJoueur->coordonnees.x + regardX][pJoueur->coordonnees.y + regardY].isLoaded;
  
  switch(pFenetre->ecran){
    case ACCUEIL:
      switch(pCaseMap->ressource){
        case NOUVEAU_JEU:
          debutJeu(pFenetre, pJeu);
          break;
        case REPRENDRE_JEU:
          reprendreJeu(pFenetre, pJeu);
          break;
        case QUITTER_JEU:
          pJeu->enJeu = 0;
          break; 
      }
      break;
    case JEU:
      if(ramasser(pJeu, *pCaseMap)){
        pCaseMap->ressource = EMPTY;
        pJeu->score = pJeu->score + 50;
        *pIsLoaded = 0;
      }
      else if(peutCasser(pJeu, *pCaseMap)){
        switch(pCaseMap->ressource){
          case TREE :
            pCaseMap->ressource = BATON;
            pJeu->score = pJeu->score + 100;
            *pIsLoaded = 0;
            break;
          case ROCHER :
            pCaseMap->ressource = CAILLOU;
            pJeu->score = pJeu->score + 100;
            *pIsLoaded = 0;
            break;
        }
      }
      else{
        switch(pCaseMap->ressource){
          case PNG_BOAT:
            quete_Radeau(pJeu->pJoueur, pJeu->pQ_Radeau, &pJeu->listeObj, pJeu->pQ_Survivant->etape);
            break;
          case PNG_PAUL:
            quete_Paul(pJeu->pJoueur, pJeu->pQ_Survivant, &pJeu->listeObj, pJeu->pQ_Radeau->e_Dialogue);
            if(pJeu->pQ_Survivant->etape == 4){
              pCaseMap->ressource = EMPTY;
              *pIsLoaded = 0;
            }
            break;
      }
      break;
    }
  }
  
}

int ramasser(Info_Jeu *pJeu, CaseMap caseMap){
  int ramassable = 0;
  Entitee* pJoueur = pJeu->pJoueur;
  ListeObj* pListeObj = &(pJeu->listeObj);
  switch(caseMap.ressource){
    case COCO :
      if(pJeu->pJoueur->pvActuelle <= pJeu->pJoueur->pvTotal - 20){
        ramassable = 1;
        pJeu->pJoueur->pvActuelle += 20;
      }
      break;
    case BATON :
      ramassable = ramasserObjet(&pListeObj->baton, pJoueur);
      break;
    case CAILLOU :
      ramassable = ramasserObjet(&pListeObj->caillou, pJoueur);
      break;
    case LEAF :
      ramassable = ramasserObjet(&pListeObj->feuille, pJoueur);
        break;
    case HACHE :
      ramassable = ramasserObjet(&pListeObj->hache, pJoueur);
      break;
    case PIOCHE :
      ramassable =  ramasserObjet(&pListeObj->pioche, pJoueur);
      break;
  }
  return  ramassable;
}


int peutCasser(Info_Jeu* pJeu, CaseMap caseMap){
  int cassable = 0;
  switch(caseMap.ressource){
    case TREE :
      if(pJeu->listeObj.hache.nb){
        cassable = 1;
      }
      break;
    case ROCHER :
      if(pJeu->listeObj.pioche.nb){
        cassable = 1;
      }
      break;
  }
  return  cassable;
}

void faim(Entitee* pJoueur, long temps){
  //pJoueur->pvActuelle = 100;
  static int dTemp;
  if(!(temps % 5)){
    if(temps != dTemp){
      dTemp = temps;
      pJoueur->pvActuelle-= 2;
      //modifpvA(5, pJoueur);    
    }
  }
}


void death(Info_Jeu* pJeu, Info_Fenetre* pFenetre){
  Entitee* pEntitee = pJeu->pJoueur;
  if(pEntitee->pvActuelle <= 0){
    pEntitee->coordonnees.x = pEntitee->initial.x;
    pEntitee->coordonnees.y = pEntitee->initial.y;
    pJeu->score -= 1000;
    pEntitee->vie --;

    if(pEntitee->vie == 1){
      printw("SYSTEME : Tu es mort, il te reste une vie.");
      pEntitee->pvActuelle = 100;
    }
    else{
      fin(pJeu, pFenetre, 3);
    }
  }
 
}

void limiteScore(Info_Jeu* pJeu, Info_Fenetre* pFenetre){
  if(pJeu->score > 10000){
    fin(pJeu, pFenetre, 2);
  }
}

void fin(Info_Jeu* pJeu, Info_Fenetre* pFenetre, int nb_Fin){
  switch(nb_Fin){
    case 1:    // fin quête
    pJeu->enJeu = 0;
  break;
    case 2:    // fin score
    pJeu->enJeu = 0;
  break;
    case 3:    // fin vie / temps
    pJeu->enJeu = 0;
  break;
  }
}
