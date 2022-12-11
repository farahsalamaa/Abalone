#include "abalone_terminal.h"

/**
 * \file abalone_terminal.c
 * \brief Creation du jeu et lancement du jeu
*/

/**
 * \fn init_board(Pablone game)
 * \brief Fonction qui genère un board
 * \param game Structure qui contient: board, state, player, timer du jeu
*/
void init_board(PAbalone game){
	char init_board[8][8] = 
		{{ 'B' , 'B' , 'B' , 'B' , 'B' , 'B' , 'B' , 'B'  },
		 { 'Z' , 'B' , 'B' , 'B' , 'B' , 'B' , 'B' , 'Z'  },
		 { 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z'  },
		 { 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z'  },
		 { 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z'  },
		 { 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z' , 'Z'  },
		 { 'Z' , 'N' , 'N' , 'N' , 'N' , 'N' , 'N' , 'Z'  },
		 { 'N' , 'N' , 'N' , 'N' , 'N' , 'N' , 'N' , 'N'  },
		 };
	/*int init_board[8][8] = 
		{{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1  },
		 { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 0  },
		 { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		 { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		 { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		 { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
		 { 0 , 2 , 2 , 2 , 2 , 2 , 2 , 0  },
		 { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2  },
		 };*/

	game->board = malloc(8*sizeof(char*));
	for (int y=0; y<8;y++){
		game->board[y] = malloc(8*sizeof(char));
		for (int x =0;x<8;x++){
			game->board[y][x] = init_board[y][x];
		}
	}
	
}

/**
 * \fn new_abalone()
 * \brief Une fonction qui genère un nouveau jeu abalone
 * \return Structure contenant: le state, timer, player et board du jeu
*/
PAbalone new_abalone(){
    PAbalone r = malloc(sizeof(Abalone));
    r->state = STATE_INITIALIZED;
	r->timer = 0;
    r->player = 'N'; // 'B' = blanc 'N' = Noir
    r->board = (char**)malloc(8*sizeof(char*));
	for (int i=0; i<8;i++){
		r->board[i] = (char*)malloc(8*sizeof(char));
	}
	init_board(r);
    return r;
}

/**
 * \fn new_abalone_board(char** tab)
 * \brief Actualiser l'etat du jeu
 * \param tab La grille de board
 * \return Le jeu avec un board actualisé
*/
PAbalone new_abalone_board(char** tab){
    PAbalone r = malloc(sizeof(Abalone));
    r->state = STATE_INITIALIZED;
	r->timer = 0;
    r->player = COULEUR_NOIR; // 'B' = blanc 'N' = Noir
    r->board = (char**)malloc(8*sizeof(char*));
	for (int i=0; i<8;i++){
		r->board[i] = (char*)malloc(8*sizeof(char));
        for (int j=0; j<8;j++){
            r->board[i][j] = tab[i][j];
        }
	}
    return r;
}

/**
 * \fn display_board(char** board)
 * \brief Affiche la grille
 * \param board La grille board
*/
void display_board(char** board){



	/*printf ("\033[5;37m  ⬤   \033[0m");
	printf ("\033[48;2;175;136;98;38;5;0m  ⬤   \033[0m");
	printf ("\033[48;2;255;0;0m  ⬤   \033[0m");
	printf ("\033[48;2;37;253;233m  ⬤   \033[0m");
	printf ("\033[48;2;255;0;0;38;5;0m ⬤   \033[0m");
	printf ("\033[48;2;37;253;233;38;5;0m  ⬤   \033[0m");*/

	int z=0;
	char alphabet[8]="ABCDEFGH";
	printf("\n");
	printf("          1    2     3     4     5     6     7     8   \n");
	printf("\n");
	for (int i=0; i<8;i++){
	printf("%c",alphabet[z]);
	printf("      ");
		for (int j=0; j<8;j++){
			switch (board[i][j]){
			
			case 'B':
                    		if((i+j)%2==0){
                   			printf ("\033[48;2;255;0;0m  ⬤   \033[0m");   	// pion blanc sur case blanche
                    		} else {
                    	 		printf ("\033[48;2;37;253;233m  ⬤   \033[0m");    	// pion blanc sur case noire
                    		}
                    		break;
                	case 'N':
                    		if((i+j)%2==0){
                    			printf ("\033[48;2;255;0;0;38;5;0m  ⬤   \033[0m");// pion noir sur case blanche
                    		} else {
                    	 			printf ("\033[48;2;37;253;233;38;5;0m  ⬤   \033[0m");	// pion noir sur case noire
                    		}
                    		break;
                    	case 'Z':
                     		if((i+j)%2==0){
                    	 		printf ("\033[48;2;255;0;0m      \033[0m"); 	// case blanche vide
                    		} else {
                    	 		printf ("\033[48;2;37;253;233m      \033[0m");   	// case noire vide
                    		}
                    		break;
			}
			
			
		}
		z+=1;
		printf("\n");
	}
}

/**
 * \fn print_error(int error)
 * \brief Affichage de l'erreur lisible à l'humain
 * \param error L'erreur dans le jeu
*/
void print_error(int error){
	switch (error){
		case ERROR_UNKNOWN: 
			printf("erreur non gérée / non comprise\n");
        	break;
      	case ERROR_OUT_OF_BOUNDS :
        	printf("\n mouvement jusqu'a en dehors du plateau\n");
        	break;
      	case ERROR_MISSING_PIECE :
        	printf("tentative de déplacement depuis un case vide\n");
        	break;
      	case ERROR_WRONG_COLOR :
        	printf("\n tentative de déplacement d'une pièce de la mauvaise couleur\n");
        	break;
      	case ERROR_BLOCKED :
        	printf("\n tentaive de déplacement d'une seule pièce vers un espace obstrué\n");
        	break;
      	case ERROR_LINE_INCOMPLETE :
        	printf("\n tentative de déplacement d'une ligne qui contient un trou ou une piece d'une autre couleur\n");
        	break;
      	case ERROR_NOT_ENOUGH_STRENGTH :
        	printf("\ntentative de déplacement en ligne contre une ligne plus forte\n");
        	break;
      	case ERROR_ALLY_IN_THE_WAY :
        	printf("\ntentative de déplacement en ligne vers un allié\n");
        	break;
      	case ERROR_TUPLE_INCOMPLETE :
        	printf("\ntentative de déplacement de 2 ou 3 pieces pas de la même couleur ou contenant du vide\n");
        	break; 
      	case ERROR_OBSTRUCTED :
        	printf("\ntentative de déplacement d'un doublet/triplet vers un espace obstrué\n");
        	break;
    }
	return;
}

/**
 * \fn etat(PAbalone r)
 * \brief Determiner l'état du jeu
 * \param r Le jeu
 * \return L'état du jeu actualisé
*/
char etat(PAbalone r){
    int w=0;
    int b=0;
    for (int i=0; i<8;i++){
        for (int j=0; j<8;j++){
            if (r->board[i][j]==COULEUR_BLANC){w++;} ; 
            if (r->board[i][j]==COULEUR_NOIR){b++;} ; 
        }
    }
	if (w<14){
        return STATE_WON_NOIR;
    }
    if (b<14){
       return STATE_WON_BLANC;
    }
	/*un fonction timer qui vas changer le timer de PAbalone 
si le timer n as pas encore commencer ==> r.timer prend 0
si le timer est entre 1 et 900 ==> r.timer prend 1
si le timer a depasser 900 ==> r.timer prend 2*/
	if (r->timer>=TIME_LIMIT){
	   return STATE_TIMEOUT;
    }else if (r->timer == 0){
		return STATE_INITIALIZED;
	}else{
		return STATE_RUNNING;
	}
}
	
/**
 * \fn play_game()
 * \brief Lancement du jeu
*/
void play_game(){
	PAbalone game = new_abalone();
	display_board(game->board);
    Coord c[2];
	Mouvement mvt;
	char* a1=malloc(6*sizeof(char));
	int error;
	time_t start;

	while (game->state == STATE_RUNNING || game->state == STATE_INITIALIZED){
		start = time(NULL);
		do {
			do{
				printf("lettres entre A-H , et les nembre entre 1-8\n");
	    		printf("inserer votre mouvement, ex : \"B1:C3\"\n");
				scanf("%5s",a1);
			}while(strlen(a1) != 5);
			error = string_to_coord(a1,c);
			if(!error) error = coord_to_mouvement(game,(&mvt),c); 
			else if(error == ERROR_OUT_OF_BOUNDS) printf("erreur de conversion de la chaine en coordonnées : coordonnée en dehors de la grille \n");
			else printf("erreur de conversion de la chaine en coordonnées : erreur inconnue\n");
			if(!error) error = finalise_mvt(game,mvt); else printf("erreur de conversion des coordonées en mouvement\n");
			if(error)print_error(error);
		}while(error);
		if(game->state == STATE_INITIALIZED){
			game->timer += 1;
		}else{
			int time_elapsed = difftime(time(NULL),start);
			game->timer += time_elapsed;
		}
		game->state = etat(game);
		//debug("Game state : %c\n",game->state);
		if (game->player == COULEUR_NOIR){
			game->player = COULEUR_BLANC;
			printf("tour des Blancs :\n");
		}else{
			game->player = COULEUR_NOIR;
			printf("tour des Noirs :\n");
		}
		
		
		display_board(game->board);
	}
	
	switch(game->state){
		case STATE_INITIALIZED:
		    printf("la partie est initialisé\n");
			break;
		case STATE_WON_BLANC:
		    printf("les blancs ont gagné !!!\n");
			break;
		case STATE_WON_NOIR:
		    printf("les noirs ont gagné !!!\n");
			break;
		case STATE_TIMEOUT:
		    printf("la partie s'est fini en égalité\n");
			break;
	}
	
}

/**
 * \fn choose_color()
 * \brief Choix du couleur par l'utilisateur
 * \return La couleur choisie par l'utilisateur, noir ou blanc
*/
char choose_color() {
    char* gameplayer = malloc(2*sizeof(char));
    do{
        printf("sélectionnez votre couleur :\n- %c pour blanc\n- %c pour noir\n", COULEUR_BLANC, COULEUR_NOIR);
        scanf("%1s",gameplayer);
        *gameplayer = gameplayer[0];
    }while(*gameplayer != COULEUR_BLANC && *gameplayer != COULEUR_NOIR);
    return *gameplayer;
}

/**
 * \fn play_game_random_ia()
 * \brief Lancement du jeu contre l'Intelligence Articficielle
*/
void play_game_random_ia() {
    PAbalone game = new_abalone();
    display_board(game->board);
    Coord c[2];
    Mouvement mvt;
    char* a1=malloc(6*sizeof(char));
    int error;
    time_t start;

    char gameplayer = choose_color();

    while (game->state == STATE_RUNNING || game->state == STATE_INITIALIZED){
        start = time(NULL);
        do {
            if (game->player == gameplayer) {
                do{
                    printf("lettres entre A-H , et les nembre entre 1-8\n");
                    printf("inserer votre mouvement, ex : \"B1:C3\"\n");
                    scanf("%5s",a1);
                }while(strlen(a1) != 5);
            } else play_random_move(game);
            string_to_coord(a1,c);
            coord_to_mouvement(game,(&mvt),c);
            error = finalise_mvt(game,mvt);
            if(error)print_error(error);
        }while(error);
        if(game->state == STATE_INITIALIZED){
            game->timer += 1;
        }else{
            int time_elapsed = difftime(time(NULL),start);
            game->timer += time_elapsed;
        }
        game->state = etat(game);
        //debug("Game state : %c\n",game->state);
        if (game->player == COULEUR_NOIR){
            game->player = COULEUR_BLANC;
            printf("tour des Blancs :\n");
        }else{
            game->player = COULEUR_NOIR;
            printf("tour des Noirs :\n");
        }


        display_board(game->board);
    }

    switch(game->state){
        case STATE_INITIALIZED:
            printf("la partie est initialisé\n");
            break;
        case STATE_WON_BLANC:
            printf("les blancs ont gagné !!!\n");
            break;
        case STATE_WON_NOIR:
            printf("les noirs ont gagné !!!\n");
            break;
        case STATE_TIMEOUT:
            printf("la partie s'est fini en égalité\n");
            break;
    }
}