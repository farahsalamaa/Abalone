#ifndef IMM2223_GR6_MOUVEMENT_H
#define IMM2223_GR6_MOUVEMENT_H

#include "const.h"
#include "abalone_terminal.h"
#include "debug.h"

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

#endif //IMM2223_GR6_MOUVEMENT_H
