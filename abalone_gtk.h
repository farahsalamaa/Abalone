#ifndef IMM2223_GR6_ABALONE_GTK_H
#define IMM2223_GR6_ABALONE_GTK_H
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "debug.h"
#include "abalone_terminal.h"
#include "mouvement.h"
#include "ia.h"
#include "const.h"



/**
 * \file abalone_gtk.h
 * \brief Bibliotheque des fonctions lancement du jeu en GTK
*/

void play_game_gtk(int argc, char **argv);
void play_game_gtk2(int argc, char **argv);
void play_game_gtk3(int argc, char **argv);

#endif //IMM2223_GR6_ABALONE_GTK_H
