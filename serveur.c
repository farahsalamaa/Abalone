#include "serveur.h"

SOCKET TCP_Create_Server(short service){
    int fdsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fdsocket == INVALID_SOCKET) exit(1);
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(service);
    int opt = 1;
    setsockopt(fdsocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(fdsocket, (struct sockaddr*) &addr, sizeof(addr)) == SOCKET_ERROR) exit(1);
    if (listen (fdsocket,5) == SOCKET_ERROR) exit(1);
    return fdsocket;
}
