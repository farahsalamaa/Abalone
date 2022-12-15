#ifndef IMM2223_GR6_CLIENT_H
#define IMM2223_GR6_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1



typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

//static void exchange();
SOCKET TCP_Create_Client(char* serverName,short service);
int TCP_String_Writer(SOCKET s,char * output);
int TCP_Long_Reader(SOCKET s,long *value);

/*
static void exchange();
SOCKET TCP_Create_Client(char* serverName,short service);
int TCP_String_Writer(SOCKET s,char * output);
int TCP_Long_Reader(SOCKET s,long *value);
*/
static void exchange();
SOCKET TCP_Create_Client(char* serverName,short service);
int TCP_String_Writer(SOCKET s,char * output);
int TCP_Long_Reader(SOCKET s,long *value);


#endif //IMM2223_GR6_CLIENT_H>>>>>>> .r231
