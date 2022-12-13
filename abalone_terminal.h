#ifndef IMM2223_GR6_ABALONE_TERMINAL_H
#define IMM2223_GR6_ABALONE_TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "const.h"
#include "debug.h"
#include "mouvement.h"
#include "ia.h"

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
void play_terminator(int depth);
void play_game_server(char* port);
void play_game_client(char* server);
void print_error(int error);
char has_player_won(char** board);
char etat(PAbalone r);
#endif //IMM2223_GR6_ABALONE_TERMINAL_H
