#ifndef IMM2223_GR6_ABALONE_GTK_H
#define IMM2223_GR6_ABALONE_GTK_H

#include <stdlib.h>
#include "gtk/gtk.h"
#include <math.h>
#include <ctype.h>
#include <string.h>
//#include <glib.h>

#include "debug.h"
#include "abalone_terminal.h"
#include "mouvement.h"

/**
 * \file abalone_gtk.h
 * \brief Bibliotheque des fonctions lancement du jeu en GTK
*/

int play_game_gtk(int argc, char **argv);

#endif //IMM2223_GR6_ABALONE_GTK_H
