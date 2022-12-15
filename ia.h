#ifndef IMM2223_GR6_IA_H
#define IMM2223_GR6_IA_H


#include <stdbool.h>
#include <stdlib.h>
#include<time.h>
#include <limits.h>

#include"const.h"
#include "mouvement.h"
#include "debug.h"
#include "abalone_terminal.h"


/**
 * \file ia.h
 * \brief Bibliothèque des fonctions utiles pour l'Intelligence Artificielle
*/

/**
 * \struct Node ia.h ia.c
 * \brief Le structure d'un noeud de l'abre minimax
*/
/**
 * \typedef Node
 * \brief Raccourci pour Node
*/
/**
 * \typedef PNode
 * \brief Pointeur vers un Node
*/
typedef struct Node {
    /*! Node enfants*/
    struct Node** children;
    /*! Nombre de Node enfants*/
    int nb_children;
    /*! plateau du noeud*/
    char** board;
    /*! Mouvement effectué depuis le père pour arriver vers ce Node*/
    Mouvement mouvement;
    /*! Hauteur du noeud par rapport au fond de l'arbre*/
    int depth;
    /*! Valeur d'évaluation du plateau de ce noeud*/
    int value;
} Node, *PNode;


int random_number(int min, int max);
Mouvement random_move(char** board, char player, Mouvement list_mvt[MAX_CHILDREN], int count);
//à partir de l'abalone et de la couleur du joueur,renvoit une liste de tous les mouvements possibles
void add_coord(Coord start, Coord end, PCoord out);
void ensemble_mouvement_possible(char** board, char player, Mouvement liste_coup[MAX_CHILDREN], int* nbr_coup);
//permet de remplir la liste des coups possibles qui sera retourné dans ensemble_mouvement_possible et count un pointeur de l'index du dernier mouvement
void gen_mouvement(char** board, char player, Coord start, Mouvement liste_coup[MAX_CHILDREN], int* nb_coup);

Mouvement play_random_move(char** board, char player);

int count_center(char** board, char player);//compte lenembre des pions au centre
int count_padding(char** board, char player);//compte les nembre des pios proche des bordure(EN DANGER)
int score_density(char** board, char player);//calcule la densite des blocks
int score_utility(char** board, char player);//somme les criteres precedant suivants leure penderance .
int score_row(char** board, char player);
int score_col(char** board, char player);
int score_group_row(char** board, char player);
int score_group_col(char** board, char player);

// dettermine les cordoner point le plus proche a l origine et celui le plus loins.
Coord PT_min(char** board, char player);
Coord PT_max(char** board, char player);
int possible_attacks(char** board, char player);//determine le nembre des attack possible
char other_player(char player);//determine la couleur du joueur opposant
int minimax(char** board, int depth, int alpha, int beta, bool max_player, char active_player, PMouvement mouvement);
Mouvement terminator_move(char** board, char active_player);

#endif //IMM2223_GR6_IA_H
