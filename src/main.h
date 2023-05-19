#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <ncurses.h>

#include "map.h"
#include "game.h"
#include "affichage.h"

typedef struct{

}Info_Fenetre;


typedef struct{

}Info_Jeu;

WINDOW* init_Curses();

#endif 