#include "joueur.h"




//entitee peux etre utilisé pour les mobs avec posibilité de laisser leurs inv au sol qd ils meurent?


void modifpvA(int dmg_Heal, Entitee* entitee){
  entitee->pvActuelle += dmg_Heal;
}

void modifpvTT(int dmg_Heal, Entitee* entitee){
  entitee->pvTotal += dmg_Heal;
}

void modifatk(int buff, Entitee* entitee){
  entitee->atk += buff;
}



void iniInventaire(Inventaire* pInv, int size){
  pInv->stockagePris = 0;
  pInv->stockageTotal = size;

  for (int n; n<size ; n++){
    res_Obj(&(pInv->inv[n]));
  }
}

void iniEntitee(Entitee* pEnt){
  pEnt->pJoueur.x = 10;
  pEnt->pJoueur.y = 10;
  pEnt->pvTotal = 0;
  pEnt->pvActuelle = 0;
  pEnt->atk = 0;
  iniInventaire(&(pEnt->inventaire), 0);
}

void mainInventaire(Inventaire* Inv, Entitee entitee){ 
  for(int n; n<5;n++){
    if(Inv->inv[n].buffObj.pv_Buff != 0){
      modifpvTT(Inv->inv[n].buffObj.pv_Buff,  &entitee);
    }
    if(Inv->inv[n].buffObj.atk_Buff != 0){
      modifatk(Inv->inv[n].buffObj.atk_Buff,  &entitee);
    }
  Inv->inv[n].buffObj.estEquipe = 1;

  }
}

void afficherStats(Entitee* entitee){
    printf("position x: %d  y: %d\n Pv total %d\n Pv actuelle %d\n Atk %d \n", entitee->pJoueur.x, entitee->pJoueur.y, entitee->pvTotal, entitee->pvActuelle, entitee->atk);
}

void testStats(Entitee* pEntitee){ // on pourra envoyé une entitée plus tard
    printf("test stats. \n");
  iniEntitee(pEntitee);
  printf("initialisez les statistiques\n");
  int x = 0;
  printf("pos x / pos y / pv TT / pv Actuelle / ATK\n");
  scanf("%d", &x);
  pEntitee->pJoueur.x = x;
  scanf("%d", &x);
  pEntitee->pJoueur.y = x;
  scanf("%d", &x);
  pEntitee->pvTotal = x;
  scanf("%d", &x);
  pEntitee->pvActuelle = x;
  scanf("%d", &x);
  pEntitee->atk = x;
  afficherStats(pEntitee);
}


