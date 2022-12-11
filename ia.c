#include "ia.h"

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
 * \fn PMouvement coord_to_mvt(PAbalone abalone, PMouvement mvt)
 * \brief Completer les composantes manquantes du mouvement
 * \param abalone Le jeu
 * \param mvt Le mouvement (non complet)
 * \return Un mouvement complet
*/
PMouvement coord_to_mvt(PAbalone abalone, PMouvement mvt) {
    mvt->dir = direction_mvt(abalone, *mvt);
    mvt->type = type_mvt(*mvt);
    mvt->longueur = length_mvt(*mvt);
    return mvt;
}

//Permet de donner la taille d'une liste de mouvements
/**
 * \fn int last_element_tab_mvt(PMouvement list_mvt)
 * \brief Donner le dernier mouvement effectué
 * \param list_mvt Une liste contenant les mouvements
 * \return Le dernier mouvement
*/
int last_element_tab_mvt(PMouvement list_mvt) {
    return list_mvt[0].start.x;
}

//Permet de choisir un coup aléatoire dans la liste de mouvement et le jouer
void random_move(PAbalone abalone, PMouvement list_mvt) {
    int random = random_number(0, last_element_tab_mvt(list_mvt));
    exec_mvt(abalone, *(list_mvt+random));
}



//à partir de l'abalone et de la couleur du joueur, renvoit une liste de tous les mouvements possibles
PMouvement ensemble_mouvement_possible(PAbalone abalone,char color){
    PMouvement liste_coup=malloc(100*sizeof(Mouvement));
    //Compteur pour la liste
    liste_coup[0].start.x=1;
    //Coordonnées boule
    Coord boule;
    //Analyse de haut en bas(x) puis décale vers la doite(y)
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(abalone->board[i][j]==color){
                //Prend coordonnées de la boule
                boule.x=i;boule.y=j;
                //boucle pour analyser mouvement de longueur 1, puis 2, puis 3    
                //debug("%i,%i",i,j);
                generation_mouvement(abalone,boule,liste_coup);
                //trace();
            }
        }
    }
    return liste_coup;
    //Ne pas oublier que liste_coup[0]->start.x donne le la position du dernier mouvement possible
}

//permet de remplir la liste des coups possibles qui sera retournée dans ensemble_mouvement_possible
void generation_mouvement(PAbalone abalone,Coord start,Mouvement *liste){
    //initialisation d'une liste regroupant toutes les coordonnées de end possibles
    PCoord liste_coord_end;
    //initialisation d'un mouvement possible
    Mouvement move_possible;
    //les valeurs possibles de la chaine de caractère longueur du mouvement selon l'entier k
    //remplissage de la liste des coordonnées de end possible
    liste_coord_end=all_end(start);
    //effectue les 4 déplacements possibles
    for (int i=0;i<20;i++){
        if (i<16){
            move_possible.start=start;
            move_possible.end=liste_coord_end[i];
        }
        switch(i){
            case (16):
            move_possible.start.x=start.x;move_possible.start.y=start.y+1;
            move_possible.end=liste_coord_end[16];
            break;

            case (17):
            move_possible.start.x=start.x;move_possible.start.y=start.y+2;
            move_possible.end=liste_coord_end[16];
            break;

            case (18):
            move_possible.start.x=start.x+1;move_possible.start.y=start.y;
            move_possible.end=liste_coord_end[17];
            break;

            case (19):
            move_possible.start.x=start.x+2;move_possible.start.y=start.y;
            move_possible.end=liste_coord_end[17];
            break;

        }
        move_possible.longueur=length_mvt(move_possible);
        move_possible.type=type_mvt(move_possible);
        //debug("move starts at : (%d,%d) and ends at : (%d,%d)",move_possible.start.x,move_possible.start.y,move_possible.end.x,move_possible.end.y);
        move_possible.dir= direction_mvt(abalone,move_possible);
        //trace();
        //vérifier si le mouvement est possible
        if(validate_mvt(abalone, move_possible)==VALIDATION_OK){
            int compteur=liste[0].start.x;
            liste[compteur]=move_possible;
            liste[0].start.x=liste[0].start.x+1;
        }
    } 
}

