#ifndef IMM2223_GR6_MOUVEMENT_H
#define IMM2223_GR6_MOUVEMENT_H

#include<stdlib.h>
#include<string.h>
#include "const.h"

#include "debug.h"

/**
 * \struct Coord abalone_terminal.h abalone_terminal.c
 * \brief Les coordonnées en 2D de la grille board
*/
/**
 * \typedef PCoord
 * \brief Pointeur vers un Coord
*/
typedef struct {
    /*!ordonnée*/
    int x;
    /*!abscisse*/
    int y;
} Coord, *PCoord;

/**
 * \struct Mouvement mouvement.h mouvement.c
 * \brief Le structure d'un mouvement contenant ses caractéristiques
*/
/**
 * \typedef PMouvement
 * \brief Pointeur vers un mouvement 
*/
typedef struct {
    /*! Coordonnées du depart*/
    Coord start;
    /*! Coordonnées d'arrivé*/
    Coord end;
} Mouvement, *PMouvement;



/**
 * \file mouvement.h
 * \brief Bibliothèque des fonctions du mouvement, validation et l'execution du mouvements
*/

int area_mvt(Mouvement mvt);
char type_mvt(Mouvement mvt);
char orientation_grp(Mouvement mvt);
char length_mvt(Mouvement mvt);
Coord voisin_carre(char** board, Mouvement mvt);
char direction_mvt(char** board, Mouvement mvt);

int validate_mvt(char** board, char player, Mouvement mvt);
char** exec_mvt(char** board, char player, Mouvement p);
int finalise_mvt(char** board, char player,Mouvement mvt);

// Convert_Coord()
int string_to_mouvement(char* string, PMouvement mvt);
int mouvement_to_string(Mouvement mvt, char* buffer);

#endif //IMM2223_GR6_MOUVEMENT_H
