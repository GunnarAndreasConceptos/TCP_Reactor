#include "unity.h"
#include "diagnostics_client.h"

//Force unity to compile the implementation of reactor interfaces as it does not seem to manage on its own
TEST_FILE("poll_reactor.c")

void test_DiagnosticsClient_CreateClient()
{
    Handle server_handle = 0;
    ServerEventNotifier event_notifier = {0};
    DiagnosticsClientPtr client = createClient(server_handle, &event_notifier);

    TEST_ASSERT_NOT_NULL(client);

    destroyClient(client);
}
