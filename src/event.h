#ifndef EVENT_H
#define EVENT_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <ncurses.h>

#include "main.h"
#include "map.h"

int getEvent(Info_Jeu* pJeu);

void action(Info_Fenetre* pFenetre, Info_Jeu* pJeu);

int peutPasser(CaseMap caseMap);

void deplacer(Info_Jeu* pJeu);

void interagir(Info_Jeu* pJeu);

void death(Entitee* pEntitee, Info_Jeu* pJeu);

int peutRamasser(CaseMap caseMap);

int peutCasser(CaseMap caseMap);


#endif