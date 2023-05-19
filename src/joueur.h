#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// bibliothèque qui permettent de modifier le terminal
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO

typedef struct{
  int x;
  int y;
}POSITION;

typedef enum{
  DROITE, GAUCHE, BAS, HAUT
}REGARD;

typedef struct{
  char nom[100];
  int PV;
  int ATK;
  int DEF;
  REGARD regardJoueur;
  POSITION posJoueur;
}JOUEUR;

void deplacementJoueur(JOUEUR* pJoueur);
