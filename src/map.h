#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

#include "brush.h"

//
//ENUM ET STRUCTURES
//

// DONNEES
typedef enum{
  VOID,
  WATER,
  DEEP_WATER,
  SAND,
  GRASS,

  BOUTON
}Biome;

typedef enum{
  EMPTY,  //
  WAVE,   //🌊
  TREE,   //🌳🌴
  BATON,  //▂
  COCO,   //🥥
  LEAF,   //🍃    
  ROCHER, //⛰ 
  CAILLOU,//☁
  PNG_PAUL,//🕺
  PNG_BOAT,//⛵

  HACHE,  //🪓
  PIOCHE, //⛏

  TOUCHE,
  NOUVEAU_JEU,
  REPRENDRE_JEU,
  QUITTER_JEU
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

  CaseMap **tab; // tab[x][y] = type CaseMa

}Donnees_Map;


// AFFICHAGE
typedef struct{
  char caractere[10]; // permet d'afficher des caractère utf-8: sprintf(caractere, "🌳");
  Brush brush; // 'Pinceau' qui contient la couleur de fond et de caractère

  int isLoaded;
}Print;

//Structure qui permet l'affichage d'une map.
typedef struct{
  int width;
  int height;

  Print **tab;

}Affichage_Map;


// MAP
typedef struct{
  int width;
  int height;

  Donnees_Map* pDonnees;
  Affichage_Map* pAffichage;
}Map;


//
//RESET DES STRUCTURES
//
// Les fonctions "res_Structure" initialisent les structure dédiée.
// C'est à dire que toutes leurs valeurs sont mis à zero/la valeur décidée comme neutre.
// /!\ Il faut modifier ces fonctions dès que l'on modifie la dite structure.


// DONNEES
void res_CaseMap(CaseMap* pCaseMap);
void res_Donnees_Map_tab(Donnees_Map* pDonnees_Map);
void res_Donnees_Map(Donnees_Map* pDonnees_Map);

// AFFICHAGE
void res_Print(Print* pPrint);
void res_Affichage_Map_tab(Affichage_Map* pAffichage_Map);
void res_Affichage_Map(Affichage_Map* pAffichage_Map);

// MAP
void res_Map(Map* pMap);


//
//CONSTRUCTEURS DES STRUCTURES
//
// Les fonctions "constructor_Structure" vont un peu plus loin que les fonction "res_"
// Elles ont pour but de facilement créer un objet du type de la structure,
// et par la même occasion d'affecter certaines valeurs.

  
//  Retourne un pointeur sur un tableau a deux dimention du type souhaité.
//  Le tableau se lit: tab[x][y]
// DONNEES
CaseMap** constructor_Donnees_Map_tab(int width, int height);
// AFFICHAGE
Print** constructor_Affichage_Map_tab(int width, int height);

//  Retourne un pointeur sur un objet de type souhaité.
// DONNEES
Donnees_Map* constructor_Donnees_Map(int width, int height);
// AFFICHAGE
Affichage_Map* constructor_Affichage_Map(int width, int height);
// MAP
Map* constructor_Map(int width, int height);


//
//  DESALLOCATION
//
//  Libère la mémoire prise par une map passée en paramètre.
//  IMPORTANT de le faire pour toutes les maps créées
// DONNEES
void free_Donnees_Map(Donnees_Map* pDonnees_Map);
// AFFICHAGE
void free_Affichage_Map(Affichage_Map* pAffichage_Map);
// MAP
void free_Map(Map* pMap);

//quete
void ocean_Affichage_Map_tab(Affichage_Map* pAffichage_Map);
void ocean_Print(Print* pPrint);



#endif