//Testing framework
#include "unity.h"
#include "diagnostics_server.h"

void test_DiagnosticsServer_CreateServer()
{
    const unsigned int server_port = 1001;
    DiagnosticsServerPtr server = createServer(server_port);
    TEST_ASSERT_NOT_NULL(server);
}

void test_DiagnosticsServer_DestroyServer()
{
    //Setup
    const unsigned int server_port = 1001;
    DiagnosticsServerPtr server = createServer(server_port);
    TEST_ASSERT_NOT_NULL(server);

    //Test that server is set to NULL after destroying
    destroyServer(&server);
    TEST_ASSERT_NULL(server);

    //Test that we do not crash when we pass a NULL into destroyServer
    server = NULL;
    destroyServer(&server);
    TEST_ASSERT_NULL(server);
}
