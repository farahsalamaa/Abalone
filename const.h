#ifndef IMM2223_GR6_CONST_H
#define IMM2223_GR6_CONST_H
#include "mouvement.h"

/**
 * \file const.h
 * \brief Bibliothèque de toutes les definitions
*/

/*! \def MVT_LIGNE
    \brief Mouvement d'un groupe de pions est en ligne
*/
/*! \def MVT_LARGEUR
    \brief Mouvement d'un groupe de pions est en largeur
*/
#define MVT_LIGNE 'N'
#define MVT_LARGEUR 'G'

/*! \def VERTICAL
    \brief Mouvement d'un groupe de pions est vertical
*/
/*! \def HORIZONTAL
    \brief Mouvement d'un groupe de pions est horizontal
*/
#define VERTICAL 'V'
#define HORIZONTAL 'H'

/*! \def ERROR_NOT_ALIGNED
    \brief Erreur car un groupe de pions n'est pas aligné 
*/
/*! \def ERROR_NOT_A_MOVEMENT
    \brief Renvoie erreur car l'input de l'utilisateur n'est pas un mouvement de type horizontal ou vertical
*/
#define ERROR_NOT_ALIGNED 'E' 
#define ERROR_NOT_A_MOVEMENT '\0'

/*! \def DIR_UP
    \brief Mouvement d'un groupe de pions est vers le haut
*/
/*! \def DIR_DOWN
    \brief Mouvement d'un groupe de pions est vers le bas
*/
/*! \def DIR_LEFT
    \brief Mouvement d'un groupe de pions est vers la gauche
*/
/*! \def DIR_RIGHT
    \brief Mouvement d'un groupe de pions est vers la droite
*/
#define DIR_UP 'U'
#define DIR_DOWN 'D'
#define DIR_LEFT 'L'
#define DIR_RIGHT 'R'

/*! \def L_0
    \brief Un groupe de pions sans longueur
*/
/*! \def L_1
    \brief Un groupe de pions de longueur 1
*/
/*! \def L_2
    \brief Un groupe de pions de longueur 2
*/
/*! \def L_3
    \brief Un groupe de pions de longueur 3
*/
#define L_0 '0'
#define L_1 '1'
#define L_2 '2'
#define L_3 '3'

/*! \def ERROR_UNKNOWN
    \brief Renvoie -1 car l'erreur n'est pas reconnue
*/
/*! \def VALIDATION_OK
    \brief Operation est validé
*/
/*! \def ERROR_OUT_OF_BOUNDS
    \brief Mouvement jusqu'à en dehors du plateau
*/
/*! \def ERROR_MISSING_PIECE
    \brief Tentative de déplacement depuis une case vide
*/
/*! \def ERROR_WRONG_COLOR
    \brief Tentative de déplacement d'une pièce de la mauvaise couleur
*/
/*! \def ERROR_NO_LENGTH
    \brief Tentative de déplacement sans longueur, sur place NON UTILISE
*/
/*! \def ERROR_BLOCKED 
    \brief Tentative de déplacement d'une seule pièce vers un espace obstrué
*/
/*! \def ERROR_LINE_INCOMPLETE 
    \brief Tentative de déplacement d'une ligne qui contient un trou ou une piece d'une autre couleur
*/
/*! \def ERROR_NOT_ENOUGH_STRENGTH 
    \brief Tentative de déplacement en ligne contre une ligne trop forte
*/
/*! \def ERROR_ALLY_IN_THE_WAY 
    \brief Tentative de déplacement en ligne vers un allié
*/
/*! \def ERROR_TUPLE_INCOMPLETE 
    \brief Tentative de déplacement de 2 ou 3 pieces pas de la même couleur ou contenant du vide
*/
/*! \def ERROR_OBSTRUCTED 
    \brief Tentative de déplacement d'un doublet/triplet vers un espace obstrué
*/
#define ERROR_UNKNOWN -1
#define VALIDATION_OK 0
#define ERROR_OUT_OF_BOUNDS 1
#define ERROR_MISSING_PIECE 2
#define ERROR_WRONG_COLOR 3
#define ERROR_NO_LENGTH 4   
#define ERROR_BLOCKED 11
#define ERROR_LINE_INCOMPLETE 21
#define ERROR_NOT_ENOUGH_STRENGTH 22
#define ERROR_ALLY_IN_THE_WAY 23
#define ERROR_TUPLE_INCOMPLETE 31
#define ERROR_OBSTRUCTED 32

/*! \def TIME_LIMIT 
    \brief Le temps limite du jeu, défini à 900 secondes ou 15 minutes
*/
#define TIME_LIMIT 900

/*! \def STATE_RUNNING
    \brief L'état du jeu est en route
*/
/*! \def STATE_INITIALIZED
    \brief L'état du jeu est initialisé
*/ 
/*! \def STATE_TIMEOUT
    \brief Le temps limite du jeu est atteint, jeu terminé
*/ 
/*! \def STATE_FINISHED
    \brief Le jeu est terminé avec un gagnant
*/ 
/*! \def STATE_WON_BLANC
    \brief Blanc gagne, jeu terminé
*/ 
/*! \def STATE_WON_NOIR
    \brief Noir gagne, jeu terminé
*/
#define STATE_RUNNING 'R'
#define STATE_INITIALIZED 'I'
#define STATE_TIMEOUT 'T'
#define STATE_FINISHED 'F'
#define STATE_WON_BLANC 'B'
#define STATE_WON_NOIR 'N'

/*! \def COULEUR_VIDE
    \brief La case vide dans la grille
*/
/*! \def COULEUR_BLANC
    \brief la couleur de joueur ou de pion blanche
*/ 
/*! \def COULEUR_NOIR
    \brief la couleur de joueur ou de pion noire
*/
#define COULEUR_VIDE 'Z'
#define COULEUR_BLANC 'B'
#define COULEUR_NOIR 'N'

/*! \def MAX_CHILDREN
    \brief le nombre d'enfants max
*/
#define MAX_CHILDREN 300

/*! \def C1
    \brief Coefficient alpha dans le calcul de la fonction d'utilité
*/
/*! \def BETA
    \brief Coefficient beta dans le calcul de la fonction d'utilité
*/
/*! \def GAMMA
    \brief Coefficient gamma dans le calcul de la fonction d'utilité
*/
/*! \def THETA
    \brief Coefficient theta dans le calcul de la fonction d'utilité
*/
#define C1 1
#define C2 1
#define C3 1
#define C4 1
#define C5 1
#define C6 100

/*! \def GROUP_2
    \brief Nombre de points accordé à un joueur dans la focntion d'utilité lors d'un groupe de 2 pions
*/
/*! \def GROUP_3
    \brief Nombre de points accordé à un joueur dans la focntion d'utilité lors d'un groupe de 3 pions
*/
#define GROUP_2 6
#define GROUP_3 14

/*! \def DEPTH
    \brief Profondeur de l'arbre minimax
*/
#define DEPTH 4

#endif //IMM2223_GR6_CONST_H
