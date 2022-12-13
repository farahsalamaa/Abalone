#include "ia.h"

//Vecteurs permettant de générer tous les mouvements possibles
Coord op[15] = {{0,1},{1,0},{0,-1},{-1,0},{0,2},{1,1},{-1,1},{2,0},{1,-1},{0,3},{1,2},{-1,2},{3,0},{2,1},{2,-1}};
Coord op_reversed[4] = {{0,-2},{-2,0},{0,-3},{-3,0}};

/**
 * \file ia.c
 * \brief Fonctions utilisées par l'Intelligence Artificielle
*/

/**
 * \fn int random_number(int min, int max)
 * \brief Genère un nombre aléatoire entre deux entiers
 * \param min Borne inférieure
 * \param max Borne supérieure
 * \return Renvoie un entier aléatoire compris entre les bornes inférieure et supérieure, bornes inclus
*/
int random_number(int min, int max) {
    int random;
    srand(time(NULL));
    random = (rand() % (max + 1 - min)) + min;
    return random;
}

/**
 * \fn void random_move(char** board, char player, PMouvement list_mvt)
 * \brief Permet de choisir un coup aléatoire dans la liste de mouvement et le jouer
 * Cette fonction execute le coup aléatoire et retourne rien.
 * \param board La grille du jeu
 * \param player Le joueur
 * \param list_mvt Une liste des mouvements possibles
 * \param count L'index du dernier mouvement de la liste des mouvements possibles
*/
void random_move(char** board, char player, PMouvement list_mvt,int count) {
    int random = random_number(0, count);
    exec_mvt(board,player,*(list_mvt+random));
}

//Fonction permettant de sommer deux vecteurs
PCoord add_coord(Coord start, Coord end) {
    PCoord out = malloc(sizeof(PCoord));
    out->x = start.x + end.x;
    out->y = start.y + end.y;
    return out;
}

/**
 * \fn PMouvement ensemble_mouvement_possible(char** board,char color)
 * \brief Déterminer tous les mouvements possible pour une couleur
 * \param board Le jeu
 * \param color Une couleur, blanc ou noir
 * \param nbr_coup Pointeur sur l'index du dernier mouvement de la liste
 * \return Renvoit une liste de tous les mouvements possibles
*/
PMouvement ensemble_mouvement_possible(char** board, char player, int* nb_coup) {
    //Initialise la liste récupérant l'ensemble des coups valides générés
    PMouvement liste_coup = malloc(MAX_CHILDREN*sizeof(Mouvement));
    *nb_coup = 0;

    //Parcourt le tableau à la recherche des pions de la bonne couleur
    for (int i=0; i<=7; i++) {
        for (int j=0; j<=7; j++) {
            if (board[i][j] == player) {
                gen_mouvement(board, player, (Coord){i,j}, liste_coup, nb_coup);
            }
        }
    }
    return liste_coup;
}

/**
 * \fn void generation_mouvement(char** board, char player,Coord start,Mouvement *liste)
 * \brief Permet de remplir la liste des coups possibles qui sera retournée dans ensemble_mouvement_possible
 * \param board Le jeu
 * \param player Le joueur choisi
 * \param start Les coordonnées de pion de départ
 * \param liste La liste des mouvements possibles
 * \param count Pointeur sur l'index du dernier mouvement de la liste
*/
void gen_mouvement(char** board, char player, Coord start, PMouvement liste_coup, int* nb_coup) {
    for (int i=0; i<15; i++) {
        Coord end = *add_coord(start,op[i]);
        Mouvement mouvement;
        mouvement.start = start; mouvement.end = end;
        if (!validate_mvt(board, player, mouvement)) {
            liste_coup[*nb_coup] = mouvement;
            (*nb_coup)++;
        }
    }
    for (int i=0; i<4; i++) {
        Coord copy_start = start;
        switch (i) {
            case 0:
                copy_start.y++;
                break;
            case 1:
                copy_start.x++;
                break;
            case 2:
                copy_start.y+=2;
                break;
            case 3:
                copy_start.x+=2;
                break;
        }
        Coord end = *add_coord(copy_start,op_reversed[i]);
        Mouvement mouvement;
        mouvement.start = copy_start; mouvement.end = end;
        if (!validate_mvt(board, player, mouvement)) {
            liste_coup[*nb_coup] = mouvement;
            (*nb_coup)++;

        }
    }
}

