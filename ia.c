#include "ia.h"

//Vecteurs permettant de générer tous les mouvements possibles
/**
 * \var op
 * \brief vecteurs utilisés pour générer les mouvements
*/
/**
 * \var op_reversed
 * \brief vecteurs utilisés pour générer les mouvements (opposés à certains)
*/
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
 * \fn PCoord add_coord(Coord start, Coord end)
 * \brief additionne deux coordonnées
 * \param start la première coordonnée
 * \param end la deuxième coordonnée
 * \return les coordonées additionnées
*/
PCoord add_coord(Coord start, Coord end) {
    PCoord out = malloc(sizeof(PCoord));
    out->x = start.x + end.x;
    out->y = start.y + end.y;
    return out;
}

/**
 * \fn PMouvement ensemble_mouvement_possible(char** board,char color, int* nb_coup)
 * \brief Déterminer tous les mouvements possible pour une couleur
 * \param board Le jeu
 * \param player le joueur qui va devoir effectuer le mouvement
 * \param nb_coup Pointeur sur l'index du dernier mouvement de la liste
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
 * \fn void gen_mouvement(char** board, char player,Coord start,PMouvement liste_coup, int* nb_coup)
 * \brief Permet de remplir la liste des coups possibles qui sera retournée dans ensemble_mouvement_possible
 * \param board Le jeu
 * \param player Le joueur choisi
 * \param start Les coordonnées de pion de départ
 * \param liste_coup La liste des mouvements possibles
 * \param nb_coup Pointeur sur l'index du dernier mouvement de la liste
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
 * \fn void random_move(char** board, char player, PMouvement list_mvt, int count)
 * \brief Permet de choisir un coup aléatoire dans la liste de mouvement et le jouer
 * Cette fonction execute le coup aléatoire et le mouvement joué.
 * \param board La grille du jeu
 * \param player Le joueur
 * \param list_mvt Une liste des mouvements possibles
 * \param count L'index du dernier mouvement de la liste des mouvements possibles
*/
Mouvement random_move(char** board, char player, PMouvement list_mvt,int count) {
    int random = random_number(0, count);
    exec_mvt(board,player,list_mvt[random]);
    return list_mvt[random];
}

/**
 * \fn void play_random_move(char** board, char player)
 * \brief Executer ou jouer un coup aléatoire et le retourne sous forme de coordonnées en string
 * \param board Le jeu
 * \param player Le joueur choisi
*/
char* play_random_move(char** board, char player) {
    int count;
    PMouvement mvts_possibles = ensemble_mouvement_possible(board, player, &count);
    Mouvement mouvement = random_move(board, player, mvts_possibles,count);
    char* buffer = malloc(5*sizeof(char));
    mouvement_to_string(mouvement, buffer);
    return buffer;
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

/**
 * \fn PT_min(char** board, char player)
 * \brief donne le point en haut à gauche par rapport à tous les pions du joueur
 * \param board le plateau
 * \param player le joueur
 * \return les coordonnees du point extreme
*/
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

/**
 * \fn PT_max(char** board, char player)
 * \brief donne le point en bas à droite par rapport à tous les pions du joueur
 * \param board le plateau
 * \param player le joueur
 * \return les coordonnees du point extreme
*/
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

/**
 * \fn int score_density(char** board, char player)
 * \ingroup g1
 * \brief calcule la densité (à quel point les pièces du joueur sont rassemblées sur le plateau)
 * \param board le plateau
 * \param player le joueur
 * \return le score de densité du joueur sur le plateau
*/
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

 /** 
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

int minimax(char** board, int depth, int alpha, int beta, bool max_player, char active_player) {
    int nb_coup = 0;
    PMouvement liste_coup = ensemble_mouvement_possible(board, active_player, &nb_coup);

    char state = has_player_won(board);

    if (depth == 0) return score_utility(board, active_player);
    else if (state == COULEUR_NOIR || state == COULEUR_BLANC) {
        if (state == active_player) return INT_MAX;
        else return INT_MIN;
    }

    if (max_player) {
        int max_eval = INT_MIN;
        for (int i=0; i<nb_coup; i++) {
            char** copy = copy_board(board);
            exec_mvt(copy, active_player, liste_coup[i]);
            int eval = minimax(copy, depth - 1, alpha, beta, false, other_player(active_player));
            destroy_board(copy);
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        free(liste_coup);
        return max_eval;
    }
    else {
        int min_eval = INT_MAX;
        for (int i=0; i<nb_coup; i++) {
            char** copy = copy_board(board);
            exec_mvt(copy, active_player, liste_coup[i]);
            int eval = minimax(copy, depth - 1, alpha, beta, true, other_player(active_player));
            destroy_board(copy);
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        free(liste_coup);
        return min_eval;
    }
}

void terminator_move(char** board, char player) {
    int initial_score = minimax(board, DEPTH, INT_MIN, INT_MAX, true, player);
    int nb_coup;
    PMouvement liste_coup = ensemble_mouvement_possible(board, player, &nb_coup);
    for (int i=0; i<nb_coup; i++) {
        char** copy = copy_board(board);
        exec_mvt(copy, player, liste_coup[i]);
        int score = minimax(copy, DEPTH-1, INT_MIN, INT_MAX, false, other_player(player));
        destroy_board(copy);
        if (initial_score == score) {
            exec_mvt(board, player, liste_coup[i]);
            free(liste_coup);
            return;
        }
        free(liste_coup);
    }
}