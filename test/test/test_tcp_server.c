#include "unity.h"
#include "tcp_server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void test_TCPServer_CreateServerSocket()
{
    //Use high numbered port, or else we need to run as admin
    const unsigned int tcp_port = 0x5555;
    int server_socket = createServerSocket(tcp_port);

    TEST_ASSERT_NOT_EQUAL(0, server_socket);

    //We check if the socket created has same port as the one provided
    struct sockaddr_in server_addr = {0};
    socklen_t len = sizeof(server_addr);
    int ret = getsockname(server_socket, (struct sockaddr *)&server_addr, &len);    
    if (ret == 0)
    {
        TEST_ASSERT_EQUAL(tcp_port, ntohs(server_addr.sin_port));
    }
    else
    {
        TEST_ABORT();
    }

    //Cannot figure out a way to test of server_socket is properly closed
    disposeServerSocket(server_socket);

}