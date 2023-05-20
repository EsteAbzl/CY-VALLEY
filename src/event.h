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


#endif