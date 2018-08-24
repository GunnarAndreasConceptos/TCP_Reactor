//Testing framework
#include "unity.h"
#include "diagnostics_server.h"

void test_DiagnosticsServer_CreateServer()
{
    const unsigned int server_port = 1001;
    DiagnosticsServerPtr server = createServer(server_port);
    TEST_ASSERT_NOT_NULL(server);

    destroyServer(server);
}