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
char orientation_grp(Coord start, Coord end);
char length_mvt(Mouvement mvt);
Coord voisin_carre(PAbalone abalone, Mouvement mvt);
char direction_mvt(PAbalone abalone, Mouvement mvt);

int validate_mvt(PAbalone abalone, Mouvement mvt);
PAbalone exec_mvt(PAbalone plateau, Mouvement p);
int finalise_mvt(PAbalone G,Mouvement mvt);

// Convert_Coord()
int string_to_coord(char* mvt, PCoord coord);
int coord_to_mouvement(PAbalone abalone, PMouvement mvt, PCoord coords);

#endif //IMM2223_GR6_MOUVEMENT_H
