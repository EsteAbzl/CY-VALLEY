#include "joueur.h"

void deplacementJoueur(JOUEUR j1){
  char deplacement = m;
  int a = 1;
  while(a==1){
    printf("");
    scanf("%c", &deplacement);
    switch(deplacement){
      case deplacement==z:
        j1.posJoueur.y = j1.posJoueur.y - 1;
        a = 0;
        break;
      case deplacement==s:
        j1.posJoueur.y = j1.posJoueur.y + 1;
        a = 0;
        break;
      case deplacement==q:
        j1.posJoueur.x = j1.posJoueur.x - 1;
        a = 0;
        break;
      case deplacement==d:
        j1.posJoueur.x = j1.posJoueur.x + 1;
        a = 0;
        break;
      default:
        a = 1;
  }   
}