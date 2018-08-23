//Testing framework
#include "unity.h"
#include "diagnostics_server.h"

void test_CreateDiagnosticsServer()
{
    const unsigned int server_port = 1001;
    DiagnosticsServerPtr server = createServer(server_port);

    TEST_ASSERT_NOT_NULL(server);
}

void test_DestroyDiagnosticsServer()
{
    const unsigned int server_port = 1001;
    DiagnosticsServerPtr server = createServer(server_port);

    TEST_ASSERT_NOT_NULL(server);

    destroyServer(&server);

    TEST_ASSERT_NULL(server);
}

void test_DestroyDiagnosticsServer_AcceptsNULL()
{
    DiagnosticsServerPtr mock_server = NULL;
    destroyServer(&mock_server);

    TEST_ASSERT_NULL(mock_server);
}