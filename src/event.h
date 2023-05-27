#ifndef EVENT_H
#define EVENT_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <ncurses.h>

#include "main.h"
#include "map.h"
#include "quete.h"
#include "donnees.h"

int getEvent(Info_Jeu* pJeu);

void action(Info_Fenetre* pFenetre, Info_Jeu* pJeu);

int peutPasser(CaseMap caseMap);

void deplacer(Info_Fenetre* pFenetre, Info_Jeu* pJeu);

void interagir(Info_Fenetre* pFenetre, Info_Jeu* pJeu);


int ramasser(Info_Jeu *pJeu, CaseMap caseMap);

int peutCasser(Info_Jeu* pJeu, CaseMap caseMap);

void death(Info_Jeu* pJeu, Info_Fenetre* pFenetre);

void limiteScore(Info_Jeu* pJeu, Info_Fenetre* pFenetre);

void faim(Entitee* pJoueur, long temps);

void fin(Info_Jeu* pJeu, Info_Fenetre* pFenetre, int nb_Fin);

#endif