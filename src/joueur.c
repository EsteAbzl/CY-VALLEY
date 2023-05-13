#include <joueur.h>



typedef struct{
  Obj inv[];
  int stockagefree;
  int stockagetotal;
}Inventaire;


typedef struct{
  Pos Pjoueur;
  int Pv;
  Inventaire InvJoueur;
}Entitee;

int modifpv(dmgorheal){
  Joueur->Pv =+ dm
}