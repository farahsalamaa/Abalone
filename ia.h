#ifndef IMM2223_GR6_IA_H
#define IMM2223_GR6_IA_H

#include "const.h"
#include "abalone_terminal.h"
#include "mouvement.h"

/**
 * \file ia.h
 * \brief Bibliothèque des fonctions utiles pour l'Intelligence Artificielle
*/

int random_number(int min, int max);
PMouvement coord_to_mvt(PAbalone abalone, PMouvement mvt);
int last_element_tab_mvt(PMouvement list_mvt);
void random_move(PAbalone abalone, PMouvement list_mvt);
//renvoie la liste des 4 coordonnees de end possibles pour n'importe quel start selon la couleur du joueur
PCoord all_end(Coord start);
//à partir de l'abalone et de la couleur du joueur,renvoit une liste de tous les mouvements possibles
PMouvement ensemble_mouvement_possible(PAbalone abalone,char color);
//permet de remplir la liste des coups possibles qui sera retourné dans ensemble_mouvement_possible
void generation_mouvement(PAbalone abalone,Coord boule,Mouvement *list);
void play_random_move(PAbalone abalone);

int count_center(PAbalone abalone,char color);//compte lenembre des pions au centre
int count_padding(PAbalone abalone,char color);//compte les nembre des pios proche des bordure(EN DANGER)
int score_density(PAbalone abalone,char color);//calcule la densite des blocks
int score_utility(PAbalone abalone);//somme les criteres precedant suivants leure penderance .
// dettermine les cordoner point le plus proche a l origine et celui le plus loins.
PCoord PT_min(PAbalone abalone,char color);
PCoord PT_max(PAbalone abalone,char color);
int possible_attacks(PAbalone abalone,char color);//determine le nembre des attack possible
char Other_player(PAbalone abalone);//determine la couleur du joueur opposant




#endif //IMM2223_GR6_IA_H
