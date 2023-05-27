#ifndef QUETE_H
#define QUETE_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <ncurses.h>

#include "donnees.h"

//void ecran_Fin_Radeau(); a faire


void res_Quete(Quete* pQuete);

void dialogue_Radeau(Quete* pQuete);

void quete_Radeau(Quete* pQuete, ListeObj* pListe, int e_Paul);
void quete_Radeau_1(Quete* pQuete, ListeObj* pListe);
void quete_Radeau_2(Quete* pQuete, ListeObj* pListe);
void quete_Radeau_3(Quete* pQuete, ListeObj* pListe);
void quete_Radeau_4(Quete* pQuete, ListeObj* pListe, int e_Paul);

void dialogue_Paul(Quete* pQuete);

void quete_Paul_1(Quete* pQuete, ListeObj* pListe);
void quete_Paul_2(Quete* pQuete, ListeObj* pListe);
void quete_Paul_3(Quete* pQuete, ListeObj* pListe);
void quete_Paul(Quete* pQuete, ListeObj* pListe, int eDQuete_Radeau);


#endif