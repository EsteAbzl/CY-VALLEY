#include "joueur.h"
JOUEUR j1;

void deplacementJoueur(JOUEUR* pJoueur) {
  char deplacement = 'm';
  int a = 0;
  while (a == 0) {
    printf("");
    scanf("%c", &deplacement);
    while(getchar() != '\n');
    switch (deplacement) {
    case 'z':
      pJoueur->posJoueur.y = pJoueur->posJoueur.y - 1;
      a = 0;
      break;
    case 's':
      pJoueur->posJoueur.y = pJoueur->posJoueur.y + 1;
      a = 0;
      break;
    case 'q':
      pJoueur->posJoueur.x = pJoueur->posJoueur.x - 1;
      a = 0;
      break;
    case 'd':
      pJoueur->posJoueur.x = pJoueur->posJoueur.x + 1;
      a = 0;
      break;
    default:
      a = 1;
    }

    printf("(%d,%d)", pJoueur->posJoueur.x, pJoueur->posJoueur.y);
  }
}