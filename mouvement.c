#include "mouvement.h"

/**
 * \file mouvement.c
 * \brief les fonctions pour definir, valider et executer un mouvement
*/

/*! \fn area_mvt(Mouvement mvt)
    \brief Calcule la surface réalisée par le mouvement
    \param mvt le mouvement donné
    \return la surface réalisée par le mouvement
*/
int area_mvt(Mouvement mvt) {
    return (abs(mvt.start.x - mvt.end.x) + 1) * (abs(mvt.start.y - mvt.end.y) + 1);
}

/**
 * \fn type_mvt(Mouvement mvt)
 * \brief determiner le type du mouvement, ligne ou largeur
 * \param mvt le mouvement donné
 * \return le mouvemnt en ligne ou en largeur
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
 * \fn orientation_grp(Coord start, Coord end)
 * \brief determiner si le mouvement d'un groupe de pions est horizontal ou vertical ou non
 * \param start coordonnées du debut du mouvement
 * \param end coordonnées de la fin du mouvement
 * \return l'orientation horizontal ou vertical ou non
*/
char orientation_grp(Coord start, Coord end){
    if (start.x == end.x) return HORIZONTAL;
    else if (start.y == end.y) return VERTICAL;
    else return ERROR_NOT_ALIGNED;
}

/**
 * \fn length_mvt(Mouvement mvt)
 * \brief calculer la longueur d'un groupe de pion en mouvement
 * \param mvt le mouvement donné
 * \return la longueur d'un groupe de pion en mouvement
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
 * \fn voisin_carre(PAbalone abalone, Mouvement mvt)
 * \brief determiner le pion voisin dans un carre (cas specifique)
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return les coordonnées du voisin d'un pion en mouvement carré
*/
Coord voisin_carre(PAbalone abalone, Mouvement mvt){
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
    if (abalone->board[x0][y0] == abalone->board[x0][y1]){
        v.x = x0;
        v.y = y1;
        return v;
    }
    else if (abalone->board[x0][y0] == abalone->board[x1][y0]){
        v.x = x1;
        v.y = y0;
        return v;
    }
    return v;
}

