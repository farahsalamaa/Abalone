#ifndef IMM2223_GR6_SERVEUR_H
#define IMM2223_GR6_SERVEUR_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "client.h"

#endif //IMM2223_GR6_SERVEUR_H

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

/**
 * \fn TCP_Create_Server(short service)
 * \brief cree une socket TCP pour le serveur 
 * \param mvt le mouvement donné
 * \param board le tableau de la partie
 * \param player le joueur actif
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un message d'erreur correspondant
*/
SOCKET TCP_Create_Server(short service);
