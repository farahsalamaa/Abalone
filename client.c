#include "client.h"

// partie client du serveur

SOCKET TCP_Create_Client(char* serverName,short service){
    struct protoent *ppe = getprotobyname("tcp");
    if (ppe == NULL) exit(1);

    SOCKET s =socket(AF_INET,SOCK_STREAM,ppe->p_proto);
    if(s == INVALID_SOCKET) exit(1);

    struct sockaddr_in sin;
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverName);

    sin.sin_port = htons(service);

    if (connect (s, (struct sockaddr*) &sin, sizeof(sin)) == SOCKET_ERROR) exit(1);

    return s;
}
int TCP_String_Writer(SOCKET s,char *output){
    int bytes_sent=send(s,output,strlen(output),0);
    if(bytes_sent==SOCKET_ERROR)exit(1);
    return bytes_sent;
}
int TCP_Long_Reader(SOCKET s,long *value){
    char buffer[1500];
    int bytes_received = TCP_String_Reader(s,buffer);
    long input = ntohl(* (long *)buffer);
    *value=input;
    return bytes_received; 
}


/*int main(int argc, char** argv){
    SOCKET s = TCP_Create_Client("127.0.0.1",1234);
    char* input;
    recv(s, input,sizeof(input),0 );
    printf("%s\n",input);
    char *input2 = "loljaimebien";
    write(s,input2,sizeof(input2));

    shutdown(s,2);
}
*/

