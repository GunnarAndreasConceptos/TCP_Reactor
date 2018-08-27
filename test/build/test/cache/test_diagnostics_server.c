#include "@@@@tcp_server.c"
#include "../src/tcp_server.c"
#include "@@@@diagnostics_client.c"
#include "../src/diagnostics_client.c"
#include "@@@@poll_reactor.c"
#include "../src/poll_reactor.c"
#include "build/temp/_test_diagnostics_server.c"
#include "diagnostics_server.h"
#include "unity.h"














void test_DiagnosticsServer_CreateServer()

{

    const unsigned int server_port = 1001;

    DiagnosticsServerPtr server = createServer(server_port);

    if ((((server)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(14))));};



    destroyServer(server);

}
