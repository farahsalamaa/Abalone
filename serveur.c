#include "serveur.h"
#include <stdlib.h>

/**
 * \fn TCP_Create_Server(short service)
 * \brief cree une socket TCP pour le serveur 
 * \param mvt le mouvement donné
 * \param board le tableau de la partie
 * \param player le joueur actif
 * \return VALIDATION_OK s'il n'est pas bloqué, sinon un message d'erreur correspondant
*/

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
int TCP_String_Reader(SOCKET s,char *input){
    char buffer[1500];
    char *tmp=buffer;
    int bufferlen = sizeof(buffer);
    int len;
    
    do{
        len =recv(s,tmp,bufferlen,0);
        tmp+=len;
        bufferlen-=len;
    }while(len!=SOCKET_ERROR && len!=0 && bufferlen!=0);
   
    if(len == SOCKET_ERROR)exit(1);
   
    memcpy(input, buffer ,tmp-buffer);
    input[tmp-buffer]='\0';
   
    return tmp-buffer;
}
int TCP_Long_Writer(SOCKET s,long value){
    long output= htonl(value);
    int bytes_sent = send(s,(const char *)& output,sizeof(output),0);
    if (bytes_sent==SOCKET_ERROR)exit(1);
    return bytes_sent;
}

/*
int main_server(){
    SOCKET master = TCP_Create_Server(1234);
    char *move = "A1:B1";
    char *move2 = malloc(sizeof(char)*13);
    while(1){
        SOCKET slave = accept(master,NULL,0);
        write(slave,move,6);
        recv(slave,move2,sizeof(move2),0);
        printf("%s\n",move2);
        shutdown(slave,2);}
    shutdown(master,2);
    return 0;
}

int main(int argc, char *argv){
    SOCKET master = TCP_Create_Server(6969);
    while(1){
        SOCKET slave = accept(master,NULL,0);
        exchange(slave);
        shutdown(slave,2);
    }
    shutdown(master,2);
}
*/