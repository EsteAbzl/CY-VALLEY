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
  pInv->inv[size];
  pInv->stockagePris = 0;
  pInv->stockageTotal = size;
  for (int n; n<size ; n++){
    pInv->inv[n].nbobj = 0;
    pInv->inv[n].nbmax = 0;
    pInv->inv[n].nbact = 0;
    pInv->inv[n].buffobj.buffpv = 0;
    pInv->inv[n].buffobj.buffatk = 0;
    pInv->inv[n].buffobj.heal = 0;
    for (int n; n<30 , n++){
          pInv->inv[n].tab[n] = 0
      }
  }
}

void mainInventaire(Inventaire* Inv){
  for(int n; n<5;n++){ // 5 est le nombre d'obj dans le main mais c changable
    if(Inv->Inv[n].buffobj.buffpv != 0){
      
  }
}

//manque prendre un item dans l'inv
// la barre main inventaire de ce que le mec utilise
// fonction qui enlève et ajt l'atk / pv en fonction de si l'obj est équipé ou pas
//fonction consommation d'un obj?
//