#include <joueur.h>



typedef struct{
  Obj Inv[];
  int Stockagepris;
  int Stockagetotal;
}Inventaire;

//entitee peux etre utilisé pour les mobs avec posibilité de laisser leurs inv au sol qd ils meurent?
typedef struct{
  Pos Pjoueur;
  int PvActuelle;
  int Pvtotal;
  int Atk;
  Inventaire InvJoueur;
}Entitee;

void modifpvA(int dmgorheal, Entitee* x){
  x->PvActuelle =+ dmgorheal;
}

void modifpvTT(int dmgorheal, Entitee* x){
  x->PvActuelle =+ dmgorheal;
}

void modifatk(int buff, Entitee* x){
  x->Atk =+ buff;
}

void iniInventaire(Inventaire* Inv, int size){
  Inv->Inv[size];
  Inv->Stockagepris = 0;
  Inv->Stockagetotal = size;
  for (int n; n<size ; n++){
    Inv->Inv[n]->nbobj = 0;
    Inv->Inv[n]->nbmax = 0;
    Inv->Inv[n]->nbact = 0;
    Inv->Inv[n]->buffobj->buffpv = 0;
    Inv->Inv[n]->buffobj->buffatk = 0;
    Inv->Inv[n]->buffobj->heal = 0;
    for (int n; n<30 , n++){
          Inv->Inv[n]->tab[n] = 0
      }
  }
}

void mainInventaire(Inventaire* Inv){
  for(int n; n<5;n++){ // 5 est le nombre d'obj dans le main mais c changable
    if{}
  }
}

//manque prendre un item dans l'inv
// la barre main inventaire de ce que le mec utilise
// fonction qui enlève et ajt l'atk / pv en fonction de si l'obj est équipé ou pas
//fonction consommation d'un obj?
//