#include "@@@@poll_reactor.c"
#include "../src/poll_reactor.c"
#include "build/temp/_test_diagnostics_client.c"
#include "diagnostics_client.h"
#include "unity.h"








void test_DiagnosticsClient_CreateClient()

{

    Handle server_handle = 0;

    ServerEventNotifier event_notifier = {0};

    DiagnosticsClientPtr client = createClient(server_handle, &event_notifier);



    if ((((client)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(13))));};



    destroyClient(client);

}
