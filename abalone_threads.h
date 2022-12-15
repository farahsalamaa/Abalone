#ifndef IMM2223_GR6_ABALONE_THREADS_H
#define IMM2223_GR6_ABALONE_THREADS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mouvement.h"
#include "abalone_terminal.h"
#include "debug.h"

#define TERMINAL 'T'
#define GTK 'G'

#define LOCAL 'L'
#define SERVER 'S'
#define CLIENT 'C'

#define PVP 'P'
#define PVE 'V'
#define EVE 'E'

typedef struct {
    char display;
    char comms;
    char mode;
    char aiplayer;
} TAttributes;

typedef struct {
    PAbalone abalone;
    Mouvement last_move;
    char input[6];
    pthread_t latest_thread;
    pthread_attr_t thread_attrs;
    TAttributes attr;
} ThreadedAbalone, *PThreadedAbalone;

void setup_game(PThreadedAbalone ta);
TAttributes get_basic_tattributes();
void set_tattributes(PThreadedAbalone ta, TAttributes attr);
void launch_game(PThreadedAbalone ta);

void* opt_switch(void* arg);
void* display_terminal(void* arg);
void* move_from_terminal(void* arg);
void* check_move(void* arg);
void* play_turn(void* arg);
void* end_turn(void* arg);

#endif //IMM2223_GR6_ABALONE_THREADS_H