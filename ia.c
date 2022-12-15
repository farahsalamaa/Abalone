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
 * \fn void add_coord(Coord start, Coord end, PCoord out)
 * \brief additionne deux coordonnées
 * \param start la première coordonnée
 * \param end la deuxième coordonnée
 * \param out le pointeur dans lequel les coordonnees ajoutes seront stockees
*/
void add_coord(Coord start, Coord end, PCoord out) {
    out->x = start.x + end.x;
    out->y = start.y + end.y;
}

/**
 * \fn void ensemble_mouvement_possible(char** board,char player, Mouvement liste_coup[MAX_CHILDREN], int* nb_coup)
 * \brief Déterminer tous les mouvements possible pour une couleur
 * \param board Le jeu
 * \param player le joueur qui va devoir effectuer le mouvement
 * \param liste_coup la liste des coups dans laquelle le nombre de coups va être stockée, qui doit être de taille MAX_CHILDREN
 * \param nb_coup Pointeur sur l'index du dernier mouvement de la liste
*/
void ensemble_mouvement_possible(char** board, char player, Mouvement liste_coup[MAX_CHILDREN], int* nb_coup) {
    *nb_coup = 0;

    //Parcourt le tableau à la recherche des pions de la bonne couleur
    for (int i=0; i<=7; i++) {
        for (int j=0; j<=7; j++) {
            if (board[i][j] == player) {
                gen_mouvement(board, player, (Coord){i,j}, liste_coup, nb_coup);
            }
        }
    }
}

/**
 * \fn void gen_mouvement(char** board, char player,Coord start, Mouvement liste_coup[MAX_CHILDREN], int* nb_coup)
 * \brief Permet de remplir la liste des coups possibles qui sera retournée dans ensemble_mouvement_possible
 * \param board Le jeu
 * \param player Le joueur choisi
 * \param start Les coordonnées de pion de départ
 * \param liste_coup La liste des mouvements dans laquelle sera stockée les coups générés, de taille MAX_CHILDREN
 * \param nb_coup Pointeur sur l'index du dernier mouvement de la liste
*/
void gen_mouvement(char** board, char player, Coord start, Mouvement liste_coup[MAX_CHILDREN], int* nb_coup) {
    for (int i=0; i<15; i++) {
        Coord end;
        add_coord(start,op[i],&end);
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
        Coord end;
        add_coord(copy_start,op_reversed[i],&end);
        Mouvement mouvement;
        mouvement.start = copy_start; mouvement.end = end;
        if (!validate_mvt(board, player, mouvement)) {
            liste_coup[*nb_coup] = mouvement;
            (*nb_coup)++;

        }
    }
}

/**
 * \fn Mouvement random_move(char** board, char player, Mouvement list_mvt[MAX_CHILDREN], int count)
 * \brief Permet de choisir un coup aléatoire dans la liste de mouvement et le jouer
 * Cette fonction execute le coup aléatoire et le mouvement joué.
 * \param board La grille du jeu
 * \param player Le joueur
 * \param list_mvt Une liste des mouvements possibles, de taille MAX_CHILDREN
 * \param count L'index du dernier mouvement de la liste des mouvements possibles
 * \return le mouvement effectué
*/
Mouvement random_move(char** board, char player, Mouvement list_mvt[MAX_CHILDREN], int count) {
    int random = random_number(0, count);
    exec_mvt(board,player,list_mvt[random]);
    return list_mvt[random];
}

