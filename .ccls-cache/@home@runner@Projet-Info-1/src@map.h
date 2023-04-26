#include <stdio.h>
#include <stdlib.h>


//Structure qui va contenir les information de chaques cases de la map.
typedef struct{
  int biome;
  int ressource;

}CaseMap;

//Structure qui réunis les informations sur une map et son tableau.
typedef struct{
  int width;
  int height;

  CaseMap **tab;

}Map;


/*RESET des structures*/

// Les fonctions "res_Structure" initialisent les structure dédiée.
// C'est à dire que toutes leurs valeurs sont mis à zero/la valeur décidée comme neutre.
// /!\ Il faut modifier ces fonctions dès que l'on modifie la dite structure.

void res_CaseMap(CaseMap* pCaseMap);
void res_Map_tab(Map* pMap);
void res_Map(Map* pMap);


/*CONSTRUCTEURS des stuctures*/

// Les fonctions "constructor_Structure" vont un peu plus loin que les fonction "res_"
// Elles ont pour but de facilement créer un objet du type de la structure,
// et par la même occasion d'affecter certaines valeurs.

// Retourne un pointeur sur un tableau a deux dimention de type CaseMap.
// Le tableau se lit: tab[x][y]
CaseMap** constructor_Map_tab(int width, int height);

// Retourne un pointeur sur un objet de type Map.
Map* constructor_Map(int width, int height);

// Libère la mémoire prise par une map passée en paramètre.
// IMPORTANT de le faire pour toutes les maps créées
void free_Map(Map* pMap);

/*AUTRES fonctions*/

// Affiche le contenu du tableau d'une Map en entier
void printMap(Map* pMap);

