#include "unity.h"
#include "diagnostics_client.h"

void test_DiagnosticsClient_CreateClient()
{
    Handle server_handle = 0;
    ServerEventNotifier event_notifier = {0};
    DiagnosticsClientPtr client = createClient(server_handle, &event_notifier);

    TEST_ASSERT_NOT_NULL(client);

    destroyClient(client);
}