/**
 * \fn void play_random_move(char** board, char player)
 * \brief Executer ou jouer un coup aléatoire
 * \param board Le jeu
 * \param player Le joueur choisi
*/
void play_random_move(char** board, char player) {
    int count;
    PMouvement mvts_possibles = ensemble_mouvement_possible(board, player, &count);
    random_move(board, player, mvts_possibles,count);
}

/** \defgroup g1 Fonctions d'évaluation
 *  Fonctions pour déterminer la fonction d'évaluation
*/

/**
 * \fn int count_center(char** board, char player)
 * \ingroup g1
 * \brief Permet de compter le nombre de pions dans le cadre intérieur (donné par min/max)
 * \param board Le jeu
 * \param player Le joueur choisi
 * \return La somme de nombre de pions d'une couleur dans le cadre intérieur
*/
int count_center(char** board, char player) {
    int min = 2; int max = 5;
    int somme = 0;
    for (int i = min; i<=max; i++) {
        for (int j = min; j<=max; j++) {
            if (board[i][j] == player) somme++;
        }
    }
    return somme;
}

/**
 * \fn int count_padding(char** board, char player)
 * \ingroup g1
 * \brief Permet de compter le nombre de pions présents au niveau des bordures
 * \param board Le jeu
 * \param player Le joueur, blanc ou noir
 * \return La somme de nombre de pions d'une couleur présents au niveau des bordures
*/
int count_padding(char** board, char player) {
    return 14 - count_center(board,player);
}

PCoord PT_min(char** board, char player){
    int x_min=7;
    int y_min=7;
    PCoord pt_min = malloc(sizeof(PCoord));
    for (int i = 0; i<=7; i++) {
        for (int j = 0; j<=7; j++) {
            if (board[i][j] == player) {
                if (i<x_min){x_min=i;}
                if(j<y_min){y_min=j;}
            }
        }
    }
    pt_min->x=x_min;
    pt_min->y=y_min;
    return(pt_min);
}

PCoord PT_max(char** board, char player){
    int x_max=0;
    int y_max=0;
    PCoord pt_max = malloc(sizeof(PCoord));
    for (int i = 0; i<=7; i++) {
        for (int j = 0; j<=7; j++) {
            if (board[i][j] == player) {
                if (i>x_max){x_max=i;}
                if(j>y_max){y_max=j;}
            }
        }
    }
    pt_max->x=x_max;
    pt_max->y=y_max;
    return(pt_max);
}

int score_density(char** board, char player){
    
    PCoord pt_min = PT_min(board, player);
    PCoord pt_max = PT_max(board, player);
    int W =(pt_max->x - pt_min->x);/*!la Largeur de la surface (Width)*/
    int H =(pt_max->y - pt_min->y);// la longeur de la surface (height)
    int S = W*H ;
    double c = 14/S;
    if(c<0.25){return 0;}
    else if(c<0.50 && c>=0.25){return 2;}
    else if(c<0.75 && c>=0.50){return 3;}
    else if(c<1.0 && c>=0.75){return 5;}
}

 /* 
    
 * \fn int possible_attacks(char** board, char player)
 * \ingroup g1
 * \brief Calculer le nombre de coups d'attaque possibles
 * \param board Le jeu
 * \param player Le joueur
 * \return Le nombre de coups d'attaque possibles
*/
int possible_attacks(char** board, char player){
    int a;
    char opp = other_player(player);
    int m;
    PMouvement l=ensemble_mouvement_possible(board,player,&m);
    int i= m+1;
    for (int j=0;j<i; j++ ){
        int x=l[j].end.x;
        int y=l[j].end.y;
        if (board[x][y]==opp){a++;}
    }
    return a;
}

