#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

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

    unsigned socketPort = htons(3001);

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = socketPort;
    inet_aton("127.0.0.1", &addr.sin_addr.s_addr);

    int addrConnect = bind(createdSocket, &addr, sizeof(addr));

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

    int acceptConnections = accept(createdSocket, &addr, sizeof(addr));

    if (acceptConnections == -1)
    {
        printf("Error trying to accept a connection on socket");
        exit(0);
    }
}