//renvoie la liste des 20 coordonnees de end possibles pour n'importe quel start selon la couleur du joueur
PCoord all_end(Coord start){
    PCoord liste_coord=malloc(18*sizeof(Coord));
    //Cas longueur 1
    liste_coord[0].x=start.x+1;liste_coord[0].y=start.y;
    liste_coord[1].x=start.x-1;liste_coord[1].y=start.y;
    liste_coord[2].x=start.x;liste_coord[2].y=start.y+1;
    liste_coord[3].x=start.x;liste_coord[3].y=start.y-1;
    //Cas longueur 2 horizontal
    liste_coord[4].x=start.x-1;liste_coord[4].y=start.y+1;
    liste_coord[5].x=start.x+1;liste_coord[5].y=start.y+1;
    liste_coord[6].x=start.x;liste_coord[6].y=start.y+2;
    //Cas longueur 2 vertical
    liste_coord[7].x=start.x+1;liste_coord[7].y=start.y-1;
    liste_coord[8].x=start.x+1;liste_coord[8].y=start.y+1;
    liste_coord[9].x=start.x+2;liste_coord[9].y=start.y;
    //Cas longueur 3 horizontal
    liste_coord[10].x=start.x-1;liste_coord[10].y=start.y+2;
    liste_coord[11].x=start.x+1;liste_coord[11].y=start.y+2;
    liste_coord[12].x=start.x;liste_coord[12].y=start.y+3;
    //Cas longuer 3 vertical
    liste_coord[13].x=start.x+2;liste_coord[13].y=start.y-1;
    liste_coord[14].x=start.x+2;liste_coord[14].y=start.y+1;
    liste_coord[15].x=start.x+3;liste_coord[15].y=start.y;
    //cas particulier
    liste_coord[16].x=start.x;liste_coord[16].y=start.y-1;
    liste_coord[17].x=start.x-1;liste_coord[17].y=start.y;
    
    return liste_coord;
}

//Fonction pour jouer directement un coup aléatoire
void play_random_move(PAbalone abalone) {
    random_move(abalone, ensemble_mouvement_possible(abalone, abalone->player));
}

//Fonctions pour déterminer la fonction d'évaluation

//Permet de compter le nombre de pions dans le cadre intérieur (donné par min/max)
int count_center(PAbalone abalone,char color) {
    int min = 2; int max = 5;
    int somme = 0;
    for (int i = min; i<=max; i++) {
        for (int j = min; j<=max; j++) {
            if (abalone->board[i][j] == color) somme++;
        }
    }
    return somme;
}

//Permet de compter le nombre de pions présents au niveau des bordures 
int count_padding(PAbalone abalone,char color) {
    return 14 - count_center(abalone,color);
}

PCoord PT_min(PAbalone abalone,char color){
    int x_min=7;
    int y_min=7;
    PCoord pt_min = malloc(sizeof(PCoord));
    for (int i = 0; i<=7; i++) {
        for (int j = 0; j<=7; j++) {
            if (abalone->board[i][j] == color) {
                if (i<x_min){x_min=i;}
                if(j<y_min){y_min=j;}
            }
        }
    }
    pt_min->x=x_min;
    pt_min->y=y_min;
    return(pt_min);
}
PCoord PT_max(PAbalone abalone,char color){
    int x_max=0;
    int y_max=0;
    PCoord pt_max = malloc(sizeof(PCoord));
    for (int i = 0; i<=7; i++) {
        for (int j = 0; j<=7; j++) {
            if (abalone->board[i][j] == color) {
                if (i>x_max){x_max=i;}
                if(j>y_max){y_max=j;}
            }
        }
    }
    pt_max->x=x_max;
    pt_max->y=y_max;
    return(pt_max);
}

int score_density(PAbalone abalone,char color){
    int somme = 0;
    PCoord pt_min = PT_min(abalone,color);
    PCoord pt_max = PT_max(abalone,color);
    int W =(pt_max->x - pt_min->x);// la Largeur de la surface (Width)
    int H =(pt_max->y - pt_min->y);// la longeur de la surface (height)
    int S = W*H ;
    for (int i= pt_min->x ;i<= pt_max->x ; i++){
           for (int j=pt_min->y ; j<= pt_max->y ; j++) {
              if (abalone->board[i][j] == color) somme++;
        }
    }
    return(somme/S);
  }
  int possible_attacks(PAbalone abalone,char color){
    int a;
    char opp = COULEUR_BLANC;
    if (color == COULEUR_BLANC){opp=COULEUR_NOIR;};
    PMouvement l=ensemble_mouvement_possible(abalone,color);
    int i= last_element_tab_mvt(l)+1;
    for (int j=0;j<i; j++ ){
        int x=l[j].end.x;
        int y=l[j].end.y;
        if (abalone->board[x][y]==opp){a++;}
    }
    return a;
  }
  // retourner la couleur du joueur opposé
  char Other_player(PAbalone abalone){
    char opp = COULEUR_BLANC;
    if (abalone->player == COULEUR_BLANC){opp=COULEUR_NOIR;}
    return opp;
  }
//Calcul du score de l'utilité 
    int score_utility(PAbalone abalone){
    int alpha,beta,gamma,teta;
    int p1 = alpha*count_center(abalone,abalone->player)
            +beta*count_padding(abalone,abalone->player)
            + gamma*score_density(abalone,abalone->player);
            +teta*possible_attacks(abalone,abalone->player);

    int p2 = alpha*count_center( abalone,Other_player(abalone))
          + beta*count_padding( abalone,Other_player(abalone))
          + gamma*score_density(abalone,Other_player(abalone));
          +teta*possible_attacks(abalone,Other_player(abalone));

    return(p1-p2);
  }