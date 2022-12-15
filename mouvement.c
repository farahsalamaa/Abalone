#include "mouvement.h"

/**
 * \file mouvement.c
 * \brief les fonctions pour definir, valider et executer un mouvement
*/

/*! \fn area_mvt(Mouvement mvt)
    \brief Calcule la surface réalisée par le mouvement
    \param mvt Le mouvement donné
    \return La surface réalisée par le mouvement
*/
int area_mvt(Mouvement mvt) {
    return (abs(mvt.start.x - mvt.end.x) + 1) * (abs(mvt.start.y - mvt.end.y) + 1);
}

/**
 * \fn type_mvt(Mouvement mvt)
 * \brief Déterminer le type du mouvement, ligne ou largeur
 * \param mvt Le mouvement donné
 * \return MVT_LIGNE ou MVT_LARGEUR, explicatifs
*/
char type_mvt(Mouvement mvt) {

    //Si une composante est répétée en x ou en y et que la surface est comprise entre 2 et 4 → mouvement en ligne
    if ((mvt.start.x == mvt.end.x || mvt.start.y == mvt.end.y) && (area_mvt(mvt) >= 2 && area_mvt(mvt) <= 4)) return MVT_LIGNE;

    //Si les deux composantes sont différentes et que la surface est égale à 4 ou 6 → mouvement en largeur
    else if ((mvt.start.x != mvt.end.x && mvt.start.y != mvt.end.y) && (area_mvt(mvt) == 4 || area_mvt(mvt) == 6)) return MVT_LARGEUR;

    //Renvoie une erreur si le mouvement n'est pas valide
    else return ERROR_NOT_A_MOVEMENT;
}

/**
 * \fn orientation_grp(Mouvement mvt)
 * \brief Déterminer si le mouvement d'un groupe de pions est horizontal ou vertical ou non
 * \param mvt Le mouvement
 * \return HORIZONTAL ou VERTICAL
*/
char orientation_grp(Mouvement mvt){
    if (mvt.start.x == mvt.end.x) return HORIZONTAL;
    else if (mvt.start.y == mvt.end.y) return VERTICAL;
    else return ERROR_NOT_ALIGNED;
}

/**
 * \fn length_mvt(Mouvement mvt)
 * \brief Calculer la longueur d'un groupe de pion en mouvement
 * \param mvt Le mouvement donné
 * \return L_0, L_1, L_2, ou L_3 en fonction de la longueur
*/
char length_mvt(Mouvement mvt){
    int length = 0;
    int lenX = abs(mvt.start.x - mvt.end.x);
    int lenY = abs(mvt.start.y - mvt.end.y);
    if (type_mvt(mvt) == MVT_LARGEUR){
        if (lenX == 0 || lenY == 0)
            {length = 1;}
        else if (lenX >= lenY)
            {length = lenX+1;}
        else length = lenY+1;
    }
    else {
        if (lenX==0)
            {length = lenY;}
        else length = lenX;
    }
    switch(length){
        case 1:
            return L_1;
            break;
        case 2:
            return L_2;
            break;
        case 3:
            return L_3;
            break;
        default:
            return L_0;
            break;
    }

}

/**
 * \fn voisin_carre(char** board, Mouvement mvt)
 * \brief Déterminer le pion voisin dans un carré (cas specifique)
 * \param board Le jeu
 * \param mvt Le mouvement donné
 * \return Les coordonnées du voisin d'un pion en mouvement carré
*/
Coord voisin_carre(char** board, Mouvement mvt){
    Coord v;
    int x0 = mvt.start.x;
    int y0 = mvt.start.y;
    int x1 = mvt.end.x;
    int y1 = mvt.end.y;
    v.x = x0;
    v.y = y1;
    if(x0 > 7 || y0 > 7 || x1 > 7 || y1 > 7 
    || x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0){
        return v;
    }
    if (board[x0][y0] == board[x0][y1]){
        v.x = x0;
        v.y = y1;
        return v;
    }
    else if (board[x0][y0] == board[x1][y0]){
        v.x = x1;
        v.y = y0;
        return v;
    }
    return v;
}

