#include <joueur.h>



typedef struct{
  Obj inv[];
  int stockagefree;
  int stockagetotal;
}Inventaire;



typedef struct{
  Pos Pjoueur;
  Int Pv;
  Inventaire InvJoueur;
}Joueur;