/**
 * \fn direction_mvt(PAbalone abalone, Mouvement mvt)
 * \brief determiner la direction du mouvement
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return la direction mouvement
*/
char direction_mvt(PAbalone abalone, Mouvement mvt){
    char len = length_mvt(mvt);
    char type = type_mvt(mvt);
    switch (len){
        case L_1:
            if (mvt.start.x == mvt.end.x){
                if (mvt.start.y > mvt.end.y){return DIR_LEFT;}
                else if (mvt.start.y < mvt.end.y){return DIR_RIGHT;}
            }
            else if (mvt.start.y == mvt.end.y){
                if (mvt.start.x > mvt.end.x){return DIR_DOWN;}
                else if (mvt.start.x < mvt.end.x){return DIR_UP;}
            }
            break;
        case L_2:
            if (type == MVT_LARGEUR){
                Coord voisin = voisin_carre(abalone, mvt);
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
 * \fn validate_mvt_piece(PAbalone abalone, Mouvement mvt)
 * \brief verifier si le mouvement donné contient le pion appartenant au joueur
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return ERROR_MISSING_PIECE s'il n'ya pas de pion, ERROR_WRONG_COLOR si pion n'appartient pas au joueur et VALIDATION_OK sinon
*/
int validate_mvt_piece(PAbalone abalone, Mouvement mvt){
    if (abalone->board[mvt.start.x][mvt.start.y] != abalone->player){
        if (abalone->board[mvt.start.x][mvt.start.y] == 'Z')
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
 * \brief verifier si le mouvement donné reste bien dans la grille
 * \param mvt le mouvement donné
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
 * \fn validate_mvt_ligne_1(PAbalone abalone, Mouvement mvt)
 * \brief verifier si le mouvement d'un pion n'est pas bloqué par un autre pion
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return ERROR_BLOCKED s'il est bloqué et VALIDATION_OK sinon
*/
int validate_mvt_ligne_1(PAbalone abalone, Mouvement mvt){
    if (abalone->board[mvt.end.x][mvt.end.y] != 'Z'){
        return ERROR_BLOCKED;
    }
    return VALIDATION_OK;   
}

/**
 * \fn validate_mvt_ligne_2(PAbalone abalone, Mouvement mvt)
 * \brief verifier si le mouvement en ligne de deux pion n'est pas bloqué par un autre pion
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un message d'erreur correspondant 
*/
int validate_mvt_ligne_2(PAbalone abalone, Mouvement mvt){
    int modX = 0;
    int modY = 0;
    
    switch (mvt.dir){
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

    if (abalone->board[mvt.start.x+modX][mvt.start.y+modY] != abalone->player){
        return ERROR_LINE_INCOMPLETE;
    }

    if (abalone->board[mvt.end.x][mvt.end.y] == abalone->player){
        return ERROR_ALLY_IN_THE_WAY;
    }else if(abalone->board[mvt.end.x][mvt.end.y] == COULEUR_VIDE){
        return VALIDATION_OK;
    }else{
        if (mvt.dir == DIR_UP || mvt.dir == DIR_DOWN){
            if (mvt.end.x+modX < 0 || mvt.end.x+modX > 7){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x+modX][mvt.end.y] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x+modX][mvt.end.y] == abalone->player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            return ERROR_NOT_ENOUGH_STRENGTH;
        }else{
            if (mvt.end.y+modY < 0 || mvt.end.y+modY > 7){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x][mvt.end.y+modY] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x][mvt.end.y+modY] == abalone->player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            return ERROR_NOT_ENOUGH_STRENGTH;
        }
    }
    return ERROR_UNKNOWN;
}

/**
 * \fn validate_mvt_ligne_3(PAbalone abalone, Mouvement mvt)
 * \brief verifier si le mouvement en ligne de trois pion n'est pas bloqué par un autre pion
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un message d'erreur correspondant
*/
int validate_mvt_ligne_3(PAbalone abalone, Mouvement mvt){
    int modX = 0;
    int modY = 0;
    
    switch (mvt.dir){
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

    if (abalone->board[mvt.start.x+modX][mvt.start.y+modY] != abalone->player){
        return ERROR_LINE_INCOMPLETE;
    }
    if (abalone->board[mvt.start.x+2*modX][mvt.start.y+2*modY] != abalone->player){
        return ERROR_LINE_INCOMPLETE;
    }

    if (abalone->board[mvt.end.x][mvt.end.y] == abalone->player){
        return ERROR_ALLY_IN_THE_WAY;
    }else if(abalone->board[mvt.end.x][mvt.end.y] == COULEUR_VIDE){
        return VALIDATION_OK;
    }else{
        if (mvt.dir == DIR_UP || mvt.dir == DIR_DOWN){
            if (mvt.end.x+modX < 0 || mvt.end.x+modX > 7){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x+modX][mvt.end.y] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x+modX][mvt.end.y] == abalone->player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            if (mvt.end.x+2*modX < 0 || mvt.end.x+2*modX > 7){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x+2*modX][mvt.end.y] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x+2*modX][mvt.end.y] == abalone->player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            return ERROR_NOT_ENOUGH_STRENGTH;
        }else{
            if (mvt.end.y+modY < 0 || mvt.end.y+modY > 7){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x][mvt.end.y+modY] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x][mvt.end.y+modY] == abalone->player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            if (mvt.end.y+2*modY < 0 || mvt.end.y+2*modY > 7){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x][mvt.end.y+2*modY] == COULEUR_VIDE){
                return VALIDATION_OK;
            }else if(abalone->board[mvt.end.x][mvt.end.y+2*modY] == abalone->player){
                return ERROR_ALLY_IN_THE_WAY;
            }

            return ERROR_NOT_ENOUGH_STRENGTH;
        }
    }
    return ERROR_UNKNOWN;
}

/**
 * \fn validate_mvt_largeur_1(PAbalone abalone, Mouvement mvt)
 * \brief verifier si le mouvement d'un pion n'est pas bloqué par un autre pion
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return VALIDATION_OK s'il n'est pas bloqué, ERROR_BLOCKED sinon 
*/
int validate_mvt_largeur_1(PAbalone abalone, Mouvement mvt){
    if (abalone->board[mvt.end.x][mvt.end.y] != 'Z'){
        return ERROR_BLOCKED;
    }
    return VALIDATION_OK;
}

/**
 * \fn validate_mvt_largeur_2(PAbalone abalone, Mouvement mvt)
 * \brief verifier si le mouvement en largeur de deux pion n'est pas bloqué par un autre pion
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un message d'erreur correspondant 
*/
int validate_mvt_largeur_2(PAbalone abalone, Mouvement mvt){
    int modX = 0;
    int modY = 0;
    
    switch (mvt.dir){
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

    if(mvt.dir == DIR_UP || mvt.dir == DIR_DOWN){
        int progression =  mvt.end.y - mvt.start.y;
        
        if (abalone->board[mvt.start.x+modX][mvt.start.y] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (abalone->board[mvt.start.x][mvt.start.y+progression] != abalone->player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (abalone->board[mvt.start.x+modX][mvt.start.y+progression] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        return VALIDATION_OK;
    }else{
        int progression =  mvt.end.x - mvt.start.x;
        
        if (abalone->board[mvt.start.x][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }
        
        if (abalone->board[mvt.start.x+progression][mvt.start.y] != abalone->player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (abalone->board[mvt.start.x+progression][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        return VALIDATION_OK;
    }

    return ERROR_UNKNOWN;
}

/**
 * \fn validate_mvt_largeur_3(PAbalone abalone, Mouvement mvt)
 * \brief verifier si le mouvement en largeur de trois pion n'est pas bloqué par un autre pion
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un message d'erreur correspondant 
*/
int validate_mvt_largeur_3(PAbalone abalone, Mouvement mvt){
    int modX = 0;
    int modY = 0;
    
    switch (mvt.dir){
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

    if(mvt.dir == DIR_UP || mvt.dir == DIR_DOWN){
        int progression =  (mvt.end.y - mvt.start.y)/2;
        if (abalone->board[mvt.start.x+modX][mvt.start.y] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (abalone->board[mvt.start.x][mvt.start.y+progression] != abalone->player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (abalone->board[mvt.start.x+modX][mvt.start.y+progression] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (abalone->board[mvt.start.x][mvt.start.y+2*progression] != abalone->player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (abalone->board[mvt.start.x+modX][mvt.start.y+2*progression] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        return VALIDATION_OK;
    }else{
        int progression =  (mvt.end.x - mvt.start.x)/2;
        if (abalone->board[mvt.start.x][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (abalone->board[mvt.start.x+progression][mvt.start.y] != abalone->player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (abalone->board[mvt.start.x+progression][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        if (abalone->board[mvt.start.x+2*progression][mvt.start.y] != abalone->player){
            return ERROR_TUPLE_INCOMPLETE;
        }
        if (abalone->board[mvt.start.x+2*progression][mvt.start.y+modY] != COULEUR_VIDE){
            return ERROR_OBSTRUCTED;
        }

        return VALIDATION_OK;
    }

    return ERROR_UNKNOWN;
}

/**
 * \fn validate_mvt(PAbalone abalone, Mouvement mvt)
 * \brief verifier si le mouvement est valide
 * \param mvt le mouvement donné
 * \param abalone le jeu contenant le board
 * \return VALIDATION_OK si valide, sinon un message d'erreur correspondant 
*/
int validate_mvt(PAbalone abalone, Mouvement mvt){
    /*Erreurs générales*/
    int error = validate_mvt_bounds(mvt);
    if(error != VALIDATION_OK){return error;}
    error = validate_mvt_piece(abalone, mvt);
    if(error != VALIDATION_OK){return error;}
    
    if (mvt.longueur == L_0){
        return ERROR_NO_LENGTH;
    }

    switch (mvt.type)
    {
    case MVT_LIGNE:
        switch (mvt.longueur)
        {
        case L_1:
            return validate_mvt_ligne_1(abalone, mvt);
            break;

        case L_2:
            return validate_mvt_ligne_2(abalone, mvt);
            break;

        case L_3:
            return validate_mvt_ligne_3(abalone, mvt);
            break;
        
        default:
            return ERROR_UNKNOWN;
            break;
        }
        break;

    case MVT_LARGEUR:
        switch (mvt.longueur)
        {
        case L_1:
            return validate_mvt_largeur_1(abalone, mvt);
            break;

        case L_2:
            return validate_mvt_largeur_2(abalone, mvt);
            break;

        case L_3:
            return validate_mvt_largeur_3(abalone, mvt);
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
 * \fn string_to_coord(char* mvt, PCoord coord)
 * \brief changement de la chaine donnée par utilisateur en coordonnées 2D
 * \param mvt le mouvement donné
 * \param coord les coordonnées du mouvement qu'on veut
 * \return 0 si les coordonnées existe dans la grille, 1 sinon
*/
int string_to_coord(char* mvt, PCoord coord){
    coord[0].x = mvt[0]-65;
    coord[0].y = mvt[1]-49;
    coord[1].x = mvt[3]-65;
    coord[1].y = mvt[4]-49;
    if(coord[0].x > 7 || coord[0].y > 7 || coord[1].x > 7 || coord[1].y > 7 || mvt[2]!=':' 
    || coord[0].x < 0 || coord[0].y < 0 || coord[1].x < 0 || coord[1].y < 0){
        return ERROR_OUT_OF_BOUNDS;   
    }else{
        return 0;
    }
}

/**
 * \fn coord_to_mouvement(PAbalone abalone, PMouvement mvt, PCoord coords)
 * \brief mettre les coordonnées dans un mouvement
 * \param mvt le mouvement donné
 * \param coord les coordonnées du mouvement qu'on veut
 * \param abalone le jeu contenant le board
 * \return 0
*/
int coord_to_mouvement(PAbalone abalone, PMouvement mvt, PCoord coords){
    mvt->start = coords[0];
    mvt->end = coords[1];

    mvt->dir = direction_mvt(abalone,(*mvt)); //TODO ajouter le plateau correct 
    mvt->type = type_mvt(*mvt);
    mvt->longueur = length_mvt(*mvt);

    return 0;
}

//fonction du dernier deplacement
/* TODO Comprendre ce truc

PCoord tposition=malloc(sizeof(tposition));
typedef struct tposition{
Coord pos[2];
}tposition;

tposition dernier_deplacement(){
    return p;
}
*/
//p variable globale contenant le dernier mvt valide 
//une variable globale qui stock le dernier mouvement effectuer.

/*une fonction qui prend un mouvement et si la fctVALIDATE return 0 il l applique 
et le stock en d sinon il affiche un erreur qui depend du retour de validate */
/**
 * \fn finalise_mvt(PAbalone G,Mouvement mvt)
 * \brief finaliser un mouvement et l'executer
 * \param mvt le mouvement donné
 * \param G le jeu contenant le board
 * \return VALIDATION_OK si mouvement validé, error sinon
*/
int finalise_mvt(PAbalone G,Mouvement mvt){
    Mouvement d;
    int error = validate_mvt(G,mvt);
    if(!error){
        exec_mvt(G,mvt);
        d = mvt;
        return VALIDATION_OK;
    }else{
        return error;
    }
}

/**
 * \fn push_mvt(PAbalone G,Mouvement mvt)
 * \brief fonction qui effectue la poussée des pions adverses
 * \param p le mouvement donné
 * \param plateau le jeu contenant le board
*/
 void push_mvt(PAbalone plateau,Mouvement p,int out){
    if (out==0){
        if (plateau->board[p.end.x][p.end.y]!=COULEUR_VIDE){
            Mouvement pushed;
            pushed.start.x = p.end.x;
            pushed.start.y = p.end.y;
            int pushedout = 1;
            if (p.dir==DIR_UP){
                if (pushed.start.x>0){
                pushed.end.x = p.end.x-1;
                pushed.end.y = p.end.y;
                pushedout=0;
                }
            }
            if (p.dir==DIR_DOWN){
                if (pushed.start.x<7){
                    pushed.end.x = p.end.x+1;
                    pushed.end.y = p.end.y;
                    pushedout=0;
                }
            }
            if (p.dir==DIR_LEFT){
                if (pushed.start.y>0){
                pushed.end.x = p.end.x;
                pushed.end.y = p.end.y-1;
                pushedout=0;
                }
            }
            if (p.dir==DIR_RIGHT){
                if (pushed.start.y<7){
                pushed.end.x = p.end.x;
                pushed.end.y = p.end.y+1;
                pushedout=0;
                }
            }
            if (plateau->player==COULEUR_NOIR){
                plateau->board[p.end.x][p.end.y]=COULEUR_BLANC;
                if (pushedout==0){
                    plateau->board[pushed.end.x][pushed.end.y]=COULEUR_BLANC;
                }
            }
            if (plateau->player==COULEUR_BLANC){
                plateau->board[p.end.x][p.end.y]=COULEUR_NOIR;
                if (pushedout==0){
                plateau->board[pushed.end.x][pushed.end.y]=COULEUR_NOIR;
                }
            }
        }
        else {
            if (plateau->player==COULEUR_NOIR){
            plateau->board[p.end.x][p.end.y]=COULEUR_BLANC;
            }
            if (plateau->player==COULEUR_BLANC){
            plateau->board[p.end.x][p.end.y]=COULEUR_NOIR;
            }
        }
    }
    else {
    }
}

//fonction qui prend le plateau en entrée, le modifie avec le nouveau mvt et retourne le plateau actualisé
//Appelle la fct push_mvt si un pion sort du plateau (à terminer)
/**
 * \fn exec_mvt(PAbalone G,Mouvement mvt)
 * \brief fonction qui effectue le mouvement
 * \param p le mouvement donné
 * \param plateau le jeu contenant le board
 * \return le board actualisé avec le mouvement effectué
*/
PAbalone exec_mvt(PAbalone plateau,Mouvement p){
    if (p.longueur==L_1){
        plateau->board[p.start.x][p.start.y]=COULEUR_VIDE;
        plateau->board[p.end.x][p.end.y]=plateau->player;
    }
    else {
        if (p.type==MVT_LIGNE){     //mvt en ligne
            plateau->board[p.start.x][p.start.y]=COULEUR_VIDE;
            if (plateau->board[p.end.x][p.end.y]!=COULEUR_VIDE){
                Mouvement mvtpush;
                mvtpush.start.x = p.end.x;
                mvtpush.start.y = p.end.y;
                mvtpush.dir = p.dir;
                int out=1;
                if (p.dir==DIR_UP){
                    if (mvtpush.start.x!=0){
                        mvtpush.end.x = p.end.x-1;
                        mvtpush.end.y = p.end.y;
                        out = 0;
                    }
                }
                if (p.dir==DIR_DOWN){
                    if (mvtpush.start.x!=7){
                        mvtpush.end.x = p.end.x+1;
                        mvtpush.end.y = p.end.y;
                        out = 0;
                    }
                }
                if (p.dir==DIR_LEFT){
                    if (mvtpush.start.y!=0){
                        mvtpush.end.x = p.end.x;
                        mvtpush.end.y = p.end.y-1;
                        out = 0;
                    }
                }
                if (p.dir==DIR_RIGHT){
                    if (mvtpush.start.y!=7){
                        mvtpush.end.x = p.end.x;
                        mvtpush.end.y = p.end.y+1;
                        out = 0;
                    }
                }
                push_mvt(plateau,mvtpush,out);
                plateau->board[p.end.x][p.end.y]=plateau->player;
            }
            else {plateau->board[p.end.x][p.end.y]=plateau->player;
            }
        }
        else if (p.type==MVT_LARGEUR){   //mvt latéral
            if (p.dir==DIR_UP){   //direction vers le haut
                plateau->board[p.start.x][p.start.y]=COULEUR_VIDE;
                plateau->board[p.end.x][p.end.y]=plateau->player;
                plateau->board[p.start.x-1][p.start.y]=plateau->player;
                if (p.start.y<p.end.y){   //comparaison de la valeur en Y
                    plateau->board[p.start.x][p.start.y+1]=COULEUR_VIDE;
                    if (p.longueur==L_3) {
                        plateau->board[p.start.x][p.start.y+2]=COULEUR_VIDE;
                        plateau->board[p.start.x-1][p.start.y+1]=plateau->player;
                    }
                }
                else { 
                    plateau->board[p.start.x][p.start.y-1]=COULEUR_VIDE;
                    if (p.longueur==L_3) {
                        plateau->board[p.start.x][p.start.y-2]=COULEUR_VIDE;
                        plateau->board[p.start.x-1][p.start.y-1]=plateau->player;
                    }
                }
            }
            if (p.dir==DIR_DOWN){          //direction vers le bas
                plateau->board[p.start.x][p.start.y]=COULEUR_VIDE;
                plateau->board[p.end.x][p.end.y]=plateau->player;
                plateau->board[p.start.x+1][p.start.y]=plateau->player;
                if (p.start.y<p.end.y){   //comparaison de la valeur en Y
                    plateau->board[p.start.x][p.start.y+1]=COULEUR_VIDE;
                    if (p.longueur==L_3) {
                        plateau->board[p.start.x][p.start.y+2]=COULEUR_VIDE;
                        plateau->board[p.start.x+1][p.start.y+1]=plateau->player;
                    }
                }
                else { 
                    plateau->board[p.start.x][p.start.y-1]=COULEUR_VIDE;
                    if (p.longueur==L_3) {
                        plateau->board[p.start.x][p.start.y-2]=COULEUR_VIDE;
                        plateau->board[p.start.x+1][p.start.y-1]=plateau->player;
                    }
                }
            }
            if (p.dir==DIR_LEFT){           //direction vers la gauche
                plateau->board[p.start.x][p.start.y]=COULEUR_VIDE;
                plateau->board[p.end.x][p.end.y]=plateau->player;
                plateau->board[p.start.x][p.start.y-1]=plateau->player;
                if (p.start.x<p.end.x){ 
                    plateau->board[p.start.x+1][p.start.y]=COULEUR_VIDE;
                    if (p.longueur==L_3) {
                        plateau->board[p.start.x+2][p.start.y]=COULEUR_VIDE;
                        plateau->board[p.start.x+1][p.start.y-1]=plateau->player;
                    }
                }
                else { 
                    plateau->board[p.start.x-1][p.start.y]=COULEUR_VIDE;
                    if (p.longueur==L_3) {
                        plateau->board[p.start.x-2][p.start.y]=COULEUR_VIDE;
                        plateau->board[p.start.x-1][p.start.y-1]=plateau->player;
                    }
                }
            }
            if (p.dir==DIR_RIGHT){              //direction vers la droite
                plateau->board[p.start.x][p.start.y]=COULEUR_VIDE;
                plateau->board[p.end.x][p.end.y]=plateau->player;
                plateau->board[p.start.x][p.start.y+1]=plateau->player;
                if (p.start.x<p.end.x){  
                    plateau->board[p.start.x+1][p.start.y]=COULEUR_VIDE;
                    if (p.longueur==L_3) {
                        plateau->board[p.start.x+2][p.start.y]=COULEUR_VIDE;
                        plateau->board[p.start.x+1][p.start.y+1]=plateau->player;
                    }
                }
                else { 
                    plateau->board[p.start.x-1][p.start.y]=COULEUR_VIDE;
                    if (p.longueur==L_3) {
                        plateau->board[p.start.x-2][p.start.y]=COULEUR_VIDE;
                        plateau->board[p.start.x-1][p.start.y+1]=plateau->player;
                    }
                }
            }
        }
    } 
    return plateau;
 }