/**
 * \fn Mouvement play_random_move(char** board, char player)
 * \brief Executer ou jouer un coup aléatoire et le retourne sous forme de mouvement
 * \param board Le jeu
 * \param player Le joueur choisi
 * \return le mouvement effectué
*/
Mouvement play_random_move(char** board, char player) {
    int count;
    Mouvement mvts_possibles[MAX_CHILDREN];
    ensemble_mouvement_possible(board, player, mvts_possibles, &count);
    Mouvement mouvement = random_move(board, player, mvts_possibles,count);
    return mouvement;
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
Coord PT_min(char** board, char player){
    int x_min=7;
    int y_min=7;
    Coord pt_min;
    for (int i = 0; i<=7; i++) {
        for (int j = 0; j<=7; j++) {
            if (board[i][j] == player) {
                if (i<x_min){x_min=i;}
                if(j<y_min){y_min=j;}
            }
        }
    }
    pt_min.x=x_min;
    pt_min.y=y_min;
    return(pt_min);
}

/**
 * \fn PT_max(char** board, char player)
 * \brief donne le point en bas à droite par rapport à tous les pions du joueur
 * \param board le plateau
 * \param player le joueur
 * \return les coordonnees du point extreme
*/
Coord PT_max(char** board, char player){
    int x_max=0;
    int y_max=0;
    Coord pt_max;
    for (int i = 0; i<=7; i++) {
        for (int j = 0; j<=7; j++) {
            if (board[i][j] == player) {
                if (i>x_max){x_max=i;}
                if(j>y_max){y_max=j;}
            }
        }
    }
    pt_max.x=x_max;
    pt_max.y=y_max;
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
    
    Coord pt_min = PT_min(board, player);
    Coord pt_max = PT_max(board, player);
    int W =(pt_max.x - pt_min.x);/*!la Largeur de la surface (Width)*/
    int H =(pt_max.y - pt_min.y);// la longeur de la surface (height)
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
    int a = 0;
    char opp = other_player(player);
    int m;
    Mouvement l[MAX_CHILDREN];
    ensemble_mouvement_possible(board,player,l,&m);
    int i= m+1;
    for (int j=0;j<i; j++ ){
        int x=l[j].end.x;
        int y=l[j].end.y;
        if (board[x][y]==opp){a++;}
    }
    return a;
}
/*! \fn score_row(char** board,char player)
    \brief Calcule le score des lignes du joueur actif selon la position de chaque pion
    \param board le jeu
    \param player le joueur actif
    \return le score des lignes du joueur actif
*/
int score_row(char** board, char player){
    int valeur[8]={-8,-4,-2,-1,-1,-2,-4,-8};
    int score=0;
    for (int i=0; i<8;i++){
        for (int j=0; j<8;j++){
            if (board[i][j]==player){
                score+=valeur[i];
            }
        } 
    }
    return score;
}
/*! \fn score_col(char** board,char player)
    \brief Calcule le score des colonnes du joueur actif selon la position de chaque pion
    \param board le jeu
    \param player le joueur actif
    \return le score des colonnes du joueur actif
*/
int score_col(char** board, char player){
    int valeur[8]={-8,-4,-2,-1,-1,-2,-4,-8};
    int score=0;
    for (int i=0; i<8;i++){
        for (int j=0; j<8;j++){
            if (board[i][j]==player){
                score+=valeur[j];
            }
        } 
    }
    return score;
}
/*! \fn score_group_row(char** board,char player)
    \brief Calcule le score des groupements de 2 ou 3 pions dans les lignes du joueur actif 
    \param board le jeu
    \param player le joueur actif
    \return le score des groupements de 2 ou 3 dans les lignes du joueur actif
*/
int score_group_row(char** board, char player){
    int score=0;
    for (int i=0; i<8;i++){
        int group_2=0;
        for (int j=0; j<8;j++){
            if (board[i][j]==player){
                if (board[i][j+1]==player){
                    score +=GROUP_2;
                    j++;
                    if(board[i][j+1]==player){
                        if(group_2==0){
                            score +=GROUP_3-GROUP_2;
                        }
                        else{
                            score=score-2*GROUP_2+GROUP_3;
                        }
                        j=7;
                    }
                    group_2++;
                }
            }
        }
    }
    return score;
}
/*! \fn score_group_col(char** board,char player)
    \brief Calcule le score des groupements de 2 ou 3 pions dans les colonnes du joueur actif
    \param board le jeu
    \param player le joueur actif
    \return le score des groupements de 2 ou 3 dans les colonnes du joueur actif
*/
int score_group_col(char** board, char player){
    int score=0;
    for (int j=0; j<8;j++){
        int group_2=0;
        for (int i=0; i<8;i++){
            if (board[i][j]==player){
                if (i==7){break;}
                if (board[i+1][j]==player){
                    score +=GROUP_2;
                    i++;
                    if (i==7){break;}
                    if(board[i+1][j]==player){
                        if(group_2==0){
                            score +=GROUP_3-GROUP_2;
                        }
                        else{
                            score=score-2*GROUP_2+GROUP_3;
                        }
                        i=7;
                    }
                    group_2++;
                }
            }
        }
    }
    return score;
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
    char player_2= other_player(player);

    int p1 = C1*score_row(board, player)
            +C2*score_col(board, player)
            +C3*score_group_row(board, player)
            +C4*score_group_col(board, player)
            +C5*score_density(board, player)
            +C6*possible_attacks(board,player);

    int p2 = C1*score_row(board, player_2)
            +C2*score_col(board, player_2)
            +C3*score_group_row(board, player_2)
            +C4*score_group_col(board, player_2)
            +C5*score_density(board, player_2)
            +C6*possible_attacks(board,player_2);

    return p1-p2;
}

/**
 * \fn int min(int a, int b)
 * \brief retourne la plus petite valeur entre a et b
 * \param a la première valeur
 * \param b la deuxième valeur
 * \return la plus petite valeur
*/
int min(int a, int b) {
    if (a > b) return b;
    return a;
}

/**
 * \fn int max(int a, int b)
 * \brief retourne la plus grande valeur entre a et b
 * \param a la première valeur
 * \param b la deuxième valeur
 * \return la plus grande valeur
*/
int max(int a, int b) {
    if (a < b) return b;
    return a;
}

int max_mouv(int a, int b, PMouvement mouvement, Mouvement mvt_to_copy) {
    if (a < b) {
        *mouvement = mvt_to_copy;
        return b;
    }
    return a;
}

/**
 * \fn int minimax(char** board, int depth, int alpha, int beta, bool max_player, char active_player)
 * \brief renvoie le score du meilleur plateau à la profondeur donnée
 * \param board le plateau
 * \param depth la profondeur de l'arbre minimax
 * \param alpha le alpha de l'élaguage alpha-beta
 * \param beta le beta de l'élaguage alpha-beta
 * \param max_player le plateau est à générer pour l'ia
 * \param active_player le joueur actif
 * \return le score du meilleur plateau trouvé
*/
int minimax(char** board, int depth, int alpha, int beta, bool max_player, char active_player, PMouvement mouvement) {
    int nb_coup = 0;
    Mouvement liste_coup[MAX_CHILDREN];
    ensemble_mouvement_possible(board, active_player, liste_coup, &nb_coup);

    char state = has_player_won(board);
    if (depth == 0) return score_utility(board, active_player);
    else if (state == STATE_WON_BLANC && active_player == COULEUR_BLANC) return INT_MAX;
    else if (state == STATE_WON_BLANC && active_player == COULEUR_NOIR) return INT_MIN;
    else if (state == STATE_WON_NOIR && active_player == COULEUR_NOIR) return INT_MAX;
    else if (state == STATE_WON_NOIR && active_player == COULEUR_BLANC) return INT_MIN;

    if (max_player) {
        int max_eval = INT_MIN;
        for (int i=0; i<nb_coup; i++) {
            char** copy = copy_board(board);
            exec_mvt(copy, active_player, liste_coup[i]);
            int eval = minimax(copy, depth - 1, alpha, beta, false, other_player(active_player), mouvement);
            destroy_board(copy);
            if (eval > max_eval && depth == DEPTH) *mouvement = liste_coup[i];
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return max_eval;
    }
    else {
        int min_eval = INT_MAX;
        for (int i=0; i<nb_coup; i++) {
            char** copy = copy_board(board);
            exec_mvt(copy, active_player, liste_coup[i]);
            int eval = minimax(copy, depth - 1, alpha, beta, true, other_player(active_player), mouvement);
            destroy_board(copy);
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return min_eval;
    }
}

/**
 * \fn void terminator_move(char** board, char player)
 * \brief fait jouer un coup à l'algorithme minimax
 * \param board le plateau
 * \param player le joueur qui doit jouer
 * \return le mouvement joué
*/
Mouvement terminator_move(char** board, char player) {
    if (DEPTH == 0) {
        return play_random_move(board, player);
    } else {
        Mouvement mouvement;
        int score = minimax(board, DEPTH, INT_MIN, INT_MAX, true, player, &mouvement);
        exec_mvt(board, player, mouvement);
        return mouvement;
    }
}
            