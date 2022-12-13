#ifndef IMM2223_GR6_SERVEUR_H
#define IMM2223_GR6_SERVEUR_H

#endif //IMM2223_GR6_SERVEUR_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

SOCKET TCP_Create_Server(short service);

static void exchange();
SOCKET TCP_Create_Server(short service);
int TCP_String_Reader(SOCKET s,char *input);
int TCP_Long_Writer(SOCKET s,long value);