/**
 * \fn direction_mvt(char** board, Mouvement mvt)
 * \brief Déterminer la direction du mouvement
 * \param board Le tableau représentant le plateau
 * \param mvt Le mouvement donné
 * \return DIR_UP, DIR_RIGHT, DIR_DOWN ou DIR_LEFT
*/
char direction_mvt(char** board, Mouvement mvt){
    char len = length_mvt(mvt);
    char type = type_mvt(mvt);
    switch (len){
        case L_1:
            if (mvt.start.x == mvt.end.x){
                if (mvt.start.y > mvt.end.y){return DIR_LEFT;}
                else if (mvt.start.y < mvt.end.y){return DIR_RIGHT;}
            }
            else if (mvt.start.y == mvt.end.y){
                if (mvt.start.x > mvt.end.x){return DIR_UP;}
                else if (mvt.start.x < mvt.end.x){return DIR_DOWN;}
            }
            break;
        case L_2:
            if (type == MVT_LARGEUR){
                Coord voisin = voisin_carre(board, mvt);
                if (voisin.x == mvt.start.x){
                    if (mvt.start.x > mvt.end.x){return DIR_UP;}
                    else if (mvt.start.x < mvt.end.x){return DIR_DOWN;}
                }
                else if (voisin.y == mvt.start.y){
                    if (mvt.start.y > mvt.end.y){return DIR_LEFT;}
                    else if (mvt.start.y < mvt.end.y){return DIR_RIGHT;}
                }
            }
            else if (type == MVT_LIGNE){
                if (mvt.start.x == mvt.end.x){
                    if (mvt.start.y > mvt.end.y){return DIR_LEFT;}
                    else if (mvt.start.y < mvt.end.y){return DIR_RIGHT;}
                }
                if (mvt.start.y == mvt.end.y){
                    if (mvt.start.x > mvt.end.x){return DIR_UP;}
                    else if (mvt.start.x < mvt.end.x){return DIR_DOWN;}
                }
            }
            break;
        case L_3: ;
            if (type == MVT_LARGEUR){
                int diff_X = mvt.end.x - mvt.start.x;
                int diff_Y = mvt.end.y - mvt.start.y;
                if (diff_X == 1){return DIR_DOWN;}
                else if (diff_X == -1){return DIR_UP;}
                else if (diff_Y == 1){return DIR_RIGHT;}
                else if (diff_Y == -1){return DIR_LEFT;}
            }
            else if (type == MVT_LIGNE){
                if (mvt.start.x == mvt.end.x){
                    if (mvt.start.y > mvt.end.y){return DIR_LEFT;}
                    else if (mvt.start.y < mvt.end.y){return DIR_RIGHT;}
                }
                else if (mvt.start.y == mvt.end.y){
                    if (mvt.start.x > mvt.end.x){return DIR_UP;}
                    else if (mvt.start.x < mvt.end.x){return DIR_DOWN;}
                }
            }
    }
    return -1; // si correspond à aucun cas
}

/**
 * \fn validate_mvt_piece(char** board,char player, Mouvement mvt)
 * \brief Vérifier si le mouvement donné contient le pion appartenant au joueur
 * \param board Le jeu
 * \param player Le joueur qui effectue le mouvement
 * \param mvt Le mouvement donné
 * \return ERROR_MISSING_PIECE s'il n'ya pas de pion, ERROR_WRONG_COLOR si pion n'appartient pas au joueur et VALIDATION_OK sinon
*/
int validate_mvt_piece(char** board,char player, Mouvement mvt){
    if (board[mvt.start.x][mvt.start.y] != player){
        if (board[mvt.start.x][mvt.start.y] == 'Z')
        {
            return ERROR_MISSING_PIECE;
        }else{
            return ERROR_WRONG_COLOR;
        }
    }else{
        return VALIDATION_OK;
    }
}

