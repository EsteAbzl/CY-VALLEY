#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{
  WATER,SAND,GRASS,VOID
}Biome;

typedef enum{
  TREE,LEAF,EMPTY
}Ressource;


//Structure qui va contenir les information de chaques cases de la map.
typedef struct{
  Biome biome;
  Ressource ressource;

}CaseMap;

//Structure qui réunis les informations sur une map et son tableau.
typedef struct{
  int width;
  int height;

  CaseMap **tab;

}Donnees_Map;


//
//RESET DES STRUCTURES
//
// Les fonctions "res_Structure" initialisent les structure dédiée.
// C'est à dire que toutes leurs valeurs sont mis à zero/la valeur décidée comme neutre.
// /!\ Il faut modifier ces fonctions dès que l'on modifie la dite structure.

void res_CaseMap(CaseMap* pCaseMap);
void res_Donnees_Map_tab(Donnees_Map* pDonnees_Map);
void res_Donnees_Map(Donnees_Map* pDonnees_Map);


//
//CONSTRUCTEURS DES STRUCTURES
//
// Les fonctions "constructor_Structure" vont un peu plus loin que les fonction "res_"
// Elles ont pour but de facilement créer un objet du type de la structure,
// et par la même occasion d'affecter certaines valeurs.

  
//Retourne un pointeur sur un tableau a deux dimention de type CaseMap.
//Le tableau se lit: tab[x][y]
CaseMap** constructor_Donnees_Map_tab(int width, int height);

//Retourne un pointeur sur un objet de type Map.
Donnees_Map* constructor_Donnees_Map(int width, int height);


//Libère la mémoire prise par une map passée en paramètre.
//IMPORTANT de le faire pour toutes les maps créées
void free_Donnees_Map(Donnees_Map* pDonnees_Map);


//
//AUTRES FONCTIONS
//

void generateMap(Donnees_Map* pDonnees_Map);

#endif