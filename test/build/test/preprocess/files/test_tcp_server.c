#include "build/temp/_test_tcp_server.c"
#include "tcp_server.h"
#include "unity.h"






void test_TCPServer_CreateServerSocket()

{



    const unsigned int tcp_port = 0x5555;

    int server_socket = createServerSocket(tcp_port);



    if (((0) != (server_socket))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(14)));};





    struct sockaddr_in server_addr = {0};

    socklen_t len = sizeof(server_addr);

    int ret = getsockname(server_socket, (struct sockaddr *)&server_addr, &len);

    if (ret == 0)

    {

        UnityAssertEqualNumber((UNITY_INT)((tcp_port)), (UNITY_INT)((ntohs(server_addr.sin_port))), (

       ((void *)0)

       ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);

    }

    else

    {

        longjmp(Unity.AbortFrame, 1);

    }





    disposeServerSocket(server_socket);



}
