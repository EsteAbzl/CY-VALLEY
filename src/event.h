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

void death(Entitee* pEntitee, Info_Jeu* pJeu);

int ramasser(Info_Jeu *pJeu, CaseMap caseMap);

int peutCasser(Info_Jeu* pJeu, CaseMap caseMap);


#endif