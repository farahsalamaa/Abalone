#include "abalone_threads.h"

void setup_game(PThreadedAbalone ta){
    trace();
    ta->abalone = new_abalone();
    ta->last_move.start.x = -1;
    ta->last_move.start.y = -1;
    ta->last_move.end.x = -1;
    ta->last_move.end.y = -1;

    trace();
}

TAttributes get_basic_tattributes(){
    TAttributes tattrs;
    tattrs.display = TERMINAL;
    tattrs.mode = PVP;
    tattrs.comms = LOCAL;
    return tattrs;
}

void set_tattributes(PThreadedAbalone ta, TAttributes attr){
    ta->attr = attr;
}

void launch_game(PThreadedAbalone ta){
    pthread_t thread1;
    ta->latest_thread = thread1;
    
    pthread_attr_t thread_attrs;
    pthread_attr_init(&thread_attrs);
    pthread_attr_setdetachstate(&thread_attrs,PTHREAD_CREATE_DETACHED);
    ta->thread_attrs = thread_attrs;
    trace();
    pthread_create(&thread1,&thread_attrs,opt_switch,ta);
    trace();

    while (ta->abalone->state == 'R' || ta->abalone->state == 'I'){sleep(1);debug("Current game state : %c",ta->abalone->state);};
    trace();
    pthread_cancel(ta->latest_thread);
    if(ta->abalone->state == STATE_WON_NOIR){
        printf("Victoire des NOIRS\n");
    }else{
        printf("Victoire des BLANCS\n");
    }

    return;
}

void* opt_switch(void* arg){
    trace();
    pthread_testcancel();
    PThreadedAbalone ta = (PThreadedAbalone) arg;
    if (ta->attr.display == TERMINAL && ta->attr.mode == PVP){
        pthread_create(&(ta->latest_thread),&(ta->thread_attrs),display_terminal,ta);
        return NULL;
    }else{

    }
    return NULL;
}

void* display_terminal(void* arg){
    trace();
    PThreadedAbalone ta = (PThreadedAbalone) arg;
    if(ta->abalone->player == COULEUR_NOIR){
        printf("c'est au tour des NOIRS\n");
    }else{
        printf("c'est au tour des BLANCS\n");
    }
    if(ta->last_move.start.x != -1){
        char buffer[] = "AAAAA";
        mouvement_to_string(ta->last_move,buffer);
        printf("Mouvement précédent : %s\n",buffer);
    }
    display_board(ta->abalone->board);
    pthread_create(&(ta->latest_thread),&(ta->thread_attrs),move_from_terminal,ta);
    return NULL;
}

void* move_from_terminal(void* arg){
    trace();
    PThreadedAbalone ta = (PThreadedAbalone) arg;
    char buffer[] = "AAAAA\0";
    printf("lettres entre A-H , et les nembre entre 1-8\n");
	printf("inserer votre mouvement, ex : \"B1:C3\"\n");
	scanf("%5s",buffer);
	while(getchar() != '\n'); //vide le buffer d'entrée
    strcpy(ta->input,buffer);
    pthread_create(&(ta->latest_thread),&(ta->thread_attrs),check_move,ta);
    return NULL;
}

void* check_move(void* arg){
    trace();
    PThreadedAbalone ta = (PThreadedAbalone) arg;
    Mouvement mvt;
    int error = string_to_mouvement(ta->input,&mvt);
    if(!error){ 
        error = validate_mvt(ta->abalone->board,ta->abalone->player,mvt);
    }else{
        print_error(error);
        pthread_create(&(ta->latest_thread),&(ta->thread_attrs),move_from_terminal,ta);
        return NULL;
    }
    if(!error){
        pthread_create(&(ta->latest_thread),&(ta->thread_attrs),play_turn,ta);
        return NULL;
    }else{
        print_error(error);
        pthread_create(&(ta->latest_thread),&(ta->thread_attrs),move_from_terminal,ta);
        return NULL;
    }
}

void* play_turn(void* arg){
    trace();
    PThreadedAbalone ta = (PThreadedAbalone) arg;
    string_to_mouvement(ta->input,&(ta->last_move));
    exec_mvt(ta->abalone->board,ta->abalone->player,ta->last_move);
    pthread_create(&(ta->latest_thread),&(ta->thread_attrs),end_turn,ta);
    return NULL;
}

void* end_turn(void* arg){
    trace();
    PThreadedAbalone ta = (PThreadedAbalone) arg;
    ta->abalone->state = etat(ta->abalone);
    debug("New game state : %c",ta->abalone->state);
    ta->abalone->player = other_player(ta->abalone->player);
    pthread_create(&(ta->latest_thread),&(ta->thread_attrs),opt_switch,ta);
    return NULL;
}

int play_terminal(){
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