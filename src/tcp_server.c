#include "tcp_server.h"

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int createServerSocket(unsigned int tcp_port)
{
    struct sockaddr_in address = {0};
    const int server_handle = socket(PF_INET, SOCK_STREAM, 0);

    if (server_handle < 0)
    {
        printf("Failed to create server socket");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(tcp_port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len = sizeof(address);
    if (bind(server_handle, (struct sockaddr *)&address, len) != 0)
    {
        printf("bind() failed");
        return 0;
    }

    if (listen(server_handle, SOMAXCONN) != 0)
    {
        printf("listen() failed");
        return 0;
    }

    return server_handle;
}

void disposeServerSocket(int server_socket)
{
    (void)close(server_socket);
}
