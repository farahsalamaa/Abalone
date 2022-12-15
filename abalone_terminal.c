#include "abalone_terminal.h"
/**
 * \file abalone_terminal.c
 * \brief Creation du jeu et lancement du jeu
*/

/**
 * \fn init_board(PAbalone game)
 * \brief Fonction qui remplace le plateau de game par la plateau de départ
 * \param game Pointeur vers une structure Abalone qui représente la partie.
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
 * \return Pointeur vers une structure contenant l'état, le temps écoule, le joueur actif et la plateau du jeu
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
 * \brief Une fonction qui génère un nouveau jeu abalone à partir d'un plateau défini
 * \param tab Le plateau de départ
 * \return Pointeur vers une structure contenant l'état, le temps écoule, le joueur actif et la plateau du jeu
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
 * \fn char** create_board()
 * \brief créé un plateau vide.
 * \return le plateau vide
*/
char** create_board() {
    char** board = malloc(8* sizeof(char*));
    for (int i=0; i<8; i++) {
        board[i] = malloc(8 * sizeof(char));
        for (int j=0; j<8; j++) board[i][j] = '\0';
    }
    return board;
}

/**
 * \fn void destroy_board(char** board)
 * \brief détruit un plateau et libère l'espace
 * \param board l'adresse du plateau de caractères à libérer
*/
void destroy_board(char** board) {
    for (int i=0; i<8; i++) free(board[i]);
    free(board);
}

/**
 * \fn void destroy_abalone(PAbalone abalone)
 * \brief détruit une partie
 * \param abalone l'adresse de la partie à libérer
*/
void destroy_abalone(PAbalone abalone) {
    for (int i=0; i<8; i++) free(abalone->board[i]);
    free(abalone->board);
    free(abalone);
}

/**
 * \fn char** copy_board(char** board)
 * \brief créé une copie d'un plateau
 * \param board le plateau à dupliquer
 * \return le plateau dupliqué à une nouvelle adresse
*/
char** copy_board(char** board) {
    char** copy = malloc(8*sizeof(char*));
    for (int i=0; i<8; i++) {
        copy[i] = malloc(8* sizeof(char));
        for (int j=0; j<8; j++) copy[i][j] = board[i][j];
    }
    return copy;
}

/**
 * \fn display_board(char** board)
 * \brief Affiche la grille
 * \param board La grille
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
 * \fn has_player_won(char** board)
 * \brief fonction pour determiner si un joueur a gagné
 * \param board le plateau dont on souhaite determiner le vainqueur
 * \return B pour victoire des blancs, N pour victoire des noirs, R pour un jeu qui continue
*/
char has_player_won(char** board){
	int w=0;
    int b=0;
    for (int i=0; i<8;i++){
        for (int j=0; j<8;j++){
            if (board[i][j]==COULEUR_BLANC){w++;} ; 
            if (board[i][j]==COULEUR_NOIR){b++;} ; 
        }
    }
	if (w<14){
        return STATE_WON_NOIR;
    }
    if (b<14){
       return STATE_WON_BLANC;
    }

	return STATE_RUNNING;
}

/**
 * \fn etat(PAbalone r)
 * \brief Determiner l'état du jeu
 * \param r Le jeu
 * \return L'état du jeu actualisé
*/
char etat(PAbalone r){

	/*un fonction timer qui vas changer le timer de PAbalone 
si le timer n as pas encore commencer ==> r.timer prend 0
si le timer est entre 1 et 900 ==> r.timer prend 1
si le timer a depasser 900 ==> r.timer prend 2*/
	if(has_player_won(r->board) != 'R'){
		return has_player_won(r->board);
	}else if (r->timer>=TIME_LIMIT){
	   return STATE_TIMEOUT;
    }else if (r->timer == 0){
		return STATE_INITIALIZED;
	}
	return STATE_RUNNING;
}
	
/**
 * \fn play_game()
 * \brief Lancement du jeu
*/
void play_game(){
	PAbalone game = new_abalone();
	display_board(game->board);
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
				while(getchar() != '\n'); //vide le buffer d'entrée
			}while(strlen(a1) != 5);
			error = string_to_mouvement(a1,(&mvt));
			if(error == ERROR_OUT_OF_BOUNDS) printf("erreur de conversion de la chaine en coordonnées : coordonnée en dehors de la grille \n");
			else if(error)printf("erreur de conversion de la chaine en coordonnées : erreur inconnue\n");
			else error = finalise_mvt(game->board,game->player,mvt);
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
 * \brief Lancement du jeu contre l'Intelligence Artificielle