/**
 * \fn validate_mvt_bounds(Mouvement mvt)
 * \brief Vérifier si le mouvement donné reste bien dans la grille
 * \param mvt Le mouvement donné
 * \return ERROR_OUT_OF_BOUNDS si erreur et VALIDATION_OK sinon
*/
int validate_mvt_bounds(Mouvement mvt){
    if (mvt.start.x > 7 || mvt.start.x < 0){
        return ERROR_OUT_OF_BOUNDS;
    }else if(mvt.start.y > 7 || mvt.start.y < 0){
        return ERROR_OUT_OF_BOUNDS;
    }else if(mvt.end.x > 7 || mvt.end.x < 0){
        return ERROR_OUT_OF_BOUNDS;
    }else if(mvt.end.y > 7 || mvt.end.y < 0){
        return ERROR_OUT_OF_BOUNDS;
    }else{
        return VALIDATION_OK;
    }
    
}

/**
 * \fn validate_mvt_ligne_1(char** board, Mouvement mvt)
 * \brief Vérifier si le mouvement d'un pion n'est pas bloqué par un autre pion
 * \param board Le tableau representant le plateau
 * \param mvt Le mouvement donné
 * \return ERROR_BLOCKED s'il est bloqué et VALIDATION_OK sinon
*/
int validate_mvt_ligne_1(char** board, Mouvement mvt){
    if (board[mvt.end.x][mvt.end.y] != COULEUR_VIDE){
        return ERROR_BLOCKED;
    }
    return VALIDATION_OK;   
}

