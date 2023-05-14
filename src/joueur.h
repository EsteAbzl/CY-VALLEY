#ifndef JOUEUR_H
#define JOUEUR_H

#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "game.h"
#include "affichage.h"

typedef struct{
  Obj inv[];
  int stockagePris;
  int stockageTotal;
}Inventaire;

typedef struct{
  Pos pJoueur;
  int pvActuelle;
  int pvTotal;
  int atk;
  Inventaire invJoueur;
}Entitee;


#endif