#include <stdio.h>
#include <sys/socket.h>

void main()
{
    printf("Main was called");

    /* A conexao de um socket consiste em um estilo de conexao
    e o protocolo que vai ser implementado */

    int createdSocket = socket(PF_INET, SOCK_STREAM, 0);

    if (createdSocket == -1)
    {
        printf("Error trying to create an socket");
        exit(0);
    }

    struct sockaddr addr = {AF_INET, SOCK_STREAM};
    socklen_t addrlen = sizeof(addr);
    struct sockaddr *addrPtr = &addr;

    int addrConnect = bind(createdSocket, addrPtr, addrlen);

    if (addrConnect == -1)
    {
        printf("Error trying to create an socket address");
        exit(0);
    }

    int socketListening = listen(createdSocket, 10);

    if (socketListening == -1)
    {
        printf("Error trying to start listening on socket");
    }
}