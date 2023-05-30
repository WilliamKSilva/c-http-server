#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE 1025

struct socketCreated
{
    struct sockaddr_in addr;
    int socket;
};

struct socketCreated createSocket()
{
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
    inet_aton("127.0.0.1", &addr.sin_addr);

    /*
        Typecasting o segundo argumento sockaddr. Sockaddr e um descriptor de socket generico
        enquanto o sockaddr_in e usado para sockets de conexao IP, INET.
    */
    int addrConnect = bind(createdSocket, (struct sockaddr *)&addr, sizeof(addr));

    if (addrConnect == -1)
    {
        printf("Error trying to create an socket address");
        exit(0);
    }

    struct socketCreated socket =
        {
            addr,
            createdSocket};

    return socket;
}

void main()
{
    printf("Main was called");

    /* A conexao de um socket consiste em um estilo de conexao
    e o protocolo que vai ser implementado */

    struct socketCreated createdSocket = createSocket();

    int socketListening = listen(createdSocket.socket, 10);

    if (socketListening == -1)
    {
        printf("Error trying to start listening on socket");
    }

    socklen_t addr_size;
    addr_size = sizeof(createdSocket.addr);

    int acceptConnections = accept(createdSocket.socket, (struct sockaddr *)&createdSocket.addr, &addr_size);

    if (acceptConnections == -1)
    {
        printf("Error trying to accept a connection on socket");
        exit(0);
    }

    char buffer[BUFFER_SIZE];

    ssize_t bytes = recv(acceptConnections, &buffer, BUFFER_SIZE - 1, 0);

    if (bytes == -1)
    {
        perror("Error receiving data from socket");
        return;
    }

    buffer[bytes] = '\0';

    printf("Received data: %s\n", buffer);
}