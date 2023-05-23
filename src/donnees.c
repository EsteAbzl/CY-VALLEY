#include "donnees.h"


unsigned long getTimeMicros(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec*1000000) + (tv.tv_usec/1);
} 


void generateMap(Donnees_Map* pDonnees_Map){
  srand(time(NULL));

  for (int y = 0; y < pDonnees_Map->height; y++) {
    for (int x = 0; x < pDonnees_Map->width; x++) {
      if((x < 10 || pDonnees_Map->width - x < 10) || (y < 10 || pDonnees_Map->height - y < 10)){
        pDonnees_Map->tab[x][y].biome = WATER;
      }
      else if((x < 15 || pDonnees_Map->width - x < 15) || (y < 15 || pDonnees_Map->height - y < 15)){
        pDonnees_Map->tab[x][y].biome = SAND;
        if( !(rand() % 50)){
          pDonnees_Map->tab[x][y].ressource = LEAF;
        }
      }
      else{
        pDonnees_Map->tab[x][y].biome = GRASS;
        if( !(rand() % 20)){
          pDonnees_Map->tab[x][y].ressource = TREE;
        }
      }
      
    }// x
  }// y
}

void res_Vide(Obj* pObj, int n){
  pObj->id_Obj = O_VIDE;
  pObj->nb_Max = 1;
  pObj->nb = 1;
  pObj->placeinv = n;
  sprintf(pObj->nom, "VIDE");
  

  //res_BuffObj(&(pObj->buffObj));
}

void init_Inventaire(Inventaire* pInv, int size){
  pInv->stockagePris = 0;
  pInv->stockageTotal = size;

  for(int n = 0; n<size ; n++){
    res_Vide(&(pInv->inv[n]), n);
  }
}

Entitee* init_Entitee(){

  Entitee* pEnt = NULL;
  if( !(pEnt = malloc(sizeof(Entitee)))){
    printf("Erreur lors de la création d'une entitée");
    exit(20);
  }
  
  pEnt->coordonnees.x = 0;
  pEnt->coordonnees.y = 0;

  pEnt->regard = DROITE;

  pEnt->T_dernierDeplacement = 0;
  pEnt->T_intervalleDeplacement = 0;
  
  pEnt->pvTotal = 0;
  pEnt->pvActuelle = 0;
  pEnt->atk = 0;
  
  init_Inventaire(&(pEnt->inventaire), 30); //changer le size si besoin

  return pEnt;
}

void res_Entitee(Entitee* pEnt){
  pEnt->coordonnees.x = 0;
  pEnt->coordonnees.y = 0;

  pEnt->T_dernierDeplacement = getTimeMicros();
  
  pEnt->pvTotal = 0;
  pEnt->pvActuelle = 0;
  pEnt->atk = 0;
  
  init_Inventaire(&(pEnt->inventaire), 30);
}

void modifpvA(int dmg_Heal, Entitee* pEntitee){
  pEntitee->pvActuelle += dmg_Heal;
  if(pEntitee->pvActuelle > pEntitee->pvTotal){
    pEntitee->pvActuelle = pEntitee->pvTotal;
  }
  if(pEntitee->pvActuelle < 0){
    //mort(pEntitee);
  }
}

void modifpvTT(int dmg_Heal, Entitee* pEntitee){
  pEntitee->pvTotal += dmg_Heal;
  if(pEntitee->pvTotal < pEntitee->pvActuelle){
    pEntitee->pvActuelle = pEntitee->pvTotal;
  }
}

void afficherStats(Entitee* entitee){
    printf("position x: %d  y: %d\n Pv total %d\n Pv actuelle %d\n Atk %d \n", entitee->coordonnees.x, entitee->coordonnees.y, entitee->pvTotal, entitee->pvActuelle, entitee->atk);
}

void res_Obj(Obj* pObj){
  pObj->id_Obj = O_VIDE;
  pObj->nb_Max = 0;
  pObj->nb = 0;
  pObj->placeinv = -1;
  sprintf(pObj->nom, "VIDE1");

  //for(int n; n<30 , n++){
  //  sprintf(pObj->nom, "");
  //  }

  //res_BuffObj(&(pObj->buffObj)); (pas encore de stats pr les objets)
}

Obj constructor_Obj(Id_Obj O_nom, int nb_Max, char nom[30]){
  Obj objet;
  res_Obj(&objet);
  objet.nb_Max = nb_Max;
  objet.id_Obj = O_nom;
  
  sprintf(objet.nom, "%s", nom);
  
  return objet;  
}

ListeObj init_ListeObj(){
  ListeObj listObj;
  
  listObj.baton = constructor_Obj(O_BATON, 100, "Baton" );
  listObj.caillou = constructor_Obj(O_CAILLOU, 100, "caillou");
  listObj.hache = constructor_Obj(O_HACHEP, 1, "hache");

  return listObj;
}


void testStats(Entitee* pEntitee){ // on pourra envoyé une entitée plus tard
    printf("test stats. \n");
  res_Entitee(pEntitee);
  printf("initialisez les statistiques\n");
  int x = 0;
  printf("pos x / pos y / pv TT / pv Actuelle / ATK\n");
  scanf("%d", &x);
  pEntitee->coordonnees.x = x;
  scanf("%d", &x);
  pEntitee->coordonnees.y = x;
  scanf("%d", &x);
  pEntitee->pvTotal = x;
  scanf("%d", &x);
  pEntitee->pvActuelle = x;
  scanf("%d", &x);
  pEntitee->atk = x;
  afficherStats(pEntitee);
}

int ramasser(Obj* pObj, Entitee* pJoueur){ //return 0 => pas ramassé return 1 => ramassé
  int estRamasse = 0;
  
  if(pObj->placeinv != -1){
      if(pObj->nb < pObj->nb_Max){
        pObj->nb += 1;
        estRamasse = 1;
      }
      else{
        printw("Tu as déjà le nombre maximum pour cette ressource.");
      }
    }
  else{
    for(int n = 0; n < pJoueur->inventaire.stockageTotal && pObj->placeinv == -1; n++){
      if(pJoueur->inventaire.inv[n].id_Obj == O_VIDE ){
        pJoueur->inventaire.inv[n] = *pObj;
        pObj->placeinv = n;
        estRamasse = 1;
      }
      if(estRamasse == 1){
        printw("place %d\n", n);
      }
    }
    if(estRamasse == 0){
      printw("Tu n'as plus de place dans ton inventaire.\n");
    }
  }
  return estRamasse;
}

void test(){
  printw("\n");
  
  Obj objet;
  Entitee joueur;
  //sprintf(joueur->inv[n].nom, "Blabla"); exemple de nomage
  res_Entitee(&joueur);
  res_Obj(&objet);
  sprintf(objet.nom, "bonjour");
  objet.id_Obj = O_BATON;
  if(ramasser(&objet, &joueur)){
    printw("ramassé");
    for(int i = 0; i<30; i++){
      printw("\nobjet %d = %s", i, joueur.inventaire.inv[i].nom );
    }
  }
  else{
    printw("pas ramassé");
  }

}