*/
void play_game_random_ia() {
    PAbalone game = new_abalone();
    display_board(game->board);
    Mouvement mvt;
    char* a1=malloc(6*sizeof(char));
    int error = 0;
    time_t start;

    char gameplayer = choose_color();

    while (game->state == STATE_RUNNING || game->state == STATE_INITIALIZED){
        start = time(NULL);
        do {
            if (game->player == gameplayer) {
                do{
                    printf("lettres entre A-H , et les nombre entre 1-8\n");
                    printf("insérer votre mouvement, ex : \"B1:C3\"\n");
                    scanf("%5s",a1);
					while(getchar() != '\n'); //vide le buffer d'entrée
                    error = string_to_mouvement(a1,&mvt);
					if(error == ERROR_OUT_OF_BOUNDS) printf("erreur de conversion de la chaine en coordonnées : coordonnée en dehors de la grille \n");
					else if(error)printf("erreur de conversion de la chaine en coordonnées : erreur inconnue\n");
					else error = finalise_mvt(game->board,game->player,mvt);
                }while(strlen(a1) != 5);
            } else play_random_move(game->board,game->player);
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


        display_board(game->board);//verifier si le mouvement en ligne de trois pion n'est pas bloqué par un autre pion
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
 * \fn void play_terminator()
 * \brief joue contre l'ia minmax, la pronfondeur est un variable globale
*/
void play_terminator() {
    PAbalone game = new_abalone();
    display_board(game->board);
    Mouvement mvt;
    char* a1=malloc(6*sizeof(char));
    int error = 0;
    time_t start;

    char gameplayer = choose_color();

    while (game->state == STATE_RUNNING || game->state == STATE_INITIALIZED){
        start = time(NULL);
        do {
            if (game->player == gameplayer) {
                do{
                    printf("lettres entre A-H , et les nombre entre 1-8\n");
                    printf("insérer votre mouvement, ex : \"B1:C3\"\n");
                    scanf("%5s",a1);
                    while(getchar() != '\n'); //vide le buffer d'entrée
                    error = string_to_mouvement(a1,&mvt);
                    if(error == ERROR_OUT_OF_BOUNDS) printf("erreur de conversion de la chaine en coordonnées : coordonnée en dehors de la grille \n");
                    else if(error)printf("erreur de conversion de la chaine en coordonnées : erreur inconnue\n");
                    else error = finalise_mvt(game->board,game->player,mvt);
                }while(strlen(a1) != 5);
            } else terminator_move(game->board, game->player);
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
 * \fn play_game_server(char* port)
 * \brief Lance le jeu en mode serveur 
 * \param port Le port où la partie sera lancé
*/
void play_game_server(char* port){
	PAbalone game = new_abalone();
	display_board(game->board);
	game->player = COULEUR_BLANC;
	Mouvement mvt;
	char* a1=malloc(6*sizeof(char));
	int error;
	time_t start;
	SOCKET master = TCP_Create_Server(atoi(port));
    SOCKET slave = accept(master,NULL,0);
	while (game->state == STATE_RUNNING || game->state == STATE_INITIALIZED){
		start = time(NULL);
		char *move = malloc(sizeof(char)*6);
		int a=recv(slave,move,sizeof(move),0);
		//int a= TCP_String_Reader(slave, move);
		//read(slave,move,sizeof(char)*6);
		//printf("%s",move);
		string_to_mouvement(move,(&mvt));
		finalise_mvt(game->board,COULEUR_NOIR,mvt);
		display_board(game->board);
		game->state = etat(game);
		if (game->state == STATE_WON_BLANC || game->state == STATE_WON_NOIR){break;}
		do {
			do{
				printf("lettres entre A-H , et les nembre entre 1-8\n");
	    		printf("inserer votre mouvement, ex : \"B1:C3\"\n");
				scanf("%5s",a1);
				while(getchar() != '\n'); //vide le buffer d'entrée
			}while(strlen(a1) != 5);
			error = string_to_mouvement(a1,(&mvt));
			if(error == ERROR_OUT_OF_BOUNDS) printf("erreur de conversion de la chaine en coordonnées : coordonnée en dehors de la grille \n");
			else if(error)printf("erreur de conversion de la chaine en coordonnées : erreur inconnue\n");
			else error = finalise_mvt(game->board,game->player,mvt);
			if(error)print_error(error);
		}while(error);
		write(slave,a1,sizeof(char)*6);
		//TCP_Long_Writer(slave,);
		if(game->state == STATE_INITIALIZED){
			game->timer += 1;
		}else{
			int time_elapsed = difftime(time(NULL),start);
			game->timer += time_elapsed;
		}
		game->state = etat(game);
		//debug("Game state : %c\n",game->state);

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
 * \fn play_game_client(char* server)
 * \brief Lance le jeu en mode client 
 * \param server Contient l'adresse ip et le port nécessaire pour la connection
*/
void play_game_client(char* server){  //server doit avoir comme format= 127.0.0.1:6969
	PAbalone game = new_abalone();
	display_board(game->board);
	game->player = COULEUR_NOIR;
	Mouvement mvt;
	char* a1=malloc(6*sizeof(char));
	char *move = malloc(sizeof(char)*6);
	int error;
	time_t start;
    char* server2 = strtok(server,":");
    char* port = strtok(NULL," ");
	SOCKET s = TCP_Create_Client(server2,atoi(port));
	while (game->state == STATE_RUNNING || game->state == STATE_INITIALIZED){
		start = time(NULL);
		char *move = malloc(sizeof(char)*6);
		do {
			do{
				printf("lettres entre A-H , et les nembre entre 1-8\n");
	    		printf("inserer votre mouvement, ex : \"B1:C3\"\n");
				scanf("%5s",a1);
				while(getchar() != '\n'); //vide le buffer d'entrée
			}while(strlen(a1) != 5);
			error = string_to_mouvement(a1,(&mvt));
			if(error == ERROR_OUT_OF_BOUNDS) printf("erreur de conversion de la chaine en coordonnées : coordonnée en dehors de la grille \n");
			else if(error)printf("erreur de conversion de la chaine en coordonnées : erreur inconnue\n");
			else error = finalise_mvt(game->board,game->player,mvt);
			if(error)print_error(error);
		}while(error);
		write(s,a1,sizeof(char)*6);
		display_board(game->board);
		game->state = etat(game);
		if (game->state == STATE_WON_BLANC || game->state == STATE_WON_NOIR){break;}
		recv(s, move,sizeof(move),0 );
		//read(s,move,sizeof(char)*6);
		//pread(s,move,sizeof(move),7);
		string_to_mouvement(move,(&mvt));
		finalise_mvt(game->board,COULEUR_BLANC,mvt);
		display_board(game->board);
		if(game->state == STATE_INITIALIZED){
			game->timer += 1;
		}else{
			int time_elapsed = difftime(time(NULL),start);
			game->timer += time_elapsed;
		}
		game->state = etat(game);
		//debug("Game state : %c\n",game->state);	

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
 * \fn play_game_server_ia(char* port)
 * \brief Lance le jeu en mode server ia 
 * \param port Le port nécessaire pour la connection
*/
void play_game_server_ia(char* port){
	PAbalone game = new_abalone();
	display_board(game->board);
	game->player = COULEUR_BLANC;
	Mouvement mvt;
	char* a1=malloc(6*sizeof(char));
	int error;
	time_t start;
	SOCKET master = TCP_Create_Server(atoi(port));
    SOCKET slave = accept(master,NULL,0);
	while (game->state == STATE_RUNNING || game->state == STATE_INITIALIZED){
		start = time(NULL);
		char *move = malloc(sizeof(char)*6);
		int a=recv(slave,move,sizeof(move),0);
		string_to_mouvement(move,(&mvt));
		finalise_mvt(game->board,COULEUR_NOIR,mvt);
		display_board(game->board);
		game->state = etat(game);
		if (game->state == STATE_WON_BLANC || game->state == STATE_WON_NOIR){break;}
		mvt = terminator_move(game->board,game->player);
		mouvement_to_string(mvt,a1);
		write(slave,a1,sizeof(char)*6);
		//TCP_Long_Writer(slave,);
		if(game->state == STATE_INITIALIZED){
			game->timer += 1;
		}else{
			int time_elapsed = difftime(time(NULL),start);
			game->timer += time_elapsed;
		}
		game->state = etat(game);
		//debug("Game state : %c\n",game->state);
		//free(a1);
		//free(move);
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
 * \fn play_game_client_ia(char* server)
 * \brief Lance le jeu en mode server ia 
 * \param server Contient l'adresse ip et le port nécessaire pour la connection sous format adresse:port
*/
void play_game_client_ia(char* server){  //server doit avoir comme format= 127.0.0.1:6969
	PAbalone game = new_abalone();
	display_board(game->board);
	game->player = COULEUR_NOIR;
	Mouvement mvt;
	char* a1=malloc(6*sizeof(char));
	char *move = malloc(sizeof(char)*6);
	int error;
	time_t start;
    char* server2 = strtok(server,":");
    char* port = strtok(NULL," ");
	SOCKET s = TCP_Create_Client(server2,atoi(port));
	while (game->state == STATE_RUNNING || game->state == STATE_INITIALIZED){
		start = time(NULL);
		char *move = malloc(sizeof(char)*6);
		mvt = terminator_move(game->board,game->player);
		mouvement_to_string(mvt,a1);
		write(s,a1,sizeof(char)*6);
		display_board(game->board);
		game->state = etat(game);
		if (game->state == STATE_WON_BLANC || game->state == STATE_WON_NOIR){break;}
		recv(s,move,sizeof(char)*6,0);
		string_to_mouvement(move,(&mvt));
		finalise_mvt(game->board,COULEUR_BLANC,mvt);
		display_board(game->board);
		if(game->state == STATE_INITIALIZED){
			game->timer += 1;
		}else{
			int time_elapsed = difftime(time(NULL),start);
			game->timer += time_elapsed;
		}
		game->state = etat(game);
		//debug("Game state : %c\n",game->state);	
		//free(a1);
		//free(move);
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