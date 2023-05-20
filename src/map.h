#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//
//ENUMS, STRUCTURES
//
typedef struct{
  int x;
  int y;
}POSITION;

typedef enum{
WATER,SAND,GRASS,VOID
}Biome;

typedef enum{
TREE,LEAF,EMPTY,OBSTACLE
}Ressource;


typedef struct{
  char caractere[10]; // permet d'afficher des caractère utf-8: sprintf(caractere, "🌳");

  char back_color[30]; // sprintf(back_color, "\033[48;2;%d;%d;%dm", r, g, b);
  char font_color[30]; // sprintf(font_color, "\033[38;2;%d;%d;%dm", r, g, b);

  int isLoaded;
}Print;

//Structure qui va contenir les information de chaques cases de la map.
typedef struct{
  POSITION posCase;
  Biome biome;
  Ressource ressource;
  int estTraversable;
  Print print;
}CaseMap;

//Structure qui réunis les informations sur une map et son tableau.
typedef struct{
  int width;
  int height;

  CaseMap **tab;

}Map;


//
//RESET DES STRUCTURES
//
// Les fonctions "res_Structure" initialisent les structure dédiée.
// C'est à dire que toutes leurs valeurs sont mis à zero/la valeur décidée comme neutre.
// /!\ Il faut modifier ces fonctions dès que l'on modifie la dite structure.

void res_Print(Print* pPrint);
void res_CaseMap(CaseMap* pCaseMap);
void res_Map_tab(Map* pMap);
void res_Map(Map* pMap);


//
//CONSTRUCTEURS DES STRUCTURES
//
// Les fonctions "constructor_Structure" vont un peu plus loin que les fonction "res_"
// Elles ont pour but de facilement créer un objet du type de la structure,
// et par la même occasion d'affecter certaines valeurs.

/*  
  Retourne un pointeur sur un tableau a deux dimention de type CaseMap.
  Le tableau se lit: tab[x][y]
*/
CaseMap** constructor_Map_tab(int width, int height);

/*
  Retourne un pointeur sur un objet de type Map.
*/
Map* constructor_Map(int width, int height);

/*
  Libère la mémoire prise par une map passée en paramètre.
  IMPORTANT de le faire pour toutes les maps créées
*/
void free_Map(Map* pMap);


//
//AUTRES FONCTIONS
//

void generateMap(Map* pMap);

/*
  Affiche le contenu du tableau d'une Map en entier
*/
void printMap(Map* pMap);

#endif