/**
 * \fn validate_mvt_ligne_2(char** board, char player, Mouvement mvt)
 * \brief Vérifier si le mouvement en ligne de deux pion n'est pas bloqué par un autre pion
 * \param board Le tableau representant le plateau
 * \param player Le joueur qui effectue le mouvement
 * \param mvt Le mouvement donné
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un code d'erreur correspondant 
*/
int validate_mvt_ligne_2(char** board, char player, Mouvement mvt){
    int modX = 0;
    int modY = 0;
    
    switch (direction_mvt(board, mvt)){
        case DIR_UP:
            modX = -1;
            break;
        case DIR_DOWN:
            modX = 1;
            break;
        case DIR_LEFT:
            modY = -1;
            break;
        case DIR_RIGHT:
            modY = 1;
            break;
    }

    if (board[mvt.start.x+modX][mvt.start.y+modY] != player){
        return ERROR_LINE_INCOMPLETE;
    }

    if (board[mvt.end.x][mvt.end.y] == player){
        return ERROR_ALLY_IN_THE_WAY;
    }else if(board[mvt.end.x][mvt.end.y] == COULEUR_VIDE){
        return VALIDATION_OK;
    }else{
        if (direction_mvt(board, mvt) == DIR_UP || direction_mvt(board, mvt) == DIR_DOWN){
            if (mvt.end.x+modX < 0 || mvt.end.x+modX > 7){
                return VALIDATION_OK;
            }else if(board[mvt.end.x+modX][mvt.end.y] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(board[mvt.end.x+modX][mvt.end.y] == player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            return ERROR_NOT_ENOUGH_STRENGTH;
        }else{
            if (mvt.end.y+modY < 0 || mvt.end.y+modY > 7){
                return VALIDATION_OK;
            }else if(board[mvt.end.x][mvt.end.y+modY] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(board[mvt.end.x][mvt.end.y+modY] == player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            return ERROR_NOT_ENOUGH_STRENGTH;
        }
    }
    return ERROR_UNKNOWN;
}

/**
 * \fn validate_mvt_ligne_3(char** board, char player, Mouvement mvt)
 * \brief Vérifier si le mouvement en ligne de trois pion n'est pas bloqué par un autre pion
 * \param board Le tableau representant le plateau
 * \param player Le joueur qui effectue le mouvement
 * \param mvt Le mouvement donné
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un code d'erreur correspondant
*/
int validate_mvt_ligne_3(char** board, char player, Mouvement mvt){
    int modX = 0;
    int modY = 0;
    
    switch (direction_mvt(board, mvt)){
        case DIR_UP:
            modX = -1;
            break;
        case DIR_DOWN:
            modX = 1;
            break;
        case DIR_LEFT:
            modY = -1;
            break;
        case DIR_RIGHT:
            modY = 1;
            break;
    }

    if (board[mvt.start.x+modX][mvt.start.y+modY] != player){
        return ERROR_LINE_INCOMPLETE;
    }
    if (board[mvt.start.x+2*modX][mvt.start.y+2*modY] != player){
        return ERROR_LINE_INCOMPLETE;
    }

    if (board[mvt.end.x][mvt.end.y] == player){
        return ERROR_ALLY_IN_THE_WAY;
    }else if(board[mvt.end.x][mvt.end.y] == COULEUR_VIDE){
        return VALIDATION_OK;
    }else{
        if (direction_mvt(board, mvt) == DIR_UP || direction_mvt(board, mvt) == DIR_DOWN){
            if (mvt.end.x+modX < 0 || mvt.end.x+modX > 7){
                return VALIDATION_OK;
            }else if(board[mvt.end.x+modX][mvt.end.y] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(board[mvt.end.x+modX][mvt.end.y] == player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            if (mvt.end.x+2*modX < 0 || mvt.end.x+2*modX > 7){
                return VALIDATION_OK;
            }else if(board[mvt.end.x+2*modX][mvt.end.y] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(board[mvt.end.x+2*modX][mvt.end.y] == player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            return ERROR_NOT_ENOUGH_STRENGTH;
        }else{
            if (mvt.end.y+modY < 0 || mvt.end.y+modY > 7){
                return VALIDATION_OK;
            }else if(board[mvt.end.x][mvt.end.y+modY] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(board[mvt.end.x][mvt.end.y+modY] == player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            if (mvt.end.y+2*modY < 0 || mvt.end.y+2*modY > 7){
                return VALIDATION_OK;
            }else if(board[mvt.end.x][mvt.end.y+2*modY] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(board[mvt.end.x][mvt.end.y+2*modY] == player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            return ERROR_NOT_ENOUGH_STRENGTH;
        }
    }
    return ERROR_UNKNOWN;
}

/**
 * \fn validate_mvt_largeur_1(char** board, Mouvement mvt)
 * \brief Vérifier si le mouvement d'un pion n'est pas bloqué par un autre pion
 * \param board Le tableau représentant le plateau
 * \param mvt Le mouvement donné
 * \return VALIDATION_OK s'il n'est pas bloqué, ERROR_BLOCKED sinon 
*/
int validate_mvt_largeur_1(char** board, Mouvement mvt){
    if (board[mvt.end.x][mvt.end.y] != COULEUR_VIDE){
        return ERROR_BLOCKED;
    }
    return VALIDATION_OK;
}

/**
 * \fn validate_mvt_largeur_2(char** board, char player, Mouvement mvt)
 * \brief Vérifier si le mouvement en largeur de deux pion n'est pas bloqué par un autre pion
 * \param board Le tableau de la partie
 * \param player Le joueur qui effectue le mouvement
 * \param mvt Le mouvement donné
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un code d'erreur correspondant 
*/
int validate_mvt_largeur_2(char** board, char player, Mouvement mvt){
    int modX = 0;
    int modY = 0;
    
    switch (direction_mvt(board, mvt)){
        case DIR_UP:
            modX = -1;
            break;
        case DIR_DOWN:
            modX = 1;
            break;
        case DIR_LEFT:
            modY = -1;
            break;
        case DIR_RIGHT:
            modY = 1;
            break;
    }

    if(direction_mvt(board, mvt) == DIR_UP || direction_mvt(board, mvt) == DIR_DOWN){
        int progression =  mvt.end.y - mvt.start.y;
        
        if (board[mvt.start.x+modX][mvt.start.y] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (board[mvt.start.x][mvt.start.y+progression] != player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (board[mvt.start.x+modX][mvt.start.y+progression] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        return VALIDATION_OK;
    }else{
        int progression =  mvt.end.x - mvt.start.x;
        
        if (board[mvt.start.x][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }
        
        if (board[mvt.start.x+progression][mvt.start.y] != player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (board[mvt.start.x+progression][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        return VALIDATION_OK;
    }

    return ERROR_UNKNOWN;
}

/**
 * \fn validate_mvt_largeur_3(char** board, char player, Mouvement mvt)
 * \brief verifier si le mouvement en largeur de trois pion n'est pas bloqué par un autre pion
 * \param board Le tableau de la partie
 * \param player Le joueur qui effectue le mouvement
 * \param mvt Le mouvement donné
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un code d'erreur correspondant 
*/
int validate_mvt_largeur_3(char** board, char player, Mouvement mvt){
    int modX = 0;
    int modY = 0;
    
    switch (direction_mvt(board, mvt)){
        case DIR_UP:
            modX = -1;
            break;
        case DIR_DOWN:
            modX = 1;
            break;
        case DIR_LEFT:
            modY = -1;
            break;
        case DIR_RIGHT:
            modY = 1;
            break;
    }

    if(direction_mvt(board, mvt) == DIR_UP || direction_mvt(board, mvt) == DIR_DOWN){
        int progression =  (mvt.end.y - mvt.start.y)/2;
        if (board[mvt.start.x+modX][mvt.start.y] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (board[mvt.start.x][mvt.start.y+progression] != player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (board[mvt.start.x+modX][mvt.start.y+progression] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (board[mvt.start.x][mvt.start.y+2*progression] != player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (board[mvt.start.x+modX][mvt.start.y+2*progression] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        return VALIDATION_OK;
    }else{
        int progression =  (mvt.end.x - mvt.start.x)/2;
        if (board[mvt.start.x][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (board[mvt.start.x+progression][mvt.start.y] != player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (board[mvt.start.x+progression][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (board[mvt.start.x+2*progression][mvt.start.y] != player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (board[mvt.start.x+2*progression][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        return VALIDATION_OK;
    }

    return ERROR_UNKNOWN;
}

/**
 * \fn validate_mvt(char** board, char player, Mouvement mvt)
 * \brief Vérifier si le mouvement est valide
 * \param board Le tableau de la partie
 * \param player Le joueur qui effectue le mouvement
 * \param mvt Le mouvement donné
 * \return VALIDATION_OK si valide, sinon un code d'erreur correspondant 
*/
int validate_mvt(char** board, char player, Mouvement mvt){
    /*Erreurs générales*/
    int error = validate_mvt_bounds(mvt);
    if(error != VALIDATION_OK){return error;}
    error = validate_mvt_piece(board, player, mvt);
    if(error != VALIDATION_OK){return error;}
    
    if (length_mvt(mvt) == L_0){
        return ERROR_NO_LENGTH;
    }

    switch (type_mvt(mvt))
    {
    case MVT_LIGNE:
        switch (length_mvt(mvt))
        {
        case L_1:
            return validate_mvt_ligne_1(board, mvt);
            break;

        case L_2:
            return validate_mvt_ligne_2(board, player, mvt);
            break;

        case L_3:
            return validate_mvt_ligne_3(board, player, mvt);
            break;
        
        default:
            return ERROR_UNKNOWN;
            break;
        }
        break;

    case MVT_LARGEUR:
        switch (length_mvt(mvt))
        {
        case L_1:
            return validate_mvt_largeur_1(board, mvt);
            break;

        case L_2:
            return validate_mvt_largeur_2(board, player, mvt);
            break;

        case L_3:
            return validate_mvt_largeur_3(board, player, mvt);
            break;
        
        default:
            return -1;
            break;
        }
        break;
    
    default:
        return ERROR_UNKNOWN;
        break;
    }
}

/**
 * \fn int string_to_mouvement(char* string, PMouvement mvt)
 * \brief Changement de la chaine donnée par utilisateur en mouvement
 * \param string La chaine de caractère à convertir
 * \param mvt Le mouvement qui devient le mouvement converti.
 * \return 0 si les coordonnées existe dans la grille, 1 sinon
*/
int string_to_mouvement(char* string, PMouvement mvt){
    mvt->start.x = string[0]-65;
    mvt->start.y = string[1]-49;
    mvt->end.x = string[3]-65;
    mvt->end.y = string[4]-49;
    if(mvt->start.x > 7 || mvt->start.y > 7 || mvt->end.x > 7 || mvt->end.y > 7 || string[2]!=':' 
    || mvt->start.x < 0 || mvt->start.y < 0 || mvt->end.x < 0 || mvt->end.y < 0){
        return ERROR_OUT_OF_BOUNDS;   
    }else{
        return 0;
    }
}

/**
 * \fn int mouvement_to_string(Mouvement mvt, char* buffer)
 * \brief Changement des coordonnées 2D en une chaine 
 * \param mvt Le mouvement à convertir
 * \param buffer La chaine de caractère qui va recevoir la conversion
 * \return 0 si le buffer peut acceuillir la chaine, 1 sinon
*/
int mouvement_to_string(Mouvement mvt, char* buffer){
    buffer[0] = mvt.start.x+65;
    buffer[1] = mvt.start.y+49;
    buffer[2] = ':';
    buffer[3] = mvt.end.x+65;
    buffer[4] = mvt.end.y+49;
    buffer[5] = '\0';
    return 0;
}

/**
 * \fn finalise_mvt(char** board, char player,Mouvement mvt)
 * \brief Finaliser un mouvement et l'executer
 * \param board Le tableau de la partie
 * \param player Le joueur qui effectue le mouvement
 * \param mvt Le mouvement donné
 * \return VALIDATION_OK si mouvement validé, error sinon
*/
int finalise_mvt(char** board, char player ,Mouvement mvt){
    Mouvement d;
    int error = validate_mvt(board, player,mvt);
    if(!error){
        exec_mvt(board, player ,mvt);
        d = mvt;
        return VALIDATION_OK;
    }else{
        return error;
    }
}

/**
 * \fn push_mvt(char** board, char player,Mouvement p,int out)
 * \brief Fonction qui effectue la poussée des pions ADVERSES
 * \param board Le tableau de la partie
 * \param player Le joueur actif
 * \param p Le mouvement donné
 * \param out Est-ce que le premier pion poussé sort
*/
void push_mvt(char** board, char player,Mouvement p,int out){
    //on ne pousse pas le premier pion en dehors
    if (out==0){
        if (board[p.end.x][p.end.y]!=COULEUR_VIDE){
            //mouvement du deuxième piont poussé
            Mouvement pushed;
            pushed.start.x = p.end.x;
            pushed.start.y = p.end.y;
            //le deuxième pion sort
            int pushedout = 1;
            // trace();
            // debug("deplacement du premier pion adverse : (%d,%d) to (%d,%d)",p.start.x,p.start.y,p.end.x,p.end.y);
            // debug("direction dumouvement du premier pion : %c",direction_mvt(board, p));
            if (direction_mvt(board, p)==DIR_UP){
                if (pushed.start.x>0){
                pushed.end.x = p.end.x-1;
                pushed.end.y = p.end.y;
                //le deuxième pion le sort pas
                pushedout=0;
                }
            }
            if (direction_mvt(board, p)==DIR_DOWN){
                if (pushed.start.x<7){
                    pushed.end.x = p.end.x+1;
                    pushed.end.y = p.end.y;
                    //le deuxième pion le sort pas
                    pushedout=0;
                }
            }
            if (direction_mvt(board, p)==DIR_LEFT){
                if (pushed.start.y>0){
                pushed.end.x = p.end.x;
                pushed.end.y = p.end.y-1;
                //le deuxième pion le sort pas
                pushedout=0;
                }
            }
            if (direction_mvt(board, p)==DIR_RIGHT){
                if (pushed.start.y<7){
                pushed.end.x = p.end.x;
                pushed.end.y = p.end.y+1;
                //le deuxième pion le sort pas
                pushedout=0;
                }
            }
            if (player==COULEUR_NOIR){
                board[p.end.x][p.end.y]=COULEUR_BLANC;
                if (pushedout==0){
                    board[pushed.end.x][pushed.end.y]=COULEUR_BLANC;
                }
            }
            if (player==COULEUR_BLANC){
                board[p.end.x][p.end.y]=COULEUR_NOIR;
                if (pushedout==0){
                board[pushed.end.x][pushed.end.y]=COULEUR_NOIR;
                }
            }
        }
        else {
            if (player==COULEUR_NOIR){
            board[p.end.x][p.end.y]=COULEUR_BLANC;
            }
            if (player==COULEUR_BLANC){
            board[p.end.x][p.end.y]=COULEUR_NOIR;
            }
        }
    }
    else {
    }
}

//fonction qui prend le plateau en entrée, le modifie avec le nouveau mvt et retourne le plateau actualisé
//Appelle la fct push_mvt si un pion sort du plateau (à terminer)
/**
 * \fn exec_mvt(char** board, char player,Mouvement p)
 * \brief Fonction qui effectue le mouvement
 * \param board Le tableau de la partie
 * \param player Le joueur actif
 * \param p Le mouvement donné
 * \return Le board actualisé avec le mouvement effectué
*/
char** exec_mvt(char** board, char player, Mouvement p){
    //longueur 1
    if (length_mvt(p)==L_1){
        board[p.start.x][p.start.y]=COULEUR_VIDE;
        board[p.end.x][p.end.y]=player;
    }
    //longueur > 1
    else {
        //LIGNE
        if (type_mvt(p)==MVT_LIGNE){     
            //On vide le début du mouvement
            board[p.start.x][p.start.y]=COULEUR_VIDE;

            //On pousse qqchose
            if (board[p.end.x][p.end.y]!=COULEUR_VIDE){
                //Mouvement de poussée du pion qui gêne
                Mouvement mvtpush;
                mvtpush.start.x = p.end.x;
                mvtpush.start.y = p.end.y;

                //direction_mvt(board, mvtpush) = direction_mvt(board, p); let's see if it's really useful
                
                //on pousse le pion suivant en dehors
                int out=1;
                if (direction_mvt(board, p)==DIR_UP){
                    if (mvtpush.start.x!=0){
                        mvtpush.end.x = p.end.x-1;
                        mvtpush.end.y = p.end.y;
                        //on ne pousse pas le pion suivant en dehors
                        out = 0;
                    }
                }
                if (direction_mvt(board, p)==DIR_DOWN){
                    if (mvtpush.start.x!=7){
                        mvtpush.end.x = p.end.x+1;
                        mvtpush.end.y = p.end.y;
                        //on ne pousse pas le pion suivant en dehors
                        out = 0;
                    }
                }
                if (direction_mvt(board, p)==DIR_LEFT){
                    if (mvtpush.start.y!=0){
                        mvtpush.end.x = p.end.x;
                        mvtpush.end.y = p.end.y-1;
                        //on ne pousse pas le pion suivant en dehors
                        out = 0;
                    }
                }
                if (direction_mvt(board, p)==DIR_RIGHT){
                    if (mvtpush.start.y!=7){
                        mvtpush.end.x = p.end.x;
                        mvtpush.end.y = p.end.y+1;
                        //on ne pousse pas le pion suivant en dehors
                        out = 0;
                    }
                }
                //On effectue la poussée du pion suivant
                push_mvt(board, player, mvtpush, out);
                //on pousse le nôtre
                board[p.end.x][p.end.y]=player;
            }
            //On ne pousse rien (simple transfert)
            else {board[p.end.x][p.end.y]=player;
            }
        }
        else if (type_mvt(p)==MVT_LARGEUR){   //mvt latéral
            if (direction_mvt(board, p)==DIR_UP){   //direction vers le haut
                board[p.start.x][p.start.y]=COULEUR_VIDE;
                board[p.end.x][p.end.y]=player;
                board[p.start.x-1][p.start.y]=player;
                if (p.start.y<p.end.y){   //comparaison de la valeur en Y
                    board[p.start.x][p.start.y+1]=COULEUR_VIDE;
                    if (length_mvt(p)==L_3) {
                        board[p.start.x][p.start.y+2]=COULEUR_VIDE;
                        board[p.start.x-1][p.start.y+1]=player;
                    }
                }
                else { 
                    board[p.start.x][p.start.y-1]=COULEUR_VIDE;
                    if (length_mvt(p)==L_3) {
                        board[p.start.x][p.start.y-2]=COULEUR_VIDE;
                        board[p.start.x-1][p.start.y-1]=player;
                    }
                }
            }
            if (direction_mvt(board, p)==DIR_DOWN){          //direction vers le bas
                board[p.start.x][p.start.y]=COULEUR_VIDE;
                board[p.end.x][p.end.y]=player;
                board[p.start.x+1][p.start.y]=player;
                if (p.start.y<p.end.y){   //comparaison de la valeur en Y
                    board[p.start.x][p.start.y+1]=COULEUR_VIDE;
                    if (length_mvt(p)==L_3) {
                        board[p.start.x][p.start.y+2]=COULEUR_VIDE;
                        board[p.start.x+1][p.start.y+1]=player;
                    }
                }
                else { 
                    board[p.start.x][p.start.y-1]=COULEUR_VIDE;
                    if (length_mvt(p)==L_3) {
                        board[p.start.x][p.start.y-2]=COULEUR_VIDE;
                        board[p.start.x+1][p.start.y-1]=player;
                    }
                }
            }
            if (direction_mvt(board, p)==DIR_LEFT){           //direction vers la gauche
                board[p.start.x][p.start.y]=COULEUR_VIDE;
                board[p.end.x][p.end.y]=player;
                board[p.start.x][p.start.y-1]=player;
                if (p.start.x<p.end.x){ 
                    board[p.start.x+1][p.start.y]=COULEUR_VIDE;
                    if (length_mvt(p)==L_3) {
                        board[p.start.x+2][p.start.y]=COULEUR_VIDE;
                        board[p.start.x+1][p.start.y-1]=player;
                    }
                }
                else { 
                    board[p.start.x-1][p.start.y]=COULEUR_VIDE;
                    if (length_mvt(p)==L_3) {
                        board[p.start.x-2][p.start.y]=COULEUR_VIDE;
                        board[p.start.x-1][p.start.y-1]=player;
                    }
                }
            }
            if (direction_mvt(board, p)==DIR_RIGHT){              //direction vers la droite
                board[p.start.x][p.start.y]=COULEUR_VIDE;
                board[p.end.x][p.end.y]=player;
                board[p.start.x][p.start.y+1]=player;
                if (p.start.x<p.end.x){  
                    board[p.start.x+1][p.start.y]=COULEUR_VIDE;
                    if (length_mvt(p)==L_3) {
                        board[p.start.x+2][p.start.y]=COULEUR_VIDE;
                        board[p.start.x+1][p.start.y+1]=player;
                    }
                }
                else { 
                    board[p.start.x-1][p.start.y]=COULEUR_VIDE;
                    if (length_mvt(p)==L_3) {
                        board[p.start.x-2][p.start.y]=COULEUR_VIDE;
                        board[p.start.x-1][p.start.y+1]=player;
                    }
                }
            }
        }
    } 
    return board;
 }