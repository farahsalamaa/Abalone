#ifndef IMM2223_GR6_IA_H
#define IMM2223_GR6_IA_H

#include <limits.h>
#include <stdbool.h>

#include "const.h"
#include "abalone_terminal.h"
#include "mouvement.h"

/**
 * \file ia.h
 * \brief Bibliothèque des fonctions utiles pour l'Intelligence Artificielle
*/

int random_number(int min, int max);
PMouvement coord_to_mvt(char** board, char player, PMouvement mvt);
int last_element_tab_mvt(PMouvement list_mvt);
void random_move(char** board, char player, PMouvement list_mvt,int count);
//renvoie la liste des 4 coordonnees de end possibles pour n'importe quel start selon la couleur du joueur
PCoord all_end(Coord start);
//à partir de l'abalone et de la couleur du joueur,renvoit une liste de tous les mouvements possibles
PMouvement ensemble_mouvement_possible(char** board, char player, int* nbr_coup);
//permet de remplir la liste des coups possibles qui sera retourné dans ensemble_mouvement_possible et count un pointeur de l'index du dernier mouvement
void gen_mouvement(char** board, char player, Coord start, PMouvement liste_coup, int* nb_coup);

void play_random_move(char** board, char player);

int count_center(char** board, char player);//compte lenembre des pions au centre
int count_padding(char** board, char player);//compte les nembre des pios proche des bordure(EN DANGER)
int score_density(char** board, char player);//calcule la densite des blocks
int score_utility(char** board, char player);//somme les criteres precedant suivants leure penderance .
// dettermine les cordoner point le plus proche a l origine et celui le plus loins.
PCoord PT_min(char** board, char player);
PCoord PT_max(char** board, char player);
int possible_attacks(char** board, char player);//determine le nembre des attack possible
char other_player(char player);//determine la couleur du joueur opposant
PNode init_node(char** board, int nb_coup, int depth);
int minimax(PNode father, int alpha, int beta, bool max_player, char active_player);
Mouvement terminator(char** board, int depth, char active_player);
void terminator_move(char** board, int depth, char active_player);


#endif //IMM2223_GR6_IA_H