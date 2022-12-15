#ifndef IMM2223_GR6_ABALONE_TERMINAL_H
#define IMM2223_GR6_ABALONE_TERMINAL_H
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "debug.h"
#include "mouvement.h"
#include "ia.h"
#include "client.h"
#include "serveur.h"


/**
 * \struct Abalone
 * \brief Contient les informations du jeu: board, state, player, timer
*/
/**
 * \typedef PAbalone
 * \brief Pointeur vers  un Abalone
*/
typedef struct {
    /*!Le plateau du jeu*/
    char** board;
    /*!L'état du jeu*/
    char state;
    /*!L'identité du joueur actif (qui doit jouer), noir ou blanc*/
    char player;
    /*!Le temps écoulé, en secondes*/
    int timer;
} Abalone, *PAbalone;



/**
 * \file abalone_terminal.h
 * \brief Bibliothèque des fonctions de creation du jeu et lancement du jeu
*/

/*  à regarder
typedef struct{
    Coord pos[2];
}tposition;
*/

void init_board(PAbalone game);
PAbalone new_abalone();
PAbalone new_abalone_board(char** tab);
char** create_board();
void destroy_board(char** board);
void destroy_abalone(PAbalone abalone);
char** copy_board(char** board);
void display_board(char** board);

void play_game();
void play_game_random_ia();
void play_terminator();
void play_game_server(char* port);
void play_game_client(char* server);
void play_game_server_ia(char* port);
void play_game_client_ia(char* server);
void print_error(int error);
char has_player_won(char** board);
char etat(PAbalone r);
#endif //IMM2223_GR6_ABALONE_TERMINAL_H