/**
 * \fn char other_player(char player)
 * \ingroup g1
 * \brief Déterminer la couleur du joueur opposé
 * \param player Le joueur
 * \return La couleur du joueur opposé
*/
char other_player(char player){
    char opp = COULEUR_BLANC;
    if (player == COULEUR_BLANC){opp=COULEUR_NOIR;}
    return opp;
}

/**
 * \fn int score_utility(char** board, char player)
 * \ingroup g1
 * \brief Calcul du score de l'utilité 
 * \param board Le jeu
 * \param player Le joueur
 * \return Une valeur d'utilité
*/
int score_utility(char** board, char player){
    int p1 = ALPHA*count_center(board, player)
            +BETA*count_padding(board, player)
            +GAMMA*score_density(board, player);
            +THETA*possible_attacks(board, player);

    int p2 = ALPHA*count_center(board,other_player(player))
            +BETA*count_padding(board,other_player(player))
            +GAMMA*score_density(board,other_player(player));
            +THETA*possible_attacks(board,other_player(player));

    return p1-p2;
}

int min(int a, int b) {
    if (a > b) return b;
    return a;
}

int max(int a, int b) {
    if (a < b) return b;
    return a;
}

PNode init_node(char** board, int nb_coup, int depth) {
    PNode node = malloc(sizeof(Node));
    node->children = malloc(MAX_CHILDREN*sizeof(PNode));
    node->nb_children = nb_coup;
    node->board = board;
    node->mouvement = (Mouvement){{0,0},{0,0}};
    node->depth = depth;
    node->value = 0;
    return node;
}

int minimax(PNode father, int alpha, int beta, bool max_player, char active_player) {
    father->nb_children = 0;
    PMouvement liste_coup = ensemble_mouvement_possible(father->board, active_player, &father->nb_children);

    char state = has_player_won(father->board);
    if (father->depth == 0 || (state == STATE_WON_NOIR || state == STATE_WON_BLANC)) {
        return score_utility(father->board, active_player);
    }

    for (int i=0; i<father->nb_children; i++) {
        char** copy = copy_board(father->board);
        exec_mvt(copy, active_player, liste_coup[i]);
        PNode child = init_node(copy, 0, father->depth-1);
        child->mouvement = liste_coup[i];
        father->children[i] = child;
    }
    free(liste_coup);

    if (max_player) {
        int max_eval = INT_MIN;
        for (int i=0; i<father->nb_children; i++) {
            father->value = minimax(father->children[i], alpha, beta, false, other_player(active_player));
            max_eval = max(max_eval, father->value);
            alpha = max(alpha, father->value);
            if (beta <= alpha) break;
        }
        return max_eval;
    } else {
        int min_eval = INT_MAX;
        for (int i=0; i<father->nb_children; i++) {
            father->value = minimax(father->children[i], alpha, beta, true, other_player(max_player));
            min_eval = min(min_eval, father->value);
            beta = min(beta, father->value);
            if (beta <= alpha) {
                break;
            }
        }
        return min_eval;
    }
}

Mouvement terminator(char** board, int depth, char active_player) {
    PNode root = init_node(board, 0, depth);
    int score = minimax(root, INT_MIN, INT_MAX, true, active_player);

    for (int i=0; i<root->nb_children; i++) {
        if (root->children[i]->value == score) {
            return root->children[i]->mouvement;
        }
    }
    return (Mouvement){{0,0},{0,0}};
}

void terminator_move(char** board, int depth, char active_player) {
    exec_mvt(board, active_player, terminator(board, depth, active_player